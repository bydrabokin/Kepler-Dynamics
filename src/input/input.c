#include <raylib.h>
#include <stdio.h>
#include "../../src/camera/camera.h"
#include "../../src/body/body.h"
#include "../../src/utilities/utilities.h"
#include "raymath.h"
#include <math.h>

bool typeSelection[4] = {true, false, false, false};
int indexSelected = 0;

void numbers_2_planets(Camera3D *camera,  PolarVector3 *cameraPolar) {
    
    if (IsKeyPressed(KEY_ZERO)) {
        changeFocus(camera, cameraPolar, mainPlanets[0].drawPos, mainPlanets[0].drawRadius);
        indexSelected = 0;
        typeSelection[0] = true;
        typeSelection[1] = false;
        typeSelection[2] = false;
        typeSelection[3] = false;
    }
    if (IsKeyPressed(KEY_ONE)) {
        changeFocus(camera, cameraPolar, mainPlanets[1].drawPos, mainPlanets[1].drawRadius);
        indexSelected = 1;
        typeSelection[0] = true;
        typeSelection[1] = false;
        typeSelection[2] = false;
        typeSelection[3] = false;
    }
    if (IsKeyPressed(KEY_TWO)) {
        changeFocus(camera, cameraPolar, mainPlanets[2].drawPos, mainPlanets[2].drawRadius);
        indexSelected = 2;
        typeSelection[0] = true;
        typeSelection[1] = false;
        typeSelection[2] = false;
        typeSelection[3] = false;
    }
    if (IsKeyPressed(KEY_THREE)) {
        changeFocus(camera, cameraPolar, mainPlanets[3].drawPos, mainPlanets[3].drawRadius);
        indexSelected = 3;
        typeSelection[0] = true;
        typeSelection[1] = false;
        typeSelection[2] = false;
        typeSelection[3] = false;
    }
    if (IsKeyPressed(KEY_FOUR)) {
        changeFocus(camera, cameraPolar, mainPlanets[4].drawPos, mainPlanets[4].drawRadius);
        indexSelected = 4;
        typeSelection[0] = true;
        typeSelection[1] = false;
        typeSelection[2] = false;
        typeSelection[3] = false;
    }
    if (IsKeyPressed(KEY_FIVE)) {
        changeFocus(camera, cameraPolar, mainPlanets[5].drawPos, mainPlanets[5].drawRadius);
        indexSelected = 5;
        typeSelection[0] = true;
        typeSelection[1] = false;
        typeSelection[2] = false;
        typeSelection[3] = false;
    }
    if (IsKeyPressed(KEY_SIX)) {
        changeFocus(camera, cameraPolar, mainPlanets[6].drawPos, mainPlanets[6].drawRadius);
        indexSelected = 6;
        typeSelection[0] = true;
        typeSelection[1] = false;
        typeSelection[2] = false;
        typeSelection[3] = false;
    }
    if (IsKeyPressed(KEY_SEVEN)) {
        changeFocus(camera, cameraPolar, mainPlanets[7].drawPos, mainPlanets[7].drawRadius);
        indexSelected = 7;
        typeSelection[0] = true;
        typeSelection[1] = false;
        typeSelection[2] = false;
        typeSelection[3] = false;
    }
    if (IsKeyPressed(KEY_EIGHT)) {
        changeFocus(camera, cameraPolar, mainPlanets[8].drawPos, mainPlanets[8].drawRadius);
        indexSelected = 8;
        typeSelection[0] = true;
        typeSelection[1] = false;
        typeSelection[2] = false;
        typeSelection[3] = false;
    }
    if (IsKeyPressed(KEY_NINE)) {
        changeFocus(camera, cameraPolar, mainPlanets[9].drawPos, mainPlanets[9].drawRadius);
        indexSelected = 9;
        typeSelection[0] = true;
        typeSelection[1] = false;
        typeSelection[2] = false;
        typeSelection[3] = false;
    }
    
}

void clickOnBody(Camera3D *camera,  PolarVector3 *cameraPolar) {
    
    
    for (int i = 0; i < numPlanets; i++) { 
        Vector2 screen = (Vector2){GetWorldToScreen(mainPlanets[i].drawPos, *camera).x, GetWorldToScreen(mainPlanets[i].drawPos, *camera).y};
        
        double radius = 6;
        double distanceToObject = Vector3Distance(camera->position, mainPlanets[i].drawPos);
        double projectedRadius = (mainPlanets[i].drawRadius.x*0.5 / (distanceToObject * tanf(camera->fovy * DEG2RAD / 2.0f))) * (GetScreenHeight() / 2.0f);
        
        if (projectedRadius > radius) radius = projectedRadius;
        
        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT) && CheckCollisionPointCircle(GetMousePosition(), screen, radius)) {
            changeFocus(camera, cameraPolar, mainPlanets[i].drawPos, mainPlanets[i].drawRadius);
            indexSelected = i;
            typeSelection[0] = true;
            typeSelection[1] = false;
            typeSelection[2] = false;
            typeSelection[3] = false;

        }
    }

    for (int i = 0; i < numMinorBodies; i++) { 
        Vector2 screen = (Vector2){GetWorldToScreen(mainMinorBodies[i].drawPos, *camera).x, GetWorldToScreen(mainMinorBodies[i].drawPos, *camera).y};
        
        double radius = 4;
        double distanceToObject = Vector3Distance(camera->position, mainMoons[i].drawPos);
        double projectedRadius = (mainMoons[i].drawRadius.x*0.5 / (distanceToObject * tanf(camera->fovy * DEG2RAD / 2.0f))) * (GetScreenHeight() / 2.0f);
        
        if (projectedRadius > radius) radius = projectedRadius;

        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT) && CheckCollisionPointCircle(GetMousePosition(), screen, radius)) {
            changeFocus(camera, cameraPolar, mainMinorBodies[i].drawPos, mainMinorBodies[i].drawDimensions);
            indexSelected = i;
            typeSelection[0] = false;
            typeSelection[1] = true;
            typeSelection[2] = false;
            typeSelection[3] = false;

        }
    }

    for (int i = 0; i < numMoons; i++) { 
        Vector2 screen = (Vector2){GetWorldToScreen(mainMoons[i].drawPos, *camera).x, GetWorldToScreen(mainMoons[i].drawPos, *camera).y};
        double radius = 2;
        
        double distanceToObject = Vector3Distance(camera->position, mainMoons[i].drawPos);
        double projectedRadius = (mainMoons[i].drawRadius.x / (distanceToObject * tanf(camera->fovy * DEG2RAD / 2.0f))) * (GetScreenHeight() / 2.0f);
        
        if (projectedRadius > radius) radius = projectedRadius;
        
        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT) && CheckCollisionPointCircle(GetMousePosition(), screen, radius)) {
            changeFocus(camera, cameraPolar, mainMoons[i].drawPos, mainMoons[i].drawRadius);
            indexSelected = i;
            typeSelection[0] = false;
            typeSelection[1] = false;
            typeSelection[2] = true;
            typeSelection[3] = false;

        }
    } 

    for (int i = 0; i < numSpacecraft; i++) { 
        Vector2 screen = (Vector2){GetWorldToScreen(mainSpacecraft[i].drawPos, *camera).x, GetWorldToScreen(mainSpacecraft[i].drawPos, *camera).y};
        
        double radius = 2;
        double distanceToObject = Vector3Distance(camera->position, mainSpacecraft[i].drawPos);
        double projectedRadius = (mainSpacecraft[i].drawDimensions.x*0.5 / (distanceToObject * tanf(camera->fovy * DEG2RAD / 2.0f))) * (GetScreenHeight() / 2.0f);
        
        if (projectedRadius > radius) radius = projectedRadius;


        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT) && CheckCollisionPointCircle(GetMousePosition(), screen, radius)) {
            changeFocus(camera, cameraPolar, mainSpacecraft[i].drawPos, mainSpacecraft[i].drawDimensions);
            indexSelected = i;
            typeSelection[0] = false;
            typeSelection[1] = false;
            typeSelection[2] = true;
            typeSelection[3] = false;

        }
    }
}