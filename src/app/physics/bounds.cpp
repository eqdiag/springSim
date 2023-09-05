#include "bounds.h"

#include "core/mesh.h"


Bounds::Bounds(float sizeX, float sizeY, float sizeZ):
	mSize{ sizeX,sizeY,sizeZ },
	mVAO{0},
	mVBO{0}
{
}

void Bounds::init(float sizeX,float sizeY,float sizeZ)
{
	setBounds(sizeX, sizeY, sizeZ);

	std::vector<math::Vec3> vertices{};
	int num_cube_vertices = sizeof(cubeVertices) / sizeof(float);
	for (int i = 0; i < num_cube_vertices; i += 3) {
		vertices.emplace_back(math::Vec3{cubeVertices[i] * mSize.x(), cubeVertices[i + 1] * mSize.y(), cubeVertices[i + 2] * mSize.z()});
	}


	glGenVertexArrays(1, &mVAO);
	glGenBuffers(1, &mVBO);

	glBindVertexArray(mVAO);

	glBindBuffer(GL_ARRAY_BUFFER, mVBO);
	glBufferData(GL_ARRAY_BUFFER, vertices.size() * 3 * sizeof(float), vertices.data(), GL_STATIC_DRAW);

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), 0);

}

void Bounds::reset(float sizeX, float sizeY, float sizeZ)
{
	mSize = math::Vec3{ sizeX,sizeY,sizeZ };


	std::vector<math::Vec3> vertices{};
	int num_cube_vertices = sizeof(cubeVertices) / sizeof(float);
	for (int i = 0; i < num_cube_vertices; i += 3) {
		vertices.emplace_back(math::Vec3{cubeVertices[i] * mSize.x(), cubeVertices[i + 1] * mSize.y(), cubeVertices[i + 2] * mSize.z()});
	}

	glBindVertexArray(mVAO);

	glBindBuffer(GL_ARRAY_BUFFER, mVBO);
	glBufferData(GL_ARRAY_BUFFER, vertices.size() * 3 * sizeof(float), vertices.data(), GL_STATIC_DRAW);
}

void Bounds::setBounds(float sizeX, float sizeY, float sizeZ)
{
	mSize = math::Vec3{ sizeX,sizeY,sizeZ };
}

Bounds::~Bounds()
{
	glDeleteBuffers(1, &mVBO);
	glDeleteVertexArrays(1, &mVAO);
}

void Bounds::applyBounds(float restitutionCoeff,std::vector<core::VertexData>& positions, std::vector<math::Vec3>& velocities)
{
	for (int i = 0; i < positions.size(); i++) {
		applyBounds(restitutionCoeff, positions[i], velocities[i]);
	}
}

void Bounds::Render()
{
	glBindVertexArray(mVAO);
	glDrawArrays(GL_TRIANGLES, 0, 36);
}

void Bounds::applyBounds(float restitutionCoeff,core::VertexData& pos, math::Vec3& vel)
{
	//Check if penetrated bounds and measure by how much
	if (abs(pos.x) >= 0.5 * mSize.x()) {
		float dx = abs(pos.x) - 0.5 * mSize.x();
		float sign = 1.0f;
		if (pos.x > 0.0) sign *= -1.0f;
		pos.x = sign * (-0.5f * mSize.x() + dx * restitutionCoeff);
		vel[0] = -vel.x() * restitutionCoeff;
	}


	if (abs(pos.y) >= 0.5*mSize.y()) {
		float dy = abs(pos.y) - 0.5 * mSize.y();
		float sign = 1.0f;
		if (pos.y > 0.0) sign *= -1.0f;
		pos.y = sign*( -0.5f * mSize.y() + dy * restitutionCoeff);
		vel[1] = -vel.y() * restitutionCoeff;
	}

	if (abs(pos.z) >= 0.5 * mSize.z()) {
		float dz = abs(pos.z) - 0.5 * mSize.z();
		float sign = 1.0f;
		if (pos.z > 0.0) sign *= -1.0f;
		pos.z = sign * (-0.5f * mSize.z() + dz * restitutionCoeff);
		vel[2] = -vel.z() * restitutionCoeff;
	}
}
