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
    mainRender.add(obj3d("test1"));
    mainRender.add(obj3d("test2"));
    mainRender.add(obj3d("test3"));
    mainRender.add(obj3d("test4"));
    mainRender.add(obj3d("test5"));
    mainRender.add(obj3d("test6"));
    mainRender.add(obj3d("test7"));
    mainRender.add(obj3d("test8"));
    mainRender.add(obj3d("test9"));
    mainRender.add(obj3d("test10"));
    

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