#include "core/settings.h"

#include "app/viewer.h"



Viewer::Viewer():
	App{},
	mViewerOpen{true},
	mMousePressed{false},
	mMouseInit{false},
	mMouseX{},
	mMouseY{},
	mRunSimulation{false},
	mDt{ 0.2 },
	mStiffness{ 20.0 },
	mDampen{ 0.7 },
	mGravity{ 1.0 },
	mParticleMass{ 0.1 },
	mBounds{std::make_shared<Bounds>(4.0,4.0,4.0)},
	mTimer{50}
{

}

Viewer::~Viewer()
{
}


void Viewer::init()
{

	//Create graphics assets
	mBoundsShader.init(SHADER_DIR, "bounds.vs", "bounds.fs");
	mMeshShader.init(SHADER_DIR, "mesh.vs", "mesh.fs");

	
	mCurrentMesh = "cube.obj";
	mMesh = mLoader.loadMesh(MODEL_DIR,mCurrentMesh.c_str());
	float radius = mMesh->getBoundingRadius();
	mCamera = std::make_unique<core::ArcCamera>(mMesh->getCentroid(), 2.0 * radius);

	float boxExtents = 6 * radius;
	mBounds->init(boxExtents,boxExtents,boxExtents);



	mSystem.init(mMesh, mBounds,mParticleMass);

	mGravityForce = std::make_shared<GravityForce>(mGravity);
	mSpringForce = std::make_shared<SpringForce>(mStiffness, mDampen, *mMesh);

	//Add gravity
	mSystem.addForce(mGravityForce);
	mSystem.addForce(mSpringForce);


	auto eye = mCamera->getEye();

	mModelMatrix = math::Mat4::identity();
	mViewMatrix = mCamera->getViewMatrix();
	mProjMatrix = math::Mat4::perspectiveProjection(3.14*45.0/180.0, 800.0 / 600.0, 0.1, 1000.);


	mBoundsShader.use();
	mBoundsShader.setUniformMat4("model", mModelMatrix.getRawData());
	mBoundsShader.setUniformMat4("view", mViewMatrix.getRawData());
	mBoundsShader.setUniformMat4("proj", mProjMatrix.getRawData());
	mBoundsShader.setUniformFloat("checkerFreq",radius*0.5);

	mMeshShader.use();
	mMeshShader.setUniformMat4("model", mModelMatrix.getRawData());
	mMeshShader.setUniformMat4("view", mViewMatrix.getRawData());
	mMeshShader.setUniformMat4("proj", mProjMatrix.getRawData());
	mMeshShader.setUniformFloat3("eye", mCamera->getEye());



	glClearColor(0.22f, 0.22f, 0.22f, 1.0f);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);
}

void Viewer::update()
{
	if (mRunSimulation) {
		float dtSeconds = mDt / 1000.0;
		mSystem.simulate(dtSeconds);
	}
}

void Viewer::render()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


	mViewMatrix = mCamera->getViewMatrix();

	//Set uniforms
	mBoundsShader.use();
	mBoundsShader.setUniformMat4("view", mViewMatrix.getRawData());

	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);
	mBounds->Render();

	mMeshShader.use();
	mMeshShader.setUniformMat4("view", mViewMatrix.getRawData());
	mMeshShader.setUniformFloat3("eye", mCamera->getEye());

	glDisable(GL_CULL_FACE);
	mMesh->Render();

	mTimer.tick();
}



void Viewer::resetSimulation()
{
	mMesh = mLoader.loadMesh(MODEL_DIR, mCurrentMesh.c_str());
	float radius = mMesh->getBoundingRadius();
	float boxExtents = 6 * radius;
	mBounds->reset(boxExtents, boxExtents, boxExtents);
	mSystem.reset(mMesh, mBounds, mParticleMass);
}





