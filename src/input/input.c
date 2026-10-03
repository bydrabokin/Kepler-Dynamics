#include <raylib.h>
#include <stdio.h>
#include "../../src/camera/camera.h"
#include "../../src/body/body.h"

bool typeSelection[4] = {true, false, false, false};
int indexSelected = 0;

void numbers_2_planets(Camera3D *camera,  PolarVector3 *cameraPolar) {
    
    if (IsKeyPressed(KEY_ZERO)) {changeFocus(camera, cameraPolar, mainPlanets[0].drawPos, mainPlanets[0].drawRadius); printf("yes\n");}
    if (IsKeyPressed(KEY_ONE)) changeFocus(camera, cameraPolar, mainPlanets[1].drawPos, mainPlanets[1].drawRadius);
    if (IsKeyPressed(KEY_TWO)) changeFocus(camera, cameraPolar, mainPlanets[2].drawPos, mainPlanets[2].drawRadius);
    if (IsKeyPressed(KEY_THREE)) changeFocus(camera, cameraPolar, mainPlanets[3].drawPos, mainPlanets[3].drawRadius);
    if (IsKeyPressed(KEY_FOUR)) changeFocus(camera, cameraPolar, mainPlanets[4].drawPos, mainPlanets[4].drawRadius);
    if (IsKeyPressed(KEY_FIVE)) changeFocus(camera, cameraPolar, mainPlanets[5].drawPos, mainPlanets[5].drawRadius);
    if (IsKeyPressed(KEY_SIX)) changeFocus(camera, cameraPolar, mainPlanets[6].drawPos, mainPlanets[6].drawRadius);
    if (IsKeyPressed(KEY_SEVEN)) changeFocus(camera, cameraPolar, mainPlanets[7].drawPos, mainPlanets[7].drawRadius);
    if (IsKeyPressed(KEY_EIGHT)) changeFocus(camera, cameraPolar, mainPlanets[8].drawPos, mainPlanets[8].drawRadius);
    if (IsKeyPressed(KEY_NINE)) changeFocus(camera, cameraPolar, mainPlanets[9].drawPos, mainPlanets[9].drawRadius);
    
}

void clickOnBody(Camera3D *camera,  PolarVector3 *cameraPolar) {
    
    
    for (int i = 0; i < numPlanets; i++) { 
        Vector2 screen = (Vector2){GetWorldToScreen(mainPlanets[i].drawPos, *camera).x, GetWorldToScreen(mainPlanets[i].drawPos, *camera).y};
        double radius = 6;
        if (IsMouseButtonDown(MOUSE_BUTTON_LEFT) && CheckCollisionPointCircle(GetMousePosition(), screen, radius)) {
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
        if (IsMouseButtonDown(MOUSE_BUTTON_LEFT) && CheckCollisionPointCircle(GetMousePosition(), screen, radius)) {
            changeFocus(camera, cameraPolar, mainMinorBodies[i].drawPos, mainMinorBodies[i].drawDimensions);
            indexSelected = i;
            typeSelection[0] = false;
            typeSelection[1] = true;
            typeSelection[2] = false;
            typeSelection[3] = false;

        }
    }
}