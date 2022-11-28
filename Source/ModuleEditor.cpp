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
    ImGuiIO& io = ImGui::GetIO();
    /*io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;
    io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;*/

    ImGui_ImplSDL2_InitForOpenGL(App->window->window, App->renderer->getContext());
    ImGui_ImplOpenGL3_Init("330");

    return true;
}

// Called every draw update
update_status ModuleEditor::Update()
{
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplSDL2_NewFrame(App->window->window);
    
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplSDL2_NewFrame();
    ImGui::NewFrame();

    ImGui::Render();
    glViewport(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
    glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

    //ImGui_ImplSDL2_ProcessEvent(&event);

    return UPDATE_CONTINUE;
}

// Called before quitting
bool ModuleEditor::CleanUp()
{
    return true;
}