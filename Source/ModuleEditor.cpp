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
{
}

// Destructor
ModuleEditor::~ModuleEditor()
{
}

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
    LOG("Initialazing ImGui with version 440");
    ImGui_ImplOpenGL3_Init("#version 440");

    fps_log = new float[60];
    ms_log = new float[60];
    fps_offset = 0;

    timer.StartMilliseconds();

    return true;
}

update_status ModuleEditor::PreUpdate()
{
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplSDL2_NewFrame(App->window->window);
    ImGui::NewFrame();

    return UPDATE_CONTINUE;
}

// Called every draw update
update_status ModuleEditor::Update()
{
    bool* demo = new bool(true);
    ImGui::ShowDemoWindow(demo);
    ConfigurationWindow();
    AboutWindow();
    ImGui::Render();
    
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

    if (quit_button) return UPDATE_STOP;

    return UPDATE_CONTINUE;
}

update_status ModuleEditor::PostUpdate()
{
    return UPDATE_CONTINUE;
}

void ModuleEditor::ConsoleWindow()
{
    
}


void ModuleEditor::AboutWindow()
{
    ImGui::Begin("About");

    ImGui::Text("Geometry Viewer developed for the first assaignment of the \"Advanced Programming for AAA Video Games\" master's degree.");
    ImGui::Text("Author: Jan Marc Costa");
    ImGui::Separator();
    ImGui::Text("General Info:");
    ImGui::BulletText("SDL 2.0");
    ImGui::BulletText("glew 2.1.0");
    ImGui::BulletText("imgui 1.88");
    ImGui::BulletText("MathGeoLib 1.5");
    ImGui::Separator();
    if (ImGui::Button("GitHub")) App->RequestBrowser();
    if (ImGui::Button("Quit")) quit_button = true;

    ImGui::End();
}


void ModuleEditor::ConfigurationWindow()
{
    ms_log[fps_offset] = timer.ReadMilliseconds();
    fps_log[fps_offset] = 1000 / ms_log[fps_offset];
    timer.StartMilliseconds();

    ImGui::Begin("Configuration"); 
    ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / fps_log[fps_offset], fps_log[fps_offset]);

    //Framerate and Milliseconds Histograms
    char title[25];
    sprintf_s(title, 25, "Framerate %.1f", fps_log[fps_offset]);
    ImGui::PlotHistogram("##framerate", &fps_log[0], 60, fps_offset, title, 0.0f, 200.0f, ImVec2(310, 100));
    sprintf_s(title, 25, "Milliseconds %.1f", ms_log[fps_offset]);
    ImGui::PlotHistogram("##framerate", &ms_log[0], 60, fps_offset, title, 0.0f, 20.0f, ImVec2(310, 100));
    
    //Hardware information
    ImGui::Separator();
    ImGui::Text("Hardware information");
    char value[75];
    sprintf_s(value, 75, "%i (Cache: %ikb)", SDL_GetCPUCount(), SDL_GetCPUCacheLineSize());
    ImGui::Text("CPUs: ");				
    ImGui::SameLine(); 
    ImGui::TextColored(ImVec4(0.0f, 1.0f, 0.0f, 1.0f), value);
    sprintf_s(value, 75, "%iMb", SDL_GetSystemRAM());
    ImGui::Text("System RAM: ");		
    ImGui::SameLine(); 
    ImGui::TextColored(ImVec4(0.0f, 1.0f, 0.0f, 1.0f), value);
    sprintf_s(value, 75, "");
    sprintf_s(value, 75, "%s", glGetString(GL_RENDERER));
    ImGui::Text("GPU Model: ");
    ImGui::SameLine(); 
    ImGui::TextColored(ImVec4(0.0f, 1.0f, 0.0f, 1.0f), value);
    sprintf_s(value, 75, "%s", glGetString(GL_VENDOR));
    //ImGui::Text("GPU Brand: ");				
    //ImGui::SameLine(); 
    //ImGui::TextColored(ImVec4(0.0f, 1.0f, 0.0f, 1.0f), value);

    //TODO: Get CPU Model

    //Software information
    SDL_version linked;
    SDL_GetVersion(&linked);
    ImGui::Separator();
    ImGui::Text("Software information");
    ImGui::Text("SDL Version: %i.%i.%i", linked.major, linked.minor, linked.patch);
    sprintf_s(value, 75, "%i", GL_VERSION);
    ImGui::Text("OpenGL version: ");
    ImGui::SameLine(); 
    ImGui::TextColored(ImVec4(0.0f, 1.0f, 0.0f, 1.0f), value);

    //TODO: Get DevIL Version
    //TODO: DirectXTex Version

    ImGui::End();

    fps_offset++;
    if (fps_offset > 59) fps_offset = 0;
}

// Called before quitting
bool ModuleEditor::CleanUp()
{
    LOG("Destroying Module Editor");

    delete fps_log;
    delete ms_log;

    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplSDL2_Shutdown();
    ImGui::DestroyContext();
    return true;
}