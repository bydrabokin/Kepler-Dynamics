#ifndef BODY_H
#define BODY_H
#include <raylib.h>

typedef struct  {
    Vector3 drawPos, pos, vel;
    Vector3 drawRadius, radius;

    double mass;
    double axial_tilt_deg, bond_albedo, mean_solar_day_s, mean_temperature_K, surface_pressure_Pa;
    
    char code[128];
    char name[128];
    char type[128];
    char bodyOrbiting[128];

} Planet;


typedef struct  {
    Vector3 drawPos, pos, vel;
    Vector3 drawDimensions, dimensions;

    double mass;
    
    char code[128];
    char name[128];
    char type[128];
    char bodyOrbiting[128];

} MinorBody;

typedef struct  {
    Vector3 drawPos, pos, vel;
    Vector3 drawRadius, radius; 

    double mass;
    double mean_solar_day_s;
    
    char code[128];
    char name[128];
    char type[128];
    char bodyOrbiting[128];

} Moon;

typedef struct  {
    Vector3 drawPos, pos, vel;
    Vector3 drawDimensions, dimensions;

    double mass;
    
    char code[128];
    char name[128];
    char type[128];
    char bodyOrbiting[128];

} Spacecraft;

#endif