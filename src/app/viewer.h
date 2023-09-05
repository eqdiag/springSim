#ifndef VIEWER_H
#define VIEWER_H

#include <memory>

#include "core/app.h"
#include "core/shader.h"
#include "core/mesh.h"
#include "core/asset_loader.h"
#include "core/camera.h"
#include "core/timer.h"

#include "math/matrix.h"

#include "physics/bounds.h"
#include "physics/physics_system.h"

static const char* meshes[] = {
	"cube.obj",
	"dodec.obj",
	"tet.obj"
};

class Viewer : public core::App {
public:
	Viewer();
	~Viewer() override;
	void init() override;
	void update();
	void render();

	const char* getCurrentMeshStr();
	void resetSimulation();

	//Input state variables
	bool mViewerOpen;
	bool mMousePressed;
	bool mMouseInit;
	float mMouseX;
	float mMouseY;

	//Simulation variables
	bool mRunSimulation;
	float mDt;
	float mStiffness;
	float mDampen;
	float mGravity;
	float mParticleMass;

	//Shader uniforms
	math::Mat4 mModelMatrix{};
	math::Mat4 mViewMatrix{};
	math::Mat4 mProjMatrix{};

	//Model and camera
	std::string mCurrentMesh;
	std::shared_ptr<core::Mesh> mMesh;
	std::unique_ptr<core::ArcCamera> mCamera;
	std::shared_ptr<GravityForce> mGravityForce;
	std::shared_ptr<SpringForce> mSpringForce;
	PhysicsSystem mSystem;

private:


	core::Shader mBoundsShader{};
	core::Shader mMeshShader{};
	std::shared_ptr<Bounds> mBounds;

	core::AssetLoader mLoader{};

	core::Timer mTimer;


};


#endif