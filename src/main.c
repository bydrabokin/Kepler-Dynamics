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


#define SCREEN_HALF_X 900
#define SCREEN_HALF_Y 450
#define screenUnit_2_meter 1e10
#define meter_2_screenUnit 1e-10

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
    loadFiles();
    initData();
    linkTextures(mainPlanets, numPlanets);
    doItwithAllSame(setDrawCordinates);
    setIntialCamera(&pov, &cameraPolar);




    while (!WindowShouldClose()) {
        
        cameraLogic(&pov, &cameraPolar);

        //Drawing
        BeginDrawing();
        ClearBackground(BLACK);

        BeginMode3D(pov);   

        drawCelestialBodies(&pov);

        EndMode3D();

        EndDrawing();

    }

}