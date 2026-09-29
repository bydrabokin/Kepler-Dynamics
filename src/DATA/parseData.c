#include <stdio.h>
#include <raylib.h>
#include "../cJSON.h"
#include "../../src/body/body.h"
#include "../../src/utilities/utilities.h"
#include "../../src/draw/draw.h"
#include <string.h>
#include <stdlib.h>

void linkTextures() {

    mainPlanets[0].textureRaw = SunRaw;
    mainPlanets[1].textureRaw = MercuryRaw;
    mainPlanets[2].textureRaw = VenusRaw;
    mainPlanets[3].textureRaw = EarthRaw;
    mainPlanets[4].textureRaw = MarsRaw;
    mainPlanets[5].textureRaw = JupiterRaw;
    mainPlanets[6].textureRaw = SaturnRaw;
    mainPlanets[7].textureRaw = UranusRaw;
    mainPlanets[8].textureRaw = NeptuneRaw;
    mainPlanets[9].textureRaw = PlutoRaw;

    for (int i = 0; i < numPlanets; i++) {
        mainPlanets[i].color = (Color)getaverageColor(mainPlanets[i].textureRaw);
    }
    
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
    
    numPlanets = 0;
    numMinorBodies = 0;
    numMoons = 0;
    numSpacecraft = 0;


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
            numPlanets++;
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
            numMinorBodies++;
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
            numMoons++;
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
            numSpacecraft++;
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

