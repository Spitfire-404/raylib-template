#include "raylib.h"
#include "myMath.h"
#include "Renderer.h"
#include <iostream>
#include <thread>
#include <atomic>
#include <vector>

int main() {
    // Initialization
    const int screenWidth = 800;
    const int screenHeight = 450;


    Renderer mainRender;
    mainRender.add(new obj3d("untitled.obj", 0,0,0));
    mainRender.renderList[0]->scale(10);


    InitWindow(screenWidth, screenHeight, "raylib template window");

    SetTargetFPS(60);

    // Main game loop

    std::atomic<bool> running{true};

    std::thread calculationThread([&mainRender, &running]() {
        while (running.load()) {
            mainRender.update(Renderer::CALC);
        }
    });

    while (!WindowShouldClose()) {
        // Update

        // Draw
        BeginDrawing();


        ClearBackground(RAYWHITE);
        mainRender.update(mainRender.DRAW);



        EndDrawing();
    }

    // De-Initialization
    running.store(false);
    calculationThread.join();

    CloseWindow();
    return 0;
}
