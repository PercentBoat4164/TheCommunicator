#include "gui.h"
#include <imgui.h>
#include <backends/imgui_impl_sdl3.h>
#include <backends/imgui_impl_sdlrenderer3.h>
#include <stdio.h>
#include <vector>
#include <string>

// Define the window and renderer
SDL_Window* window = nullptr;
SDL_Renderer* renderer = nullptr;

// Global color palette
ColorPalette globalPalette = {
        ImVec4(0.1f, 0.1f, 0.1f, 1.0f), // Background color
        ImVec4(0.2f, 0.2f, 0.2f, 1.0f), // Foreground color
        ImVec4(0.3f, 0.3f, 0.3f, 1.0f), // Button color
        ImVec4(1.0f, 1.0f, 1.0f, 1.0f)  // Text color
};

// Function to update the color palette
void updateColorPalette(const ColorPalette& palette) {
    globalPalette = palette;
    ImGui::GetStyle().Colors[ImGuiCol_WindowBg] = palette.backgroundColor;
    ImGui::GetStyle().Colors[ImGuiCol_FrameBg] = palette.foregroundColor;
    ImGui::GetStyle().Colors[ImGuiCol_Button] = palette.buttonColor;
    ImGui::GetStyle().Colors[ImGuiCol_Text] = palette.textColor;
}

bool initializeGUI() {
    // Initialize SDL
    ///if (SDL_Init(SDL_INIT_VIDEO) != 0) {
    ///    printf("Error: SDL_Init(): %s\n", SDL_GetError());
    ///    return false;
    ///}

    // Create a window
    window = SDL_CreateWindow("The Communicator", 1280, 720, SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE);
    if (!window) {
        printf("Error: SDL_CreateWindow(): %s\n", SDL_GetError());
        SDL_Quit();
        return false;
    }

    // Create a renderer
    renderer = SDL_CreateRenderer(window, nullptr);
    if (!renderer) {
        printf("Error: SDL_CreateRenderer(): %s\n", SDL_GetError());
        SDL_DestroyWindow(window);
        SDL_Quit();
        return false;
    }
    SDL_SetRenderVSync(renderer, 1);

    // Initialize ImGui
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGui::StyleColorsDark();

    // Initialize ImGui backends
    ImGui_ImplSDL3_InitForSDLRenderer(window, renderer);
    ImGui_ImplSDLRenderer3_Init(renderer);

    // Set initial color palette
    updateColorPalette(globalPalette);

    return true;
}

void renderGUI() {
    // Start a new ImGui frame
    ImGui_ImplSDLRenderer3_NewFrame();
    ImGui_ImplSDL3_NewFrame();
    ImGui::NewFrame();

    // Main window layout
    // Set the main window to fill the entire screen
    ImGui::SetNextWindowPos(ImVec2(0, 0)); // Position at the top-left corner
    ImGui::SetNextWindowSize(ImGui::GetIO().DisplaySize); // Fill the entire window

    ImGui::Begin("Main Window", nullptr,
                 ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoBringToFrontOnFocus);

    // Left panel for conversation threads (20% of the width)
    ImGui::BeginChild("Conversation Threads", ImVec2(ImGui::GetContentRegionAvail().x * 0.2f,
                      ImGui::GetContentRegionAvail().y - 100), true,
                      ImGuiWindowFlags_HorizontalScrollbar);
    static std::vector<std::string> threads = {"Thread 1", "Thread 2", "Thread 3", "Thread 4", "Thread 5", "Thread 6", "Thread 7", "Thread 8", "Thread 9", "Thread 10"};
    static int selectedThread = 0;
    for (int i = 0; i < threads.size(); i++) {
        if (ImGui::Selectable(threads[i].c_str(), selectedThread == i)) {
            selectedThread = i;
        }
    }
    ImGui::EndChild();

    // Right panel for selected conversation thread (80% of the width)
    ImGui::SameLine();
    ImGui::BeginChild("Selected Thread", ImVec2(0, ImGui::GetContentRegionAvail().y - 100),
                      true);
    ImGui::Text("Selected Thread: %s", threads[selectedThread].c_str());
    ImGui::Text("This is where the conversation will be displayed.");
    ImGui::EndChild();

    // Bottom section: Text entry box, send button, and color palette dropdown
    ImGui::BeginChild("Bottom Section", ImVec2(0, 100), true);

    // Text input area with its own scrollbar
    ImGui::BeginChild("Text Input Scroll", ImVec2(-1, -30), true); // Leave space for the button and color palette
    static char textInput[1024] = "";
    ImGui::InputTextMultiline("##Input", textInput, IM_ARRAYSIZE(textInput), ImVec2(-1, -1));
    ImGui::EndChild();

    // Columns for send button and color palette dropdown
    ImGui::BeginChild("Button and Palette", ImVec2(0, 100), false); // Fixed height for the button and palette

    // Send button in the first column
    if (ImGui::Button("Send", ImVec2(80, 0))) {
        // Handle send button click
        printf("Send button clicked: %s\n", textInput);
        textInput[0] = '\0'; // Clear the input box
    }
    ImGui::SameLine(); //Place two items on the same row
    // Color palette dropdown in the second column
    if (ImGui::CollapsingHeader("Color Palette")) {
        if (ImGui::ColorEdit3("Background Color", (float*)&globalPalette.backgroundColor)) {
            updateColorPalette(globalPalette);
        }
        if (ImGui::ColorEdit3("Foreground Color", (float*)&globalPalette.foregroundColor)) {
            updateColorPalette(globalPalette);
        }
        if (ImGui::ColorEdit3("Button Color", (float*)&globalPalette.buttonColor)) {
            updateColorPalette(globalPalette);
        }
        if (ImGui::ColorEdit3("Text Color", (float*)&globalPalette.textColor)) {
            updateColorPalette(globalPalette);
        }
    }

    ImGui::EndChild(); // End of Button and Palette child window

    ImGui::EndChild(); // End of Bottom Section

    ImGui::End(); // End of Main Window

    // Render the ImGui frame
    ImGui::Render();
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);
    ImGui_ImplSDLRenderer3_RenderDrawData(ImGui::GetDrawData(), renderer);
    SDL_RenderPresent(renderer);
}
void shutdownGUI() {
    // Cleanup ImGui backends
    ImGui_ImplSDLRenderer3_Shutdown();
    ImGui_ImplSDL3_Shutdown();
    ImGui::DestroyContext();

    // Cleanup SDL
    if (renderer) {
        SDL_DestroyRenderer(renderer);
    }
    if (window) {
        SDL_DestroyWindow(window);
    }
    SDL_Quit();
}