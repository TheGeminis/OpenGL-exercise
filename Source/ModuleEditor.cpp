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
    LOG("Initialazing ImGui with version 440");
    ImGui_ImplOpenGL3_Init("#version 440");
    //IMGUI_CHECKVERSION();

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
    //glViewport(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
    //glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
    //glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    bool* demo = new bool(true);
    ImGui::ShowDemoWindow(demo);
    ConfigurationWindow();
    ImGui::Render();
    
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

    //ImGui_ImplSDL2_ProcessEvent(&event);

    return UPDATE_CONTINUE;
}

update_status ModuleEditor::PostUpdate()
{
    return UPDATE_CONTINUE;
}

void ModuleEditor::ConsoleWindow()
{
    
}


void ModuleEditor::ConfigurationWindow()
{
    bool show_demo_window = true;
    bool show_another_window = false;
    ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);

    static float f = 0.0f;
    static int counter = 0;

    ImGui::Begin("Hello, world!");                          // Create a window called "Hello, world!" and append into it.

    ImGui::Text("This is some useful text.");               // Display some text (you can use a format strings too)
    ImGui::Checkbox("Demo Window", &show_demo_window);      // Edit bools storing our window open/close state
    ImGui::Checkbox("Another Window", &show_another_window);

    ImGui::SliderFloat("float", &f, 0.0f, 1.0f);            // Edit 1 float using a slider from 0.0f to 1.0f
    ImGui::ColorEdit3("clear color", (float*)&clear_color); // Edit 3 floats representing a color

    if (ImGui::Button("Button"))                            // Buttons return true when clicked (most widgets return true when edited/activated)
        counter++;
    ImGui::SameLine();
    ImGui::Text("counter = %d", counter);

    ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
    ImGui::End();
}

// Called before quitting
bool ModuleEditor::CleanUp()
{
    LOG("Destroying Module Editor");

    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplSDL2_Shutdown();
    ImGui::DestroyContext();
    return true;
}