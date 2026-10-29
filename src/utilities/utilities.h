#ifndef UTILITIES_H
#define UTILITIES_H
#include "../../src/body/body.h"

extern Font SpaceFont;
extern Texture2D SunRaw, MercuryRaw, VenusRaw, EarthRaw, MarsRaw, JupiterRaw, SaturnRaw, SaturnRingsRaw, UranusRaw, NeptuneRaw, PlutoRaw;

extern Texture2D CeresRaw, ErisRaw, MakemakeRaw, HaumeaRaw;

extern Texture2D MoonRaw, PhobosRaw, IoRaw, EuropaRaw, GanymedeRaw, CallistoRaw;
extern Texture2D MimasRaw, EnceladusRaw, TethysRaw, DioneRaw, RheaRaw, TitanRaw, IapetusRaw, PhoebeRaw;
extern Texture2D CharonRaw;
extern Texture2D defaultMoonRaw, defaultMinorBodyRaw;
extern Texture2D BackgroundRaw;

extern Model DawnGLB, JunoGLB, New_HorizonsGLB, Osiris_RexGLB, PioneerGLB, PSPGLB, VoyagerGLB;

extern int framesticked;
extern Vector2 middle;

typedef struct {
    double x;
    double y;
    double z;
} DVector3;

void doItwithAllDifferent(void (*functionPlanets)(), void (*functionMinorBodies)(), void (*functionMoons)(), void (*functionSpacecraft)());
void doItwithAllSame(void (*function)());

void loadFiles();
void loadFont();
void loadPlanets();
void loadMinorBodies();
void loadMoons();
void loadSpacecraft();
void loadExtra();


#endif