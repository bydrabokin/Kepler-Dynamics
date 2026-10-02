#include <stdio.h>
#include <raylib.h>
#include <string.h>
#include <math.h>
#include "../../src/body/body.h"
#include "../../src/utilities/utilities.h"
#include "raymath.h"
#define screenUnit_2_meter 1e7
#define meter_2_screenUnit 1e-7


void drawBody(Camera3D *camera, int fontsize, char *bodyType, int i) {

    Vector3 pos, radius;
    double rad;
    double multiplier;
    Color color;
    char name[128];

    if (!strcmp(bodyType, "planet")) {
        pos = mainPlanets[i].drawPos;
        radius = mainPlanets[i].drawRadius;
        rad = 6;
        multiplier = 1.0;
        color = mainPlanets[i].color;
        strcpy(name, mainPlanets[i].name);
    } else if (!strcmp(bodyType, "minorBody")) {
        pos = mainMinorBodies[i].drawPos;
        radius = mainMinorBodies[i].drawDimensions;
        rad = 4;
        multiplier = 0.5;
        color = GRAY;   
        strcpy(name, mainMinorBodies[i].name);
    } else if (!strcmp(bodyType, "moon")) {
        pos = mainMoons[i].drawPos;
        radius = mainMoons[i].drawRadius;
        rad = 2;
        multiplier = 1.0;
        color = RED;
        strcpy(name, mainMoons[i].name);
    } else if (!strcmp(bodyType, "spacecraft")) {
        pos = mainSpacecraft[i].drawPos;
        radius = mainSpacecraft[i].drawDimensions;
        rad = 3;
        multiplier = 0.5;
        color = DARKGRAY;
        strcpy(name, mainSpacecraft[i].name);
    }

    Vector2 screenCordinates = (Vector2){GetWorldToScreen(pos, *camera).x, GetWorldToScreen(pos, *camera).y};
    Vector2 screenPlanet;
    double dx, dy, distance;
    double opacity = 255;
    bool draw = true;

    if (!strcmp(bodyType, "moon")) { 
        
        char *orbiting = mainMoons[i].bodyOrbiting;
        
        for (int planet = 0; planet < numPlanets; planet++) {
            if (!strcmp(mainPlanets[planet].name, orbiting)) {
                screenPlanet = (Vector2){GetWorldToScreen(mainPlanets[planet].drawPos, *camera).x, GetWorldToScreen(mainPlanets[planet].drawPos, *camera).y};
                break;
            }
        }
        
        dx = screenCordinates.x - screenPlanet.x;
        dy = screenCordinates.y - screenPlanet.y;
        distance = sqrt(dx*dx + dy*dy); 


        if (distance < 20) draw = false;
        if (distance < 40) opacity = ((distance - 20) / 20) * 255;


        
    }
    
    double distanceToObject = Vector3Distance(camera->position, pos);
    double projectedRadius = (radius.x*multiplier / (distanceToObject * tanf(camera->fovy * DEG2RAD / 2.0f))) * (GetScreenHeight() / 2.0f);
    
    if (projectedRadius > rad) {
        draw = false;
    } 

    
    EndMode3D();
    Vector2 textPos = {screenCordinates.x + fontsize/2.0, screenCordinates.y - fontsize/1.5};
    
    if (draw) {

        DrawTextEx(SpaceFont, name, textPos, fontsize, 1, (Color){color.r, color.g, color.b, opacity});
        DrawCircleLines(screenCordinates.x, screenCordinates.y, rad, (Color){color.r, color.g, color.b, opacity});
        
    }
    
    BeginMode3D(*camera);
    
    DrawSphere(pos, radius.x*multiplier, (Color){color.r, color.g, color.b, opacity});
}

void drawCelestialBodies(Camera3D *camera) {
    int celestialNum = numPlanets + numMinorBodies + numMoons + numSpacecraft;
    int index;

    for (int i = 0; i < celestialNum; i++) {
        if (i < numPlanets) {
            index = i;
            drawBody(camera, 24, mainPlanets[index].type, index);
        } else if (i < numPlanets + numMinorBodies) {
            index = i - numPlanets;
            drawBody(camera, 14, mainMinorBodies[index].type, index);
        } else if (i < numPlanets + numMinorBodies + numMoons) {
            index = i - (numMinorBodies + numPlanets);
            drawBody(camera, 18, mainMoons[index].type, index);
        } else if (i < celestialNum) {
            index = i - celestialNum + numSpacecraft;
            drawBody(camera, 16, mainSpacecraft[index].type, index);
        }
    }
}


void setDrawCordinates(Vector3 pos, Vector3 radius, Vector3 *drawPos, Vector3 *drawRadius) {
    *drawPos = (Vector3){pos.x*meter_2_screenUnit, pos.y*meter_2_screenUnit, pos.z*meter_2_screenUnit};
    *drawRadius = (Vector3){radius.x*meter_2_screenUnit, radius.y*meter_2_screenUnit, radius.z*meter_2_screenUnit};
}

Color getaverageColor(Texture2D texture) {
    Image image = LoadImageFromTexture(texture);
    Color *colors = LoadImageColors(image);
    Vector2 dimensions = {image.width, image.height};
    int stepsizex = dimensions.x / 20;
    int stepsizey = dimensions.y / 20;

    Vector4 totalRGB = {0, 0, 0, 0};
    int i = 0;

    for (int x = 0; x < dimensions.x; x += stepsizex) {
        for (int y = 0; y < dimensions.y; y += stepsizey) {
            int index = (y * image.width) + x;
            Color pixelColor = colors[index];
            totalRGB.x += pixelColor.r;
            totalRGB.y += pixelColor.g;
            totalRGB.z += pixelColor.b;
            totalRGB.w += pixelColor.a;
            i++;

        }
    }

    double saturation = 1.3;
    UnloadImageColors(colors); 
    UnloadImage(image);        

    Color avgColor = {totalRGB.x/i, totalRGB.y/i, totalRGB.z/i, totalRGB.w/i};

    Vector3 hsv = ColorToHSV(avgColor);

    hsv.y *= saturation;

    if (hsv.y > 1.0f)
        hsv.y = 1.0f;

    avgColor = ColorFromHSV(hsv.x, hsv.y, hsv.z);

    return avgColor;
}