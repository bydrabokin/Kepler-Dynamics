#include <stdio.h>
#include <raylib.h>
#include "../../src/body.h"
#define screenUnit_2_meter 1e10
#define meter_2_screenUnit 1e-10

void drawCelestialBodies(Planet *mainPlanets, int numPlanets, MinorBody *mainMinorBodies, int numMinorBodies, Moon *mainMoons, int numMoons, Spacecraft *mainSpacecraft, int numSpacecraft) {
    int celestialNum = numPlanets + numMinorBodies + numMoons + numSpacecraft;
    int index;

    for (int i = 0; i < celestialNum; i++) {
        if (i < numPlanets) {
            index = i;
            DrawSphere((Vector3)mainPlanets[index].drawPos, mainPlanets[index].drawRadius.x, WHITE);
        } else if (i < numPlanets + numMinorBodies) {
            index = i - numPlanets;
            DrawSphere((Vector3)mainMinorBodies[index].drawPos, mainMinorBodies[index].drawDimensions.x/2.0, BLUE);
        } else if (i < numPlanets + numMinorBodies + numMoons) {
            index = i - (numMinorBodies + numPlanets);
            DrawSphere((Vector3)mainMoons[index].drawPos, mainMoons[index].drawRadius.x, RED);
        } else if (i < celestialNum) {
            index = i - celestialNum + numSpacecraft;
            DrawSphere((Vector3)mainSpacecraft[index].drawPos, mainSpacecraft[index].drawDimensions.x, GREEN);
        }
    }
}

void setDrawCordinatesPlanet(Planet *planet) {
    planet->drawPos = (Vector3){planet->pos.x*meter_2_screenUnit, planet->pos.y*meter_2_screenUnit, planet->pos.z*meter_2_screenUnit};
    planet->drawRadius = (Vector3){planet->radius.x*meter_2_screenUnit, planet->radius.y*meter_2_screenUnit, planet->radius.z*meter_2_screenUnit};
    if (planet->drawRadius.x < 0.5) planet->drawRadius.x = 0.5;
    if (planet->drawRadius.y < 0.5) planet->drawRadius.y = 0.5;
    if (planet->drawRadius.z < 0.5) planet->drawRadius.z = 0.5;
}

void setDrawCordinatesMinorBody(MinorBody *minorBody) {
    minorBody->drawPos = (Vector3){minorBody->pos.x*meter_2_screenUnit, minorBody->pos.y*meter_2_screenUnit, minorBody->pos.z*meter_2_screenUnit};
    minorBody->drawDimensions = (Vector3){minorBody->dimensions.x*meter_2_screenUnit, minorBody->dimensions.y*meter_2_screenUnit, minorBody->dimensions.z*meter_2_screenUnit};
    
    if (minorBody->drawDimensions.x < 0.2) minorBody->drawDimensions.x = 0.2;
    if (minorBody->drawDimensions.y < 0.2) minorBody->drawDimensions.y = 0.2;
    if (minorBody->drawDimensions.z < 0.2) minorBody->drawDimensions.z = 0.2;

}

void setDrawCordinatesMoon(Moon *moon) {
    moon->drawPos = (Vector3){moon->pos.x*meter_2_screenUnit, moon->pos.y*meter_2_screenUnit, moon->pos.z*meter_2_screenUnit};
    moon->drawRadius = (Vector3){moon->radius.x*meter_2_screenUnit, moon->radius.y*meter_2_screenUnit, moon->radius.z*meter_2_screenUnit};

    if (moon->drawRadius.x < 0.4) moon->drawRadius.x = 0.4;
    if (moon->drawRadius.y < 0.4) moon->drawRadius.y = 0.4;
    if (moon->drawRadius.z < 0.4) moon->drawRadius.z = 0.4;
}   

void setDrawCordinatesSpacecraft(Spacecraft *spacecraft) {
    spacecraft->drawPos = (Vector3){spacecraft->pos.x*meter_2_screenUnit, spacecraft->pos.y*meter_2_screenUnit, spacecraft->pos.z*meter_2_screenUnit};
    spacecraft->drawDimensions = (Vector3){spacecraft->dimensions.x*meter_2_screenUnit, spacecraft->dimensions.y*meter_2_screenUnit, spacecraft->dimensions.z*meter_2_screenUnit};
    if (spacecraft->drawDimensions.x < 0.1) spacecraft->drawDimensions.x = 0.1;
    if (spacecraft->drawDimensions.y < 0.1) spacecraft->drawDimensions.y = 0.1;
    if (spacecraft->drawDimensions.z < 0.1) spacecraft->drawDimensions.z = 0.1;
}