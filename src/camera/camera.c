#include <raylib.h>
#include <math.h>
#include "../../src/body/body.h"
#include <stdio.h>


typedef struct  {
    double r, θ, φ;
} PolarVector3;

Vector3 focus = {0, 0, 0};
Vector3 radius = {0, 0, 0};
bool move = false;

double newTheta;
double newPhi;
double startR;
double change = 0;


int stage = 0;

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

    cameraPolar->r = 300;
    cameraPolar->θ = 90;
    cameraPolar->φ = 0;


    camera->target = (Vector3)mainPlanets[0].drawPos;
    camera->position = (Vector3){camera->target.x + polar_2_cartesian(*cameraPolar).x, camera->target.y + polar_2_cartesian(*cameraPolar).y, camera->target.z + polar_2_cartesian(*cameraPolar).z};
    camera->up = (Vector3){0, 1, 0};

    camera->fovy = 100;
    camera->projection = CAMERA_PERSPECTIVE;
}

void cameraLogic(Camera3D *camera, PolarVector3 *cameraPolar) {
    
    //zoom
    if (GetMouseWheelMove() == -1.0) {
        cameraPolar->r *= 1.2;
        move = false;
    } else if (GetMouseWheelMove() == 1.0) {
        cameraPolar->r *= 0.8;
        move = false;
    }

    //dragging
    if (IsMouseButtonDown(MOUSE_BUTTON_LEFT)) {
        move = false;
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
        
    focus = pos;
    radius = radiusInput;
    move = true;

}

void goToFocus(Camera3D *camera,  PolarVector3 *cameraPolar) {
    
    double targetDistanceToObject = (radius.x * GetScreenHeight()) / (2.0 * 100 * tanf(camera->fovy * DEG2RAD / 2.0f));
    
    Vector3 currentPos = camera->position;
    double dy = focus.y - currentPos.y;
    double dx = focus.x - currentPos.x;
    double dz = focus.z - currentPos.z;

    double dx2, dy2, dz2;
    
    if (stage == 0) {
        newTheta = atan2(dz, dx) *RAD2DEG;
        newPhi = atan2(dy, sqrtf(dx*dx+dz*dz)) *RAD2DEG;
    }

    double newR;
    
    double time = 50;
    double lockNum = 0.05;

    double dTheta = cameraPolar->θ-newTheta;
    double dPhi = cameraPolar->φ-newPhi; 
    double dr = cameraPolar->r - targetDistanceToObject+1;

    double saved = cameraPolar->r;

    
    
    if (move) {
        if (dPhi != 0 && dTheta != 0 && stage == 0) {
            dTheta = cameraPolar->θ-newTheta;
            
            if (dTheta > 180.0001)
                dTheta -= 360;
            else if (dTheta < -180.0001)
                dTheta += 360;

            double absTheta = fabs(dTheta);
        
            if (absTheta > lockNum && cameraPolar->θ != newTheta) {
                cameraPolar->θ -= (dTheta/time) * 2;
            } else cameraPolar->θ = newTheta;
            


            dPhi = cameraPolar->φ-newPhi;
            double absPhi = fabs(dPhi);
            
            if (absPhi > lockNum && cameraPolar->φ != newPhi) {
                cameraPolar->φ -= dPhi / time;
                
            }  else cameraPolar->φ = newPhi;
            
            
        } 

        if ((fabs(dPhi) < 1 && fabs(dTheta) < 1) || stage == 1) {
            
            dPhi = 0;
            dTheta = 0;
            if (stage == 0) {
                dx2 = currentPos.x - focus.x;
                dy2 = currentPos.y - focus.y;
                dz2 = currentPos.z - focus.z;
                newPhi = atan2(dy2, sqrt(dx2*dx2 + dz2*dz2)) * RAD2DEG;
                newTheta = atan2(dz2, dx2) * RAD2DEG;
                newR = sqrtf(dx2*dx2+dy2*dy2+dz2*dz2) + saved*2;
                camera->target = focus;
                cameraPolar->θ = newTheta;
                cameraPolar->φ = newPhi;
                cameraPolar->r = newR;
                saved = cameraPolar->r;
                startR = saved - targetDistanceToObject;
                printf("start: %f\n", startR);
            }
            
            
            //printf("current r: %f, target r: %f, new R: %f\n", cameraPolar->r, targetDistanceToObject, newR);
            printf("startR: %f\n", startR);
            double absR = fabs(dr);
            dr = cameraPolar->r - targetDistanceToObject;

            double percentThere = (startR - cameraPolar->r) / (startR- targetDistanceToObject);

            if (startR - dr < 200 || dr < 400) {
                change = 10;
                //printf("20\n");
            } else if (percentThere <= 0.5 ) {
                change += 5;
                printf("+5\n");

            } else if (percentThere > 0.5 && change > 0) {
                change += 5;
                printf("-5\n");

            } else {
                change = 10;
            }

            printf("dr: %f, dr change: %f: %% done: %f\n", dr, change, percentThere);

            if (absR > lockNum && cameraPolar->r != targetDistanceToObject) {
                cameraPolar->r -= change;
                if (cameraPolar->r < targetDistanceToObject) cameraPolar->r = targetDistanceToObject;
                
            }  else cameraPolar->r = targetDistanceToObject;
            
            cameraPolar->θ = newTheta;
            cameraPolar->φ = newPhi;

            stage = 1;


        }

        if (dPhi == 0 && dTheta == 0 && dr == 0) {
            move = false;
            printf("finished\n");
            stage = 0;

            
        }
    }
}