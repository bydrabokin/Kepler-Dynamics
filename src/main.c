#include <raylib.h>
#include <stdio.h>
#include <math.h>
#include <string.h>
#include <stdlib.h>
#include "cJSON.h"
#include "../src/body/body.h"
#include "../src/DATA/parseData.h"
#include "../src/utilities/utilities.h"
#include "../src/draw/draw.h"
#include "../src/camera/camera.h"
#include "../src/input/input.h"

#define SCREEN_HALF_X 900
#define SCREEN_HALF_Y 450
#define screenUnit_2_meter 1e7
#define meter_2_screenUnit 1e-7

#define AU 1.496e+11 //in meters
#define G 6.6743e-11

int targetFps;
PolarVector3 cameraPolar;

Planet mainPlanets[256];
int numPlanets;

MinorBody mainMinorBodies[256];
int numMinorBodies;

Moon mainMoons[256];
int numMoons;

Spacecraft mainSpacecraft[256];
int numSpacecraft;

int main() {
    
    //FPS
    //system("python3 DATA/getData.py");
    targetFps = 100;
    SetTargetFPS(targetFps);
    InitWindow(1800, 900, "Kepler Dynamics 🪐");
    Model voyager = LoadModel("../assets/spacecraft/Juno.glb");
    
    Camera3D pov = {0};
    
    //set
    initData();
    loadExtra();
    doItwithAllSame(setDrawCordinates);
    setIntialCamera(&pov, &cameraPolar);
    


    while (!WindowShouldClose()) {
        
        cameraLogic(&pov, &cameraPolar);
        
        numbers_2_planets(&pov, &cameraPolar);
        clickOnBody(&pov, &cameraPolar);

        //Drawing
        BeginDrawing();
        ClearBackground(BLACK);

        
        
        if (framesticked <= 5) {
            DrawTexturePro(BackgroundRaw, (Rectangle){0, 0, BackgroundRaw.width, BackgroundRaw.height}, (Rectangle){0, 0, 1800, 900}, (Vector2){0, 0}, 0, WHITE);            
            printf("background\n");
        }

        if (framesticked == 0) {
            loadFont();
            DrawTextEx(SpaceFont, "Loading Planets...", (Vector2){middle.x - 200, middle.y - 50}, 45, 1, WHITE);
        } else if (framesticked == 1) {
            loadPlanets();
            DrawTextEx(SpaceFont, "Loading Moons...", (Vector2){middle.x - 200, middle.y - 50}, 45, 1, WHITE);
        } else if (framesticked == 2) {
            loadMoons();
            DrawTextEx(SpaceFont, "Loading Minor Bodies...", (Vector2){middle.x - 200, middle.y - 50}, 45, 1, WHITE);
        } else if (framesticked == 3) {
            loadMinorBodies();
            DrawTextEx(SpaceFont, "Loading Spacecraft...", (Vector2){middle.x - 200, middle.y - 50}, 45, 1, WHITE);
        } else if (framesticked == 4) {
            loadSpacecraft();
            DrawTextEx(SpaceFont, "Linking Textures...", (Vector2){middle.x - 200, middle.y - 50}, 45, 1, WHITE);
        } else if (framesticked == 5) {
            linkTextures();
        }

        BeginMode3D(pov);   
        
        if (framesticked > 5) drawCelestialBodies(&pov);

        EndMode3D();

        EndDrawing();

        printf("CAMERA: (x: %f, y: %f, z: %f) r: %f, theta: %f, psi: %f Center: (x: %f, y: %f, z: %f)\n", pov.position.x, pov.position.y, pov.position.z, cameraPolar.r, cameraPolar.θ, cameraPolar.φ, pov.target.x, pov.target.y, pov.target.z);
        framesticked++;
    }

}