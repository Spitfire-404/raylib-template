#include "raylib.h"
#include "myMath.h"
#include "Renderer.h"
#include <iostream>
#include <vector>

int main() {
    // Initialization
    const int screenWidth = 800;
    const int screenHeight = 450;

    Renderer mainRender;
    mainRender.add(obj3d("test2"));

    InitWindow(screenWidth, screenHeight, "raylib template window");

    SetTargetFPS(60);

    // Main game loop
    while (!WindowShouldClose()) {
        // Update
        
        // Draw
        BeginDrawing();
        
        mainRender.update();
        
        ClearBackground(RAYWHITE);
        DrawText("Hello, raylib!", 350, 220, 20, LIGHTGRAY);
        mainRender.update();




        EndDrawing();
    }

    // De-Initialization
    CloseWindow();

    return 0;
}