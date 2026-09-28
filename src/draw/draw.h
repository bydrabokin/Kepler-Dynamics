#ifndef DRAW_H
#define DRAW_J
#include "../../src/body.h"

void drawCelestialBodies(Planet *mainPlanets, int numPlanets, MinorBody *mainMinorBodies, int numMinorBodies, Moon *mainMoons, int numMoons, Spacecraft *mainSpacecraft, int numSpacecraft, Camera3D *camera);

void setDrawCordinatesPlanet(Planet *planet);
void setDrawCordinatesMinorBody(Planet *planet);
void setDrawCordinatesMoon(Planet *planet);
void setDrawCordinatesSpacecraft(Planet *planet);

void drawBody(Vector3 pos, Vector3 radius, bool dimensions, Camera3D *camera);

#endif