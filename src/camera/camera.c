#include <raylib.h>
#include <math.h>

typedef struct  {
    double r, θ, φ;
} PolarVector3;

Vector3 polar_2_cartesian(PolarVector3 polar) {
    Vector3 cartesian;
    cartesian.x = polar.r * cosf(polar.φ * DEG2RAD) * cosf(polar.θ * DEG2RAD);
    cartesian.y = polar.r * sinf(polar.φ * DEG2RAD);
    cartesian.z = polar.r * cosf(polar.φ * DEG2RAD) * sinf(polar.θ * DEG2RAD);

    return cartesian;
}

void setIntialCamera(Camera3D *camera, PolarVector3 *cameraPolar) {

    cameraPolar->r = 100;
    cameraPolar->θ = 90;
    cameraPolar->φ = 0;

    camera->position = (Vector3){cameraPolar->r, cameraPolar->θ, cameraPolar->φ} ;
    camera->target = (Vector3){0, 0, 0};
    camera->up = (Vector3){0, 1, 0};

    camera->fovy = 100;
    camera->projection = CAMERA_PERSPECTIVE;
}

void cameraLogic(Camera3D *camera, PolarVector3 *cameraPolar) {
    
    //zoom
    if (GetMouseWheelMove() == 1.0) {
        cameraPolar->r *= 1.2;
    } else if (GetMouseWheelMove() == -1.0) {
        cameraPolar->r *= 0.8;
    }

    //dragging
    if (IsMouseButtonDown(MOUSE_BUTTON_LEFT)) {

        float sensitivity = 0.3;
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
    
    camera->position = (Vector3)polar_2_cartesian(*cameraPolar);
}
