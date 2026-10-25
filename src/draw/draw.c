#include <stdio.h>
#include <raylib.h>
#include <string.h>
#include <math.h>
#include "../../src/body/body.h"
#include "../../src/utilities/utilities.h"
#include "../../src/input/input.h"
#include "raymath.h"
#define screenUnit_2_meter 5e6
#define meter_2_screenUnit 5e-6


double nameTagDrawCondtions(Camera3D *camera, char *name, char *bodyType, char *orbiting, Vector2 pos, int fontsize, Vector2 textPos) {
    double opacity = 255;
    double threshold = 80;
    double threshold2 = 20;
    double minDistance = threshold;
    double dx1, dx2, dy1, dy2, distance, distance1, distance2;

    Vector2 textSize = MeasureTextEx(SpaceFont, name, fontsize, 1);
    Vector2 textCenter = {textPos.x + textSize.x/2.0, textPos.y + textSize.y/2.0};

    if (strcmp(bodyType, "moon") == 0) {
        if (typeSelection[0] == true && strcmp(orbiting, mainPlanets[indexSelected].name) == 0) {
            
            dx1 = textCenter.x - 900;
            dy1 = textCenter.y - 450;
            distance1 = sqrtf(dx1*dx1+dy1*dy1);

            dx2 = pos.x - 900;
            dy2 = pos.y - 450;
            distance2 = sqrtf(dx2*dx2+dy2*dy2);

            distance = fmin(distance1, distance2);

            opacity = (fmin(fmax(distance - threshold2, 0), threshold - threshold2) / (threshold - threshold2)) * 255;
        } else {
            opacity = 0;
        }
    } else if (strcmp(bodyType, "spacecraft") == 0) {
        for (int i = 0; i < numPlanets; i++) {
            Vector2 screenCordsPlanet = GetWorldToScreen(mainPlanets[i].drawPos, *camera);
            dx1 = textCenter.x - screenCordsPlanet.x;
            dy1 = textCenter.y - screenCordsPlanet.y;
            distance1 = sqrtf(dx1*dx1+dy1*dy1);

            dx2 = pos.x - screenCordsPlanet.x;
            dy2 = pos.y - screenCordsPlanet.y;
            distance2 = sqrtf(dx2*dx2+dy2*dy2);

            distance = fmin(distance1, distance2);
            minDistance = fmin(minDistance, distance);

        } 

        for (int i = 0; i < numSpacecraft; i++) {

            if (strcmp(mainSpacecraft[i].name, name) == 0) break;

            Vector2 screenCordsPlanet = GetWorldToScreen(mainSpacecraft[i].drawPos, *camera);
            threshold = 60;
            threshold2 = 15;

            dx1 = textCenter.x - screenCordsPlanet.x;
            dy1 = textCenter.y - screenCordsPlanet.y;
            distance1 = sqrtf(dx1*dx1+dy1*dy1);

            dx2 = pos.x - screenCordsPlanet.x;
            dy2 = pos.y - screenCordsPlanet.y;
            distance2 = sqrtf(dx2*dx2+dy2*dy2);

            distance = fmin(distance1, distance2);
            
            distance = fmin(distance1, distance2);
            minDistance = fmin(minDistance, distance);

        }
        opacity = fmin(opacity, (fmin(fmax(minDistance - threshold2, 0), threshold - threshold2) / (threshold - threshold2)) * 255);

    } else if (strcmp(bodyType, "planet") == 0) {
        
        threshold = 40;
        threshold2 = 10;
        
        for (int i = 0; i < numPlanets; i++) {

            if (strcmp(mainPlanets[i].name, name) == 0) break;

            Vector2 screenCordsPlanet = GetWorldToScreen(mainPlanets[i].drawPos, *camera);
            

            dx1 = textCenter.x - screenCordsPlanet.x;
            dy1 = textCenter.y - screenCordsPlanet.y;
            distance1 = sqrtf(dx1*dx1+dy1*dy1);

            dx2 = pos.x - screenCordsPlanet.x;
            dy2 = pos.y - screenCordsPlanet.y;
            distance2 = sqrtf(dx2*dx2+dy2*dy2);

            distance = fmin(distance1, distance2);
            
            distance = fmin(distance1, distance2);
            minDistance = fmin(minDistance, distance);

        }
        threshold = 40;
        threshold2 = 10;
        
        if (typeSelection[0]) {
            for (int i = 0; i < numPlanets; i++) {

                if (strcmp(mainPlanets[indexSelected].name, name) == 0) continue;

                Vector2 screenCordsPlanet = GetWorldToScreen(mainPlanets[indexSelected].drawPos, *camera);
                threshold = 40;
                threshold2 = 10;

                dx1 = textCenter.x - screenCordsPlanet.x;
                dy1 = textCenter.y - screenCordsPlanet.y;
                distance1 = sqrtf(dx1*dx1+dy1*dy1);

                dx2 = pos.x - screenCordsPlanet.x;
                dy2 = pos.y - screenCordsPlanet.y;
                distance2 = sqrtf(dx2*dx2+dy2*dy2);

                distance = fmin(distance1, distance2);
                
                distance = fmin(distance1, distance2);
                minDistance = fmin(minDistance, distance);

            }
        }

        opacity = fmin(opacity, (fmin(fmax(minDistance - threshold2, 0), threshold - threshold2) / (threshold - threshold2)) * 255);

        bool selectedIShow = typeSelection[0] && strcmp(name, mainPlanets[indexSelected].name) == 0;
        
        if (selectedIShow) {
            opacity = 255;
        }

    } else if (strcmp(bodyType, "minorBody") == 0) {
        
        threshold = 80;
        threshold2 = 20;
        
        for (int i = 0; i < numPlanets; i++) {
            Vector2 screenCordsPlanet = GetWorldToScreen(mainPlanets[i].drawPos, *camera);
            dx1 = textCenter.x - screenCordsPlanet.x;
            dy1 = textCenter.y - screenCordsPlanet.y;
            distance1 = sqrtf(dx1*dx1+dy1*dy1);

            dx2 = pos.x - screenCordsPlanet.x;
            dy2 = pos.y - screenCordsPlanet.y;
            distance2 = sqrtf(dx2*dx2+dy2*dy2);

            distance = fmin(distance1, distance2);
            minDistance = fmin(minDistance, distance);

        } 

        threshold = 60;
        threshold2 = 15;

        for (int i = 0; i < numMinorBodies; i++) {

            if (strcmp(mainMinorBodies[i].name, name) == 0) break;

            Vector2 screenCordsPlanet = GetWorldToScreen(mainMinorBodies[i].drawPos, *camera);

            dx1 = textCenter.x - screenCordsPlanet.x;
            dy1 = textCenter.y - screenCordsPlanet.y;
            distance1 = sqrtf(dx1*dx1+dy1*dy1);

            dx2 = pos.x - screenCordsPlanet.x;
            dy2 = pos.y - screenCordsPlanet.y;
            distance2 = sqrtf(dx2*dx2+dy2*dy2);

            distance = fmin(distance1, distance2);
            
            distance = fmin(distance1, distance2);
            minDistance = fmin(minDistance, distance);

        }
        opacity = fmin(opacity, (fmin(fmax(minDistance - threshold2, 0), threshold - threshold2) / (threshold - threshold2)) * 255);
    }

    return opacity;
}
void drawBody(Camera3D *camera, int fontsize, char *bodyType, int i) {

    Vector3 pos, radius;
    double rad;
    double multiplier;
    Color color;
    char name[128];
    char orbiting[128];


    if (!strcmp(bodyType, "planet")) {
        pos = mainPlanets[i].drawPos;
        radius = mainPlanets[i].drawRadius;
        rad = 6;
        multiplier = 1.0;
        color = mainPlanets[i].color;
        strcpy(name, mainPlanets[i].name);
        strcpy(orbiting, mainPlanets[i].bodyOrbiting);

    } else if (!strcmp(bodyType, "minorBody")) {
        pos = mainMinorBodies[i].drawPos;
        radius = mainMinorBodies[i].drawDimensions;
        rad = 4;
        multiplier = 0.5;
        color = BROWN;   
        strcpy(name, mainMinorBodies[i].name);
        strcpy(orbiting, mainMinorBodies[i].bodyOrbiting);

    } else if (!strcmp(bodyType, "moon")) {
        pos = mainMoons[i].drawPos;
        radius = mainMoons[i].drawRadius;
        rad = 5;
        multiplier = 1.0;
        color = RED;
        strcpy(name, mainMoons[i].name);
        strcpy(orbiting, mainMoons[i].bodyOrbiting);

    } else if (!strcmp(bodyType, "spacecraft")) {
        pos = mainSpacecraft[i].drawPos;
        radius = mainSpacecraft[i].drawDimensions;
        rad = 3;
        multiplier = 0.5;
        color = WHITE;
        strcpy(name, mainSpacecraft[i].name);
        strcpy(orbiting, mainSpacecraft[i].bodyOrbiting);
    }

    Vector2 screenCordinates = (Vector2){GetWorldToScreen(pos, *camera).x, GetWorldToScreen(pos, *camera).y};
    Vector2 textPos = {screenCordinates.x + fontsize/2.0, screenCordinates.y - fontsize/1.5};
    
    EndMode3D();
    
    double opacity = nameTagDrawCondtions(camera, name, bodyType, orbiting, screenCordinates, fontsize, textPos);
    bool draw = opacity == 0 ? false:true;

    double distanceToObject = Vector3Distance(camera->position, pos);
    double projectedRadius = (radius.x*multiplier / (distanceToObject * tanf(camera->fovy * DEG2RAD / 2.0f))) * (GetScreenHeight() / 2.0f);
    
    
    if (projectedRadius > rad) {
        draw = false;
    } 
    
    if (draw) {
        DrawTextEx(SpaceFont, name, textPos, fontsize, 1, (Color){color.r, color.g, color.b, opacity});
        DrawCircleLines(screenCordinates.x, screenCordinates.y, rad, (Color){color.r, color.g, color.b, opacity});
    }

    DrawCircle(screenCordinates.x, screenCordinates.y, projectedRadius, (Color){color.r, color.g, color.b, opacity});
    
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