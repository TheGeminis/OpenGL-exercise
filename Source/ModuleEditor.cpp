#include "Globals.h"
#include "Application.h"
#include "ModuleWindow.h"
#include "ModuleRender.h"
#include "ModuleEditor.h"
#include "SDL/include/SDL.h"
#include <GL\glew.h>
#include "libs/imgui/imgui.h"
#include "libs/imgui/imgui_impl_opengl3.h"
#include "libs/imgui/imgui_impl_sdl.h"

ModuleEditor::ModuleEditor()
{}

// Destructor
ModuleEditor::~ModuleEditor()
{}

// Called before render is available
bool ModuleEditor::Init()
{
    ImGui::CreateContext();
    //set up some flags:
    LOG("Configuring ImGui io flags")
    ImGuiIO& io = ImGui::GetIO(); (void)io;
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;       // Enable Keyboard Controls
    //io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls
    io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;           // Enable Docking
    io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;         // Enable Multi-Viewport / Platform Windows

    LOG("Initialazing ImplSDL2_InitForOpenGL with window and context");
    ImGui_ImplSDL2_InitForOpenGL(App->window->window, App->renderer->getContext());
    LOG("Initialazing ImGui with version 460");
    ImGui_ImplOpenGL3_Init("#version 460");
    //IMGUI_CHECKVERSION();

    return true;
}

update_status ModuleEditor::PreUpdate()
{
    ImGui_ImplOpenGL3_NewFrame(); //******ALGO PETA AQUI!!!****** : 
    //<Source:API> <Type:Other> <Severity:low> <ID:131216> <Message:Program/shader state info: GLSL program 12 failed to link>
    //<Source:API> <Type:Error> <Severity:high> <ID:1282> <Message:GL_INVALID_OPERATION error generated. <program> object is not successfully linked, or is not a program object.>
    
    ImGui_ImplSDL2_NewFrame(App->window->window);
    ImGui::NewFrame();

    return UPDATE_CONTINUE;
}

// Called every draw update
update_status ModuleEditor::Update()
{
    //glViewport(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
    //glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
    //glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    bool* demo = new bool(true);
    ImGui::ShowDemoWindow(demo);
    ImGui::Render();
    
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData()); //******ALGO PETA AQUI!!!****** : 
    //<Source:API> <Type:Error> <Severity:high> <ID:1282> <Message:GL_INVALID_OPERATION error generated. <program> has not been linked, or is not a program object.>
    //<Source:API> <Type:Error> <Severity:high> <ID:1282> <Message:GL_INVALID_OPERATION error generated. <program> object is not successfully linked, or is not a program object.>
    //<Source:API> <Type:Error> <Severity:high> <ID:1282> <Message:GL_INVALID_OPERATION error generated. No active program.>
    //<Source:API> <Type:Error> <Severity:high> <ID:1281> <Message:GL_INVALID_VALUE error generated. <index> out of range.>

    //ImGui_ImplSDL2_ProcessEvent(&event);

    return UPDATE_CONTINUE;
}

update_status ModuleEditor::PostUpdate()
{
    return UPDATE_CONTINUE;
}

// Called before quitting
bool ModuleEditor::CleanUp()
{
    return true;
}