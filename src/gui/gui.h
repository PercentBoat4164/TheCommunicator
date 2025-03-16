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

// Color palette structure
struct ColorPalette {
    ImVec4 backgroundColor;
    ImVec4 foregroundColor;
    ImVec4 buttonColor;
    ImVec4 textColor;
};

// Function to update the color palette
void updateColorPalette(const ColorPalette& palette);

#endif // GUI_H