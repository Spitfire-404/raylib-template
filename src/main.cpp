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
    mainRender.add(new obj3d("untitled.obj"));


    InitWindow(screenWidth, screenHeight, "raylib template window");

    SetTargetFPS(60);

    // Main game loop
    while (!WindowShouldClose()) {
        // Update

        // Draw
        mainRender.update(mainRender.CALC);
        BeginDrawing();


        ClearBackground(RAYWHITE);
        DrawText("Hello, raylib!", 350, 220, 20, LIGHTGRAY);
        mainRender.update(mainRender.DRAW);




        EndDrawing();
    }

    // De-Initialization
    CloseWindow();

    return 0;
}
