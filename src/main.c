#include <raylib.h>
#include <stdio.h>
#include <math.h>
#include <string.h>
#include <stdlib.h>
#include "cJSON.h"

#define SCREEN_HALF_X 900
#define SCREEN_HALF_Y 450
#define screenUnit_2_meter 1e10
#define meter_2_screenUnit 1e-10

#define AU 1.496e+11 //in meters
#define G 6.6743e-11

int targetFps;

typedef struct  {
    double r, θ, φ;
} PolarVector3;

PolarVector3 cameraPolar;

typedef struct  {
    Vector3 drawPos, pos, vel;
    Vector3 radius;

    double mass;
    double axial_tilt_deg, bond_albedo, mean_solar_day_s, mean_temperature_K, surface_pressure_Pa;
    
    char code[128];
    char name[128];
    char type[128];
    char bodyOrbiting[128];

} Planet;

Planet mainPlanets[256];

typedef struct  {
    Vector3 drawPos, pos, vel;
    Vector3 dimensions;

    double mass;
    
    char code[128];
    char name[128];
    char type[128];
    char bodyOrbiting[128];

} MinorBody;

MinorBody mainMinorBodies[256];

typedef struct  {
    Vector3 drawPos, pos, vel;
    Vector3 radius;

    double mass;
    double mean_solar_day_s;
    
    char code[128];
    char name[128];
    char type[128];
    char bodyOrbiting[128];

} Moon;

Moon mainMoons[256];

typedef struct  {
    Vector3 drawPos, pos, vel;
    Vector3 dimensions;

    double mass;
    
    char code[128];
    char name[128];
    char type[128];
    char bodyOrbiting[128];

} Spacecraft;

Spacecraft mainSpacecraft[256];



Vector3 polar_2_cartesian(PolarVector3 polar) {
    Vector3 cartesian;
    cartesian.x = polar.r * cosf(polar.φ * DEG2RAD) * cosf(polar.θ * DEG2RAD);
    cartesian.y = polar.r * sinf(polar.φ * DEG2RAD);
    cartesian.z = polar.r * cosf(polar.φ * DEG2RAD) * sinf(polar.θ * DEG2RAD);

    return cartesian;
}

//set initial
void setInitialMiscellanious() {
}

void setIntialCamera(Camera3D *camera) {

    cameraPolar.r = 10;
    cameraPolar.θ = 10;
    cameraPolar.φ = 34;

    camera->position = (Vector3){cameraPolar.r, cameraPolar.θ, cameraPolar.φ} ;
    camera->target = (Vector3){0, 0, 0};
    camera->up = (Vector3){0, 1, 0};

    camera->fovy = 100;
    camera->projection = CAMERA_PERSPECTIVE;
}

void cameraLogic(Camera3D *camera) {
    
    //zoom
    if (GetMouseWheelMove() == 1.0) {
        cameraPolar.r *= 1.2;
    } else if (GetMouseWheelMove() == -1.0) {
        cameraPolar.r *= 0.8;
    }

    //dragging
    if (IsMouseButtonDown(MOUSE_BUTTON_LEFT)) {

        float sensitivity = 0.3;
        Vector2 delta = {GetMouseDelta().x * sensitivity, GetMouseDelta().y * sensitivity};
        cameraPolar.θ += delta.x;
        cameraPolar.φ += delta.y;

        //limits
        if (cameraPolar.θ >= 360)
            cameraPolar.θ -= 360;

        if (cameraPolar.θ < 0)
            cameraPolar.θ += 360;

        if (cameraPolar.φ > 89)
            cameraPolar.φ = 89;

        if (cameraPolar.φ < -89)
            cameraPolar.φ = -89;

        }
    
    camera->position = (Vector3)polar_2_cartesian(cameraPolar);
}

void readFile(char **wholeJsonStr) {

    //read file->
    //open file
    FILE *f = fopen("DATA/data.json", "r");
    if (f == NULL) {
        printf("Failed to open file\n");
        return;
    }
    //go to end
    fseek(f, 0, SEEK_END);
    long length = ftell(f);
    rewind(f);

    //read
   *wholeJsonStr = (char *)malloc(length + 1);
    if (*wholeJsonStr == NULL) {
        printf("failed file\n");
        fclose(f);
        return;
    }

    //finish string
    size_t readBytes = fread(*wholeJsonStr, 1, length, f);
    (*wholeJsonStr)[readBytes] = '\0';    


    //clean up
    fclose(f);
}

void initData() {

    char *file = NULL;
    readFile(&file);
    cJSON *root = cJSON_Parse(file);

    free(file);

    if (root == NULL) {
        printf("JSON parsing failed\n");
    }
    
    cJSON *body = root->child;
    int i = 0;

    cJSON *radius_m, *radiusx, *radiusy, *radiusz, *dimensions_m, *dimensionsx, *dimensionsy, *dimensionsz;
    cJSON *axial_tilt_deg, *bond_albedo, *mean_solar_day_s, *mean_temperature_K, *surface_pressure_Pa, *orbiting;
    cJSON *state, *position_m, *positionx, *positiony, *positionz, *velocity_ms, *velocityx, *velocityy, *velocityz;
    cJSON *type, *name, *physical, *mass_kg;
    
    while (body != NULL) {

        //parsing the json
        type = cJSON_GetObjectItem(body, "type");
        name = cJSON_GetObjectItem(body, "name");

        physical = cJSON_GetObjectItem(body, "physical");
        mass_kg = cJSON_GetObjectItem(physical, "mass_kg");

        if (strcmp(type->valuestring, "planet") == 0 || strcmp(type->valuestring, "moon") == 0) {
            radius_m = cJSON_GetObjectItem(physical, "radius_m");
            radiusx = cJSON_GetObjectItem(radius_m, "x");
            radiusy = cJSON_GetObjectItem(radius_m, "y");
            radiusz = cJSON_GetObjectItem(radius_m, "z");
        } else if (strcmp(type->valuestring, "minorBody") == 0 || strcmp(type->valuestring, "spacecraft") == 0) {
            printf("First Check\n");
            dimensions_m = cJSON_GetObjectItem(physical, "dimensions_m");
            dimensionsx = cJSON_GetObjectItem(dimensions_m, "x");
            dimensionsy = cJSON_GetObjectItem(dimensions_m, "y");
            dimensionsz = cJSON_GetObjectItem(dimensions_m, "z");
        }

        if (strcmp(type->valuestring, "planet") == 0) {
            axial_tilt_deg = cJSON_GetObjectItem(physical, "axial_tilt_deg");
            bond_albedo = cJSON_GetObjectItem(physical, "bond_albedo");
            mean_solar_day_s = cJSON_GetObjectItem(physical, "mean_solar_day_s");
            mean_temperature_K = cJSON_GetObjectItem(physical, "mean_temperature_K");
            surface_pressure_Pa = cJSON_GetObjectItem(physical, "surface_pressure_Pa");
        } else if (strcmp(type->valuestring, "moon") == 0) {
            mean_solar_day_s = cJSON_GetObjectItem(physical, "mean_solar_day_s");
        }

        state = cJSON_GetObjectItem(body, "state");

        orbiting = cJSON_GetObjectItem(physical, "orbiting");

        position_m = cJSON_GetObjectItem(state, "position_m");
        positionx = cJSON_GetObjectItem(position_m, "x");
        positiony = cJSON_GetObjectItem(position_m, "y");
        positionz = cJSON_GetObjectItem(position_m, "z");

        velocity_ms = cJSON_GetObjectItem(state, "velocity_ms");
        velocityx = cJSON_GetObjectItem(velocity_ms, "x");
        velocityy = cJSON_GetObjectItem(velocity_ms, "y");
        velocityz = cJSON_GetObjectItem(velocity_ms, "z");
        
        if (strcmp(type->valuestring, "planet") == 0) {

            Planet bufferPlanet = {

                .mass = mass_kg->valuedouble,
                .radius = (Vector3){radiusx->valuedouble, radiusy->valuedouble, radiusz->valuedouble},
                
                .axial_tilt_deg = axial_tilt_deg->valuedouble,
                .bond_albedo = bond_albedo->valuedouble,
                .mean_solar_day_s = mean_solar_day_s->valuedouble,
                .mean_temperature_K = mean_temperature_K->valuedouble,
                .surface_pressure_Pa = surface_pressure_Pa->valuedouble,
                
                .pos = (Vector3){positionx->valuedouble, positiony->valuedouble, positionz->valuedouble},
                .vel = (Vector3){velocityx->valuedouble, velocityy->valuedouble, velocityz->valuedouble},
            };

            strcpy(bufferPlanet.code, body->string);
            strcpy(bufferPlanet.type, type->valuestring);
            strcpy(bufferPlanet.name, name->valuestring);
            strcpy(bufferPlanet.bodyOrbiting, orbiting->valuestring);
    
            mainPlanets[i] = (Planet)bufferPlanet;

        } else if (strcmp(type->valuestring, "minorBody") == 0) {
            MinorBody bufferMinorBody = {

                .mass = mass_kg->valuedouble,
                .dimensions = (Vector3){dimensionsx->valuedouble, dimensionsy->valuedouble, dimensionsz->valuedouble},
                
                .pos = (Vector3){positionx->valuedouble, positiony->valuedouble, positionz->valuedouble},
                .vel = (Vector3){velocityx->valuedouble, velocityy->valuedouble, velocityz->valuedouble},
            };

            strcpy(bufferMinorBody.code, body->string);
            strcpy(bufferMinorBody.type, type->valuestring);
            strcpy(bufferMinorBody.name, name->valuestring);
            strcpy(bufferMinorBody.bodyOrbiting, orbiting->valuestring);


            mainMinorBodies[i] = (MinorBody)bufferMinorBody;

        } else if (strcmp(type->valuestring, "moon") == 0) {
            Moon bufferMoon = {

                .mass = mass_kg->valuedouble,
                .radius = (Vector3){dimensionsx->valuedouble, dimensionsy->valuedouble, dimensionsz->valuedouble},

                .mean_solar_day_s = mean_solar_day_s->valuedouble,

                .pos = (Vector3){positionx->valuedouble, positiony->valuedouble, positionz->valuedouble},
                .vel = (Vector3){velocityx->valuedouble, velocityy->valuedouble, velocityz->valuedouble},
            };

            strcpy(bufferMoon.code, body->string);
            strcpy(bufferMoon.type, type->valuestring);
            strcpy(bufferMoon.name, name->valuestring);
            strcpy(bufferMoon.bodyOrbiting, orbiting->valuestring);

            mainMoons[i] = (Moon)bufferMoon;

        } else if (strcmp(type->valuestring, "spacecraft") == 0) {
            Spacecraft bufferSpacecraft = {

                .mass = mass_kg->valuedouble,
                .dimensions = (Vector3){dimensionsx->valuedouble, dimensionsy->valuedouble, dimensionsz->valuedouble},
                
                .pos = (Vector3){positionx->valuedouble, positiony->valuedouble, positionz->valuedouble},
                .vel = (Vector3){velocityx->valuedouble, velocityy->valuedouble, velocityz->valuedouble},
            };

            strcpy(bufferSpacecraft.code, body->string);
            strcpy(bufferSpacecraft.type, type->valuestring);
            strcpy(bufferSpacecraft.name, name->valuestring);
            strcpy(bufferSpacecraft.bodyOrbiting, orbiting->valuestring);


            mainSpacecraft[i] = (Spacecraft)bufferSpacecraft;
        }


        char beforeType[128];
        strcpy(beforeType, type->valuestring);
        
        i++;
        body = body->next;

        if (body == NULL) break;
        
        type = cJSON_GetObjectItem(body, "type");

        char afterType[128];
        strcpy(afterType, type->valuestring);

        if (strcmp(beforeType, afterType) != 0) {
            i = 0;
        }

    }

}



int main() {
    
    //FPS
    //system("python3 DATA/getData.py");
    targetFps = 100;
    SetTargetFPS(targetFps);

    InitWindow(1800, 900, "Kepler Dynamics 🪐");
    Model voyager = LoadModel("../assets/spacecraft/Juno.glb");
    
    Camera3D pov = {0};
    
    //set
    setInitialMiscellanious();
    setIntialCamera(&pov);
    initData();


    while (!WindowShouldClose()) {
        
        cameraLogic(&pov);

        //Drawing
        BeginDrawing();
        ClearBackground(BLACK);

        BeginMode3D(pov);   

        //DrawSphere((Vector3){0, 2, 0}, 1, BLUE);
        DrawModel(voyager, (Vector3){0, 0, 0}, 1.0f, RAYWHITE);

        EndMode3D();

        EndDrawing();

    }

}