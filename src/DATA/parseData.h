#ifndef PARSEDATA_H
#define PARSEDATA_H
#include <raylib.h>
#include "../../src/body.h"
#include <string.h>
#include <stdlib.h>


void readFile(char **wholeJsonStr);

void initData(Planet *mainPlanets, int *numPlanets, MinorBody *mainMinorBodies, int *numMinorBodies, Moon *mainMoons, int *numMoons, Spacecraft *mainSpacecraft, int *numSpacecraft);
#endif