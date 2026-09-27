#ifndef UTILITIES_H
#define UTILITIES_H
#include "../../src/body.h"


void doItwithAllDifferent(void (*functionPlanets)(), void (*functionMinorBodies)(), void (*functionMoons)(), void (*functionSpacecraft)(), Planet *mainPlanets, int numPlanets, MinorBody *mainMinorBodies, int numMinorBodies, Moon *mainMoons, int numMoons, Spacecraft *mainSpacecraft, int numSpacecraft);


#endif