#ifndef FORCE_H
#define FORCE_H

#include <vector>

#include "math/vec.h"
#include "core/mesh.h"

class Force{
public:
	//Compute force on particle i
	virtual math::Vec3 computeForce(int i, const std::vector<core::VertexData>& positions, std::vector<math::Vec3>& velocities) = 0;
};

class GravityForce : public Force {
public:
	GravityForce(float gravConstant = 9.8f);
	void setGravity(float gravConstant);
	math::Vec3 computeForce(int i, const std::vector<core::VertexData>& positions, std::vector<math::Vec3>& velocities) override;
private:
	math::Vec3 mForce;
};

class SpringForce : public Force {

	struct Spring {
		//Vertex indices
		int i;
		int j;
		float length;
	};

public:
	SpringForce(float springConstant,float dampingConstant,const core::Mesh& mesh);
	void setSpringConstant(float springConstant);
	void setDampingConstant(float dampingConstant);
	math::Vec3 computeForce(int i, const std::vector<core::VertexData>& positions, std::vector<math::Vec3>& velocities) override;

private:
	float mSpringConstant;
    float mDampingConstant;
	std::vector<Spring> mSprings;
};


#endif