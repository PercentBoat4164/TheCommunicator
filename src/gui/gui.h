#ifndef GUI_H
#define GUI_H

#include <SDL3/SDL.h>
#include <imgui.h>

// Function declarations
bool initializeGUI();
void renderGUI();
void shutdownGUI();

// External variables for the window and renderer
extern SDL_Window* window;
extern SDL_Renderer* renderer;

#endif // GUI_H