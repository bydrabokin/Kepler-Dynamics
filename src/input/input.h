#ifndef INPUT_H
#define INPUT_H
#include "../../src/camera/camera.h"

extern bool typeSelection[4];
extern int indexSelected;

void numbers_2_planets(Camera3D *camera,  PolarVector3 *cameraPolar);
void clickOnBody(Camera3D *camera,  PolarVector3 *cameraPolar);

#endif