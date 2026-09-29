#ifndef DRAW_H
#define DRAW_J
#include "../../src/body/body.h"


void drawCelestialBodies(Camera3D *camera);

void setDrawCordinates(Vector3 pos, Vector3 radius, Vector3 *drawPos, Vector3 *drawRadius);

void drawBody(Camera3D *camera, int fontsize, char *bodyType, int i);

Color getaverageColor(Texture2D texture);

#endif
