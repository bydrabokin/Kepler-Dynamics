#include <raylib.h>
#include <stdio.h>
#include <math.h>
#include <string.h>
#include <stdlib.h>

#define SCREEN_HALF_X 900
#define SCREEN_HALF_Y 450
#define screenUnit_2_meter 1e10
#define meter_2_screenUnit 1e-10

#define AU 1.496e+11 //in meters
#define G 6.6743e-11

int targetFps;

typedef struct  {
    double r, θ, φ;
} PolarVector3;

PolarVector3 cameraPolar;


Vector3 polar_2_cartesian(PolarVector3 polar) {
    Vector3 cartesian;
    cartesian.x = polar.r * cosf(polar.φ * DEG2RAD) * cosf(polar.θ * DEG2RAD);
    cartesian.y = polar.r * sinf(polar.φ * DEG2RAD);
    cartesian.z = polar.r * cosf(polar.φ * DEG2RAD) * sinf(polar.θ * DEG2RAD);

    return cartesian;
}

//set initial
void setInitialMiscellanious() {
}

void setIntialCamera(Camera3D *camera) {

    cameraPolar.r = 10;
    cameraPolar.θ = 10;
    cameraPolar.φ = 34;

    camera->position = (Vector3){cameraPolar.r, cameraPolar.θ, cameraPolar.φ} ;
    camera->target = (Vector3){0, 0, 0};
    camera->up = (Vector3){0, 1, 0};

    camera->fovy = 100;
    camera->projection = CAMERA_PERSPECTIVE;
}

void cameraLogic(Camera3D *camera) {
    
    //zoom
    if (GetMouseWheelMove() == 1.0) {
        cameraPolar.r *= 1.2;
    } else if (GetMouseWheelMove() == -1.0) {
        cameraPolar.r *= 0.8;
    }

    //dragging
    if (IsMouseButtonDown(MOUSE_BUTTON_LEFT)) {

        float sensitivity = 0.3;
        Vector2 delta = {GetMouseDelta().x * sensitivity, GetMouseDelta().y * sensitivity};
        cameraPolar.θ += delta.x;
        cameraPolar.φ += delta.y;

        //limits
        if (cameraPolar.θ >= 360)
            cameraPolar.θ -= 360;

        if (cameraPolar.θ < 0)
            cameraPolar.θ += 360;

        if (cameraPolar.φ > 89)
            cameraPolar.φ = 89;

        if (cameraPolar.φ < -89)
            cameraPolar.φ = -89;

        }
    
    camera->position = (Vector3)polar_2_cartesian(cameraPolar);
}


int main() {
    
    //FPS
    //system("python3 DATA/getData.py");
    targetFps = 100;
    SetTargetFPS(targetFps);

    InitWindow(1800, 900, "Kepler Dynamics 🪐");
    
    Camera3D pov = {0};
    
    //set
    setInitialMiscellanious();
    setIntialCamera(&pov);


    while (!WindowShouldClose()) {
        
        cameraLogic(&pov);

        //Drawing
        BeginDrawing();
        ClearBackground(BLACK);

        BeginMode3D(pov);   

        DrawCubeWires((Vector3){0, 0, 0}, 2, 2, 2, RED);
        DrawSphere((Vector3){0, 2, 0}, 1, BLUE);
        
        EndMode3D();

        EndDrawing();

    }

}