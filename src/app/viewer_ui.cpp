#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"

#include "app/viewer.h"
#include "app/viewer_ui.h"


ViewerUi::ViewerUi(core::Window& window, Viewer& viewer) :
    Ui{ window }, mViewer{ viewer}
{
}

void ViewerUi::update()
{
    ImGuiWindowFlags window_flags = ImGuiWindowFlags_MenuBar;
    window_flags |= ImGuiWindowFlags_NoBackground;



    if (ImGui::BeginMainMenuBar())
    {
        if (ImGui::BeginMenu("View"))
        {
            if (ImGui::MenuItem("Simulation Parameters")) {
                mViewer.mViewerOpen = !mViewer.mViewerOpen;
            }
            ImGui::EndMenu();
        }

        ImGui::EndMainMenuBar();
    }

    if (mViewer.mViewerOpen) {

        ImGui::Begin("Simulation Parameters");

       

    
        if (ImGui::Button("Start")) {
            mViewer.mRunSimulation = true;
        }

        ImGui::SameLine();

        if (ImGui::Button("Pause")) {
            mViewer.mRunSimulation = false;
        }

        ImGui::SameLine();


        if (ImGui::Button("Reset")) {
            mViewer.mRunSimulation = false;
            mViewer.resetSimulation();
        }

        if (ImGui::CollapsingHeader("Physical Properties", ImGuiTreeNodeFlags_DefaultOpen)) {
            
            ImGui::SliderFloat("Time Step (ms)", &mViewer.mDt,0.1,1.0);
            if (ImGui::SliderFloat("Stiffness", &mViewer.mStiffness, 1.0, 50.0)) {
                mViewer.mSpringForce->setSpringConstant(mViewer.mStiffness);
            }
            if (ImGui::SliderFloat("Damping", &mViewer.mDampen, 1.0, 50.0)) {
                mViewer.mSpringForce->setDampingConstant(mViewer.mDampen);
            }
            if (ImGui::SliderFloat("Gravity", &mViewer.mGravity, 0.5, 10.0)) {
                mViewer.mGravityForce->setGravity(mViewer.mGravity);
            };
            if (ImGui::SliderFloat("Mass", &mViewer.mParticleMass, 0.1, 10.0)) {
                mViewer.mSystem.setParticleMasses(mViewer.mParticleMass);
            }

        }

    


        ImGui::End();
    }

}
