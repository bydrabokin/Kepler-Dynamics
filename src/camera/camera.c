#include <raylib.h>
#include <math.h>
#include "../../src/body/body.h"
#include "../../src/body/body.h"
#include "../../src/input/input.h"
#include "raymath.h"
#include <stdio.h>

Vector3 focus = {0, 0, 0};
Vector3 radius = {0, 0, 0};

double newTheta;
double newPhi;
double startR;
double change = 0;

int stage = 0;

bool canZoomIn(Camera3D *camera) {
    Vector3 pos;
    double radius;
    
    if (typeSelection[0]) {
        pos = mainPlanets[indexSelected].drawPos;
        radius = mainPlanets[indexSelected].drawRadius.x;
    }
    if (typeSelection[1]) {
        pos = mainMinorBodies[indexSelected].drawPos;
        radius = mainMinorBodies[indexSelected].drawDimensions.x;
    }
    if (typeSelection[2]) {
        pos = mainMoons[indexSelected].drawPos;
        radius = mainMoons[indexSelected].drawRadius.x;
    }
    if (typeSelection[3]) {
        pos = mainSpacecraft[indexSelected].drawPos;
        radius = mainSpacecraft[indexSelected].drawDimensions.x;
    }

    float threshold = radius * 0.25;    
    return Vector3Distance(camera->position, pos) > radius + threshold;
}

double angleDifference(double a, double b) {
    double d = a - b;

    while (d > 180.0)
        d -= 360.0;

    while (d < -180.0)
        d += 360.0;

    return d;
}

Vector3 polar_2_cartesian(PolarVector3 polar) {
    Vector3 cartesian;
    cartesian.x = polar.r * cosf(polar.φ * DEG2RAD) * cosf(polar.θ * DEG2RAD);
    cartesian.y = polar.r * sinf(polar.φ * DEG2RAD);
    cartesian.z = polar.r * cosf(polar.φ * DEG2RAD) * sinf(polar.θ * DEG2RAD);

    return cartesian;
}

PolarVector3 cartesian_2_polar(Vector3 cartesian) {
    PolarVector3 polar;
    polar.r = sqrt(cartesian.x*cartesian.x+cartesian.y*cartesian.y+cartesian.z*cartesian.z);
    polar.θ = atan2(cartesian.y, cartesian.x);
    polar.φ = acos(cartesian.z/polar.r);

    return polar;
}


void setIntialCamera(Camera3D *camera, PolarVector3 *cameraPolar) {

    camera->fovy = 100;
    cameraPolar->r = (mainPlanets[0].drawRadius.x * GetScreenHeight()) / (2 * 100 * tanf(camera->fovy*DEG2RAD/2.0));
    cameraPolar->θ = 90;
    cameraPolar->φ = 0;


    camera->target = (Vector3)mainPlanets[0].drawPos;
    camera->position = (Vector3){camera->target.x + polar_2_cartesian(*cameraPolar).x, camera->target.y + polar_2_cartesian(*cameraPolar).y, camera->target.z + polar_2_cartesian(*cameraPolar).z};
    camera->up = (Vector3){0, 1, 0};

    camera->projection = CAMERA_PERSPECTIVE;
    
    
}


void cameraLogic(Camera3D *camera, PolarVector3 *cameraPolar) {
    
    //zoom
    if (GetMouseWheelMove() == -1.0) {
        cameraPolar->r *= 1.2;
    } else if (GetMouseWheelMove() == 1.0) {
        if (canZoomIn(camera)) cameraPolar->r *= 0.8;
    }
    

    //dragging
    if (IsMouseButtonDown(MOUSE_BUTTON_LEFT)) {
        float sensitivity = 0.2;
        Vector2 delta = {GetMouseDelta().x * sensitivity, GetMouseDelta().y * sensitivity};
        cameraPolar->θ += delta.x;
        cameraPolar->φ += delta.y;

        //limits
        if (cameraPolar->θ >= 360)
            cameraPolar->θ -= 360;

        if (cameraPolar->θ < 0)
            cameraPolar->θ += 360;

        if (cameraPolar->φ > 89)
            cameraPolar->φ = 89;

        if (cameraPolar->φ < -89)
            cameraPolar->φ = -89;

        }
    
    Vector3 offset = polar_2_cartesian(*cameraPolar);
    camera->position.x = camera->target.x + offset.x;
    camera->position.y = camera->target.y + offset.y;
    camera->position.z = camera->target.z + offset.z;

}

void changeFocus(Camera3D *camera,  PolarVector3 *cameraPolar, Vector3 pos, Vector3 radiusInput) {
        
    camera->target = pos;
    double targetRadius = 100;
    double targetDistance = (radiusInput.x * GetScreenHeight()) / (2 * targetRadius * tanf(camera->fovy*DEG2RAD/2.0));
    cameraPolar->r = targetDistance;

}

