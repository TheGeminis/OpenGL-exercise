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
    //io.ConfigFlags |= … - imgui.h

    ImGui_ImplSDL2_InitForOpenGL(App->window->window, App->renderer->getContext());
    ImGui_ImplOpenGL3_Init("330");

    return true;
}

// Called every draw update
update_status ModuleEditor::Update()
{
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplSDL2_NewFrame(App->window->window);
    ImGui::NewFrame();

    return UPDATE_CONTINUE;
}

// Called before quitting
bool ModuleEditor::CleanUp()
{
    return true;
}