#ifndef CAMERA_H
#define CAMERA_H
#include <raylib.h>

typedef struct  {
    double r, θ, φ;
} PolarVector3;

Vector3 polar_2_cartesian(PolarVector3 polar);

void setIntialCamera(Camera3D *camera, PolarVector3 *cameraPolar);

void cameraLogic(Camera3D *camera, PolarVector3 *cameraPolar);



#endif