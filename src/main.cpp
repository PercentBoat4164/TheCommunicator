#include "gui/gui.h"
#include "backends/imgui_impl_sdl3.h"

int main() {
    // Initialize the GUI
    if (!initializeGUI()) {
        return -1;
    }

    // Main loop
    bool running = true;
    while (running) {
        // Handle events
        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            ImGui_ImplSDL3_ProcessEvent(&event);
            if (event.type == SDL_EVENT_QUIT) {
                running = false;
            }
        }

        // Render the GUI
        renderGUI();
    }

    // Shutdown the GUI
    shutdownGUI();

    return 0;
}