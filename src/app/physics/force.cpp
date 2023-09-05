#include "force.h"
#include <cassert>

GravityForce::GravityForce(float gravConstant):
	mForce{0.0,-gravConstant,0.0}
{
}

void GravityForce::setGravity(float gravConstant)
{
	mForce = math::Vec3{ 0.0,-gravConstant,0.0 };
}


math::Vec3 GravityForce::computeForce(int i, const std::vector<core::VertexData>& positions, std::vector<math::Vec3>& velocities)
{
	return mForce;
}

SpringForce::SpringForce(float springConstant, float dampingConstant,const core::Mesh& mesh):
	mSpringConstant{springConstant},
	mDampingConstant{dampingConstant}
{
	auto positions = mesh.getVertexData();
	//Build springs based on initial mesh positions
	for (int i = 0; i < positions.size(); i++) {
		for (int j = i+1; j < positions.size(); j++) {
			math::Vec3 p{ positions[i].x,positions[i].y,positions[i].z };
			math::Vec3 q{ positions[j].x, positions[j].y, positions[j].z };
			auto dx = p - q;
			if (dx.norm2() > 0.01) {
				mSprings.push_back(Spring{ i,j,dx.norm() });
			}
		}
	}


}

void SpringForce::setSpringConstant(float springConstant)
{
	mSpringConstant = springConstant;
}

void SpringForce::setDampingConstant(float dampingConstant)
{
	mDampingConstant = dampingConstant;
}

math::Vec3 SpringForce::computeForce(int i, const std::vector<core::VertexData>& positions, std::vector<math::Vec3>& velocities)
{
	//Without damping, compute spring force for each other spring
	math::Vec3 force{0.0,0.0,0.0}; 
	math::Vec3 pi{ positions[i].x,positions[i].y,positions[i].z };
	//std::cout << mSpringConstant << std::endl;
	for (auto& spring : mSprings) {
		if (spring.i == i) {
			assert(i != spring.j);
			math::Vec3 pj{ positions[spring.j].x, positions[spring.j].y, positions[spring.j].z };
			auto dx = pj - pi;
			float l = dx.norm();
			auto dxn = dx / l;
			math::Vec3 springForce{dxn* mSpringConstant*(l - spring.length)};
			math::Vec3 dampingForce{dxn* mDampingConstant* (velocities[spring.j] - velocities[spring.i]).dot(dxn)};
			force += springForce + dampingForce;
		}
	}

	return force;
}
