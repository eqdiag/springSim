#ifndef PHYSICS_SYSTEM_H
#define PHYSICS_SYSTEM_H

#include <memory>

#include "core/mesh.h"
#include "math/vec.h"

#include "bounds.h"
#include "force.h"


class PhysicsSystem {
public:
	PhysicsSystem();
	void init(std::shared_ptr<core::Mesh> mesh, std::shared_ptr<Bounds> bounds,float particleMass = 1.0f);
	void simulate(float dt);

	void setParticleMasses(float particleMass);
	void reset(std::shared_ptr<core::Mesh> mesh, std::shared_ptr<Bounds> bounds, float particleMass);

	//Force stuff
	void addForce(std::shared_ptr<Force> newForce);
	void clearForces();
private:

	//Bounds for checking collisions
	std::shared_ptr<Bounds> mBounds;

	int mNumParticles;
	//Positions stored in mesh
	std::shared_ptr<core::Mesh> mMesh;
	//Velocities
	std::vector<math::Vec3> mVelocities;
	std::vector<math::Vec3> mForces;
	std::vector<float> mMasses;

	std::vector<std::shared_ptr<Force>> mSystemForces;
};

#endif 
