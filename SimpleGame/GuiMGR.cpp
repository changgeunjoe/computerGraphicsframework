#include "stdafx.h"
#include "GUIMgr.h"


GUIMgr& GUIMgr::GetInstance()
{
    static GUIMgr mgr{};
    return mgr;
}

void GUIMgr::Init()
{
    gui_context = ImGui::CreateContext();
    ImGui::SetCurrentContext(gui_context);

    ImGui_ImplGLUT_InstallFuncs();
    ImGui_ImplGLUT_Init();
    ImGui_ImplOpenGL3_Init();
    ImGui_ImplOpenGL3_CreateFontsTexture();
    ImGui_ImplOpenGL3_CreateDeviceObjects();
}

void GUIMgr::Render()
{
    ImGui_ImplGLUT_NewFrame();
    ImGui::NewFrame();

    // ImGui 사용 코드
    ImGui::Begin("Hi");
    ImGui::Text("This is a sample ImGui window.");
  /*  if (ImGui::ColorEdit4("clear color", glm::value_ptr(Core::GetInstance().GetBackGroundColor()))) {
        auto& m_clearColor = Core::GetInstance().GetBackGroundColor();
        glClearColor(m_clearColor.x, m_clearColor.y, m_clearColor.z, 1);
    }*/
    ImGui::End();


    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

GUIMgr::~GUIMgr()
{
    ImGui_ImplOpenGL3_DestroyFontsTexture();
    ImGui_ImplOpenGL3_DestroyDeviceObjects();

    ImGui_ImplGLUT_Shutdown();
    ImGui_ImplOpenGL3_Shutdown();
}