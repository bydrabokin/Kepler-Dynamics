#include <raylib.h>
#include <stdio.h>
#include <math.h>
#include <string.h>

#define SCREEN_HALF_X 900
#define SCREEN_HALF_Y 450

#define AU 1.496e+11 //in meters
#define G 6.6743e-11

int targetFps;

int main() {
    
    //FPS
    targetFps = 100;
    SetTargetFPS(targetFps);

    InitWindow(1800, 900, "Kepler Dynamics 🪐");

    while (!WindowShouldClose()) {
        
        //Drawing
        BeginDrawing();
        ClearBackground(BLACK);

        DrawText("Kepler Dynamics", SCREEN_HALF_X, SCREEN_HALF_Y, 30, WHITE);
        EndDrawing();

    }

}