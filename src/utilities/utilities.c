#include <stdio.h>
#include "../../src/body.h"
#include "../../src/draw/draw.h"


void doItwithAllDifferent(void (*functionPlanets)(), void (*functionMinorBodies)(), void (*functionMoons)(), void (*functionSpacecraft)(), Planet *mainPlanets, int numPlanets, MinorBody *mainMinorBodies, int numMinorBodies, Moon *mainMoons, int numMoons, Spacecraft *mainSpacecraft, int numSpacecraft) {
    int celestialNum = numPlanets + numMinorBodies + numMoons + numSpacecraft;
    //printf("%i\n", celestialNum);
    int index;

    for (int i = 0; i < celestialNum; i++) {
        if (i < numPlanets) {
            index = i;
            functionPlanets(&mainPlanets[index]);
            //printf("%s, %f, %f, %f\n",  mainPlanets[index].name, mainPlanets[index].drawPos.x, mainPlanets[index].drawPos.y, mainPlanets[index].drawPos.z);
        } else if (i < numPlanets + numMinorBodies) {
            index = i - numPlanets;
            functionMinorBodies(&mainMinorBodies[index]);
            //printf("%s, %f, %f, %f\n",  mainMinorBodies[index].name, mainMinorBodies[index].drawPos.x, mainMinorBodies[index].drawPos.y, mainMinorBodies[index].drawPos.z);
        } else if (i < numPlanets + numMinorBodies + numMoons) {
            index = i - (numMinorBodies + numPlanets);
            functionMoons(&mainMoons[index]);
            //printf("%s, %f, %f, %f\n",  mainMoons[index].name, mainMoons[index].drawPos.x, mainMoons[index].drawPos.y, mainMoons[index].drawPos.z);
        } else if (i < celestialNum) {
            index = i - numPlanets - numMinorBodies - numMoons;
            functionSpacecraft(&mainSpacecraft[index]);
            printf("%s, %f, %f, %f\n",  mainSpacecraft[index].name, mainSpacecraft[index].drawPos.x, mainSpacecraft[index].drawPos.y, mainSpacecraft[index].drawPos.z);
        }


    }
}

