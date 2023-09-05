#include "physics_system.h"



PhysicsSystem::PhysicsSystem():
	mNumParticles{ 0 }
{
}

void PhysicsSystem::init(std::shared_ptr<core::Mesh> mesh, std::shared_ptr<Bounds> bounds, float particleMass)
{
	mMesh = mesh;
	mBounds = bounds;
	mNumParticles = mesh->getNumVertices();

	mVelocities.resize(mNumParticles);
	std::fill(mVelocities.begin(), mVelocities.end(), 0.0);
	mForces.resize(mNumParticles);
	std::fill(mForces.begin(), mForces.end(), 0.0);
	mMasses.resize(mNumParticles);
	std::fill(mMasses.begin(), mMasses.end(), particleMass);

}

void PhysicsSystem::simulate(float dt)
{
	//Clear old forces
	clearForces();

	//Accumulate forces
	for (int i = 0; i < mNumParticles; i++) {
		for (auto& force : mSystemForces){
			mForces[i] += force->computeForce(i,mMesh->getVertexData(), mVelocities);
		}
	}
	

	//Update velocities
	for (int i = 0; i < mNumParticles; i++) {
		//Explicit euler update
		mVelocities[i] += ((mForces[i] / mMasses[i])*dt);
	}

	//Updated positions
	auto& positions = mMesh->getVertexDataMut();
	for (int i = 0; i < mNumParticles;i++) {
		auto newPosition = math::Vec3{ positions[i].x,positions[i].y,positions[i].z } + mVelocities[i] * dt;
		mMesh->setPosition(i,newPosition);
	}

	//Apply collision resolution
	mBounds->applyBounds(0.7, positions, mVelocities);

	mMesh->refreshPositions();
}

void PhysicsSystem::setParticleMasses(float particleMass)
{
	std::fill(mMasses.begin(), mMasses.end(), particleMass);
}

void PhysicsSystem::reset(std::shared_ptr<core::Mesh> mesh, std::shared_ptr<Bounds> bounds, float particleMass)
{
	mMesh = mesh;
	mBounds = bounds;
	mNumParticles = mesh->getNumVertices();

	std::cout << "num partices: " << mNumParticles << std::endl;

	mVelocities.clear();
	mForces.clear();
	mMasses.clear();

	mVelocities.resize(mNumParticles);
	std::fill(mVelocities.begin(), mVelocities.end(), 0.0);
	mForces.resize(mNumParticles);
	std::fill(mForces.begin(), mForces.end(), 0.0);
	mMasses.resize(mNumParticles);
	std::fill(mMasses.begin(), mMasses.end(), particleMass);
}


void PhysicsSystem::addForce(std::shared_ptr<Force> newForce)
{
	mSystemForces.push_back(newForce);
}

void PhysicsSystem::clearForces()
{
	for (auto& force : mForces) {
		force = math::Vec3{ 0.0,0.0,0.0 };
	}
}
