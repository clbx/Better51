// dear imgui: standalone example application for SDL2 + OpenGL
// If you are new to dear imgui, see examples/README.txt and documentation at the top of imgui.cpp.
// (SDL is a cross-platform general purpose library for handling windows, inputs, OpenGL/Vulkan graphics context creation, etc.)
// (GL3W is a helper library to access OpenGL functions since there is no standard header to access modern OpenGL functions easily. Alternatives are GLEW, Glad, etc.)

#include "imgui.h"
#include "imgui_impl_sdl.h"
#include "imgui_impl_opengl3.h"
#include "imgui_memory_editor.h"
#include "i8051.hpp"
#include <stdio.h>
#include <SDL.h>
#include <GL/gl3w.h>
#include <iostream>


int main(int argc, char** argv){
    // Setup SDL
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER | SDL_INIT_GAMECONTROLLER) != 0){
        printf("Error: %s\n", SDL_GetError());
        return -1;
    }

    const char* glsl_version = "#version 150";
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_FLAGS, SDL_GL_CONTEXT_FORWARD_COMPATIBLE_FLAG); // Always required on Mac
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 2);

    // Create window with graphics context
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
    SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);
    SDL_GL_SetAttribute(SDL_GL_STENCIL_SIZE, 8);
    SDL_WindowFlags window_flags = (SDL_WindowFlags)(SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE | SDL_WINDOW_ALLOW_HIGHDPI);
    SDL_Window* window = SDL_CreateWindow("Better51", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1600, 900, window_flags);
    SDL_GLContext gl_context = SDL_GL_CreateContext(window);
    SDL_GL_MakeCurrent(window, gl_context);
    SDL_GL_SetSwapInterval(1); // Enable vsync

    

    bool err = gl3wInit() != 0;
    if (err){
        fprintf(stderr, "Failed to initialize OpenGL loader!\n");
        return 1;
    }
   
    char* filename;
    if(argc > 1){
        filename = argv[1];        
    }
    


    // Setup Dear ImGui context
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;

    // Setup Dear ImGui style
    ImGui::StyleColorsDark();

    // Setup Platform/Renderer bindings
    ImGui_ImplSDL2_InitForOpenGL(window, gl_context);
    ImGui_ImplOpenGL3_Init(glsl_version);


    ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f); 

    static MemoryEditor ram_edit;
    static MemoryEditor rom_edit;
    i8051 proc;

    bool getLoadBinaryMenu = false;
    bool invalidFile = false;

    proc.load(filename);
    // Main loop
    bool done = false;
    while (!done){
       
        SDL_Event event;
        while (SDL_PollEvent(&event)){
            ImGui_ImplSDL2_ProcessEvent(&event);
            if (event.type == SDL_QUIT)
                done = true;
            if (event.type == SDL_WINDOWEVENT && event.window.event == SDL_WINDOWEVENT_CLOSE && event.window.windowID == SDL_GetWindowID(window))
                done = true;
        }

        

        

        // Start the Dear ImGui frame
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplSDL2_NewFrame(window);
        ImGui::NewFrame();

        //ImGui::ShowDemoWindow();

        if (ImGui::BeginMainMenuBar()){
            if (ImGui::BeginMenu("File")){
                if(ImGui::MenuItem("Load Assembly")){}
                if(ImGui::MenuItem("Save Assembly","CTRL+S")){}
                if(ImGui::MenuItem("Load Binary")){getLoadBinaryMenu = true;}
                if(ImGui::MenuItem("Save Binary","CTRL+S")){}
                if(ImGui::MenuItem("Exit")){return 1;}
                ImGui::EndMenu();
            }
            if (ImGui::BeginMenu("Edit")){
                if (ImGui::MenuItem("Undo", "CTRL+Z")) {}
                if (ImGui::MenuItem("Redo", "CTRL+Y", false, false)) {}  // Disabled item
                ImGui::Separator();
                if (ImGui::MenuItem("Cut", "CTRL+X")) {}
                if (ImGui::MenuItem("Copy", "CTRL+C")) {}
                if (ImGui::MenuItem("Paste", "CTRL+V")) {}
                ImGui::EndMenu();
            }
            ImGui::EndMainMenuBar();
        }

        ImGui::SetNextWindowPos(ImVec2(710,100), ImGuiCond_Once);
        ImGui::SetNextWindowSize(ImVec2(540,175), ImGuiCond_Once);
        ram_edit.DrawWindow("Memory Editor", proc.memory, sizeof(uint8_t)*128);
        ram_edit.HighlightMax = proc.pc;
        ram_edit.HighlightMin = proc.pc;

        ImGui::SetNextWindowSize(ImVec2(540,400), ImGuiCond_Once);
        ImGui::SetNextWindowPos(ImVec2(710,280), ImGuiCond_Once);
        rom_edit.DrawWindow("Program Code Editor", proc.rom, sizeof(uint8_t) * 4096);

        ImGui::SetNextWindowPos(ImVec2(340,100), ImGuiCond_Once);
        ImGui::Begin("Editor");
            static char text[1024 * 16] ="";
            ImGui::InputTextMultiline("##source", text, 1024*64, ImVec2(350, ImGui::GetTextLineHeight() * 42));
        ImGui::End();

        ImGui::SetNextWindowSize(ImVec2(260,60), ImGuiCond_Once);
        ImGui::SetNextWindowPos(ImVec2(75,100), ImGuiCond_Once);
        ImGui::Begin("Control");
            if(ImGui::Button("Step")){
                proc.tick();
            }
            ImGui::SameLine();
            if(ImGui::Button("Reset")){
                proc.reset();
            }
        ImGui::End();

        ImGui::SetNextWindowSize(ImVec2(260,400), ImGuiCond_Once);
        ImGui::SetNextWindowPos(ImVec2(75,160), ImGuiCond_Once);
        ImGui::Begin("Registers");
            ImGui::Text("PC: (%X)",proc.pc);
            ImGui::Text("A: (%X)", proc.a);
            ImGui::Text("B: (%X)",proc.b);
            ImGui::Text("PSW: "BYTE_TO_BINARY_PATTERN, BYTE_TO_BINARY(proc.psw));
        ImGui::End();

        ImGui::SetNextWindowPos(ImVec2(1080,20), ImGuiCond_Once);
        ImGui::Begin("Debug");
        ImVec2 mousePos = ImGui::GetMousePos();
            ImGui::Text("%f, %f",mousePos.x,mousePos.y);
        ImGui::End();

        /* this is broken, please fix me */
        if(getLoadBinaryMenu){
            ImGui::SetNextWindowSize(ImVec2(700,125), ImGuiCond_Once);
            ImGui::SetNextWindowPos(ImVec2(280,20), ImGuiCond_Once);
            ImGui::Begin("Load Binary");
                ImGui::Text("Input the filepath to the binary relative to the exectuable (sorry this will change soon)");
                static char filepath[128] = "";
                ImGui::InputText("Input Filepath",filepath,IM_ARRAYSIZE(filepath));
                ImGui::Text("%s",filepath);
                if(ImGui::Button("Load")){
                    printf("%s\n",filename);
                    bool good = proc.load(filename);
                    if(good){
                        getLoadBinaryMenu = false;
                    }else{
                        invalidFile = true;
                    }
                }
                if(invalidFile){
                    ImGui::TextColored(ImVec4(1.0f,0.0f,0.0f,1.0f), "Invalid File");
                }
            ImGui::End();


             
        }



        // Rendering
        ImGui::Render();
        glViewport(0, 0, (int)io.DisplaySize.x, (int)io.DisplaySize.y);
        glClearColor(clear_color.x, clear_color.y, clear_color.z, clear_color.w);
        glClear(GL_COLOR_BUFFER_BIT);
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
        SDL_GL_SwapWindow(window);
   


    }

    // Cleanup
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplSDL2_Shutdown();
    ImGui::DestroyContext();

    SDL_GL_DeleteContext(gl_context);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}
