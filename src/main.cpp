#include "raylib.h"
#include "myMath.h"
#include "Renderer.h"
#include <cmath>
#include <thread>
#include <atomic>
#include <vector>

int main() {
    // Initialization
    const int screenWidth = 800;
    const int screenHeight = 450;


    Renderer mainRender;
    mainRender.add(new obj3d("untitled.obj", 0,0,50));
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
        // random crap for testing
        mainRender.renderList[0]->pos.x = 40*std::sin(GetTime());
        mainRender.renderList[0]->pos.y = 40*std::cos(GetTime());
        mainRender.renderList[0]->pos.z = 4* std::sin(GetTime()*4)+50;

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
