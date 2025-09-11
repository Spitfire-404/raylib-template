#include "raylib.h"
#include "myMath.h"
#include <iostream>
#include <vector>

int main() {
    // Initialization
    const int screenWidth = 800;
    const int screenHeight = 450;
    InitWindow(screenWidth, screenHeight, "raylib template window");

    SetTargetFPS(60);

    // Main game loop
    while (!WindowShouldClose()) {
        // Update

        // Draw
        BeginDrawing();
        ClearBackground(RAYWHITE);
        DrawText("Hello, raylib!", 350, 220, 20, LIGHTGRAY);
        EndDrawing();
    }

    // De-Initialization
    CloseWindow();

    return 0;
}