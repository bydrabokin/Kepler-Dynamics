#include <stdio.h>
#include "../../src/body/body.h"
#include "../../src/draw/draw.h"

Font SpaceFont;
Texture2D SunRaw, MercuryRaw, VenusRaw, EarthRaw, MarsRaw, JupiterRaw, SaturnRaw, SaturnRingsRaw, UranusRaw, NeptuneRaw, PlutoRaw;

Texture2D CeresRaw, ErisRaw, MakemakeRaw, HaumeaRaw;

Texture2D MoonRaw, PhobosRaw, IoRaw, EuropaRaw, GanymedeRaw, CallistoRaw;
Texture2D MimasRaw, EnceladusRaw, TethysRaw, DioneRaw, RheaRaw, TitanRaw, IapetusRaw, PhoebeRaw;
Texture2D CharonRaw;

Model DawnGLB, JunoGLB, New_HorizonsGLB, Osiris_RexGLB, PioneerGLB, PSPGLB, VoyagerGLB;

void doItwithAllDifferent(void (*functionPlanets)(), void (*functionMinorBodies)(), void (*functionMoons)(), void (*functionSpacecraft)()) {
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


void doItwithAllSame(void (*function)()) {
    int celestialNum = numPlanets + numMinorBodies + numMoons + numSpacecraft;
    int index;

    Vector3 pos, radius;
    Vector3 *drawPos, *drawRadius;
    for (int i = 0; i < celestialNum; i++) {
        if (i < numPlanets) {
            index = i;
            pos = mainPlanets[index].pos;
            radius = mainPlanets[index].radius;
            drawPos = &mainPlanets[index].drawPos;
            drawRadius = &mainPlanets[index].drawRadius;
        } else if (i < numPlanets + numMinorBodies) {
            index = i - numPlanets;
            pos = mainMinorBodies[index].pos;
            radius = mainMinorBodies[index].dimensions;
            drawPos = &mainMinorBodies[index].drawPos;
            drawRadius = &mainMinorBodies[index].drawDimensions;
        } else if (i < numPlanets + numMinorBodies + numMoons) {
            index = i - (numMinorBodies + numPlanets);
            pos = mainMoons[index].pos;
            radius = mainMoons[index].radius;
            drawPos = &mainMoons[index].drawPos;
            drawRadius = &mainMoons[index].drawRadius;
        } else if (i < celestialNum) {
            index = i - numPlanets - numMinorBodies - numMoons;
            pos = mainSpacecraft[index].pos;
            radius = mainSpacecraft[index].dimensions;
            drawPos = &mainSpacecraft[index].drawPos;
            drawRadius = &mainSpacecraft[index].drawDimensions;
        }

        function(pos, radius, drawPos, drawRadius);
    }
}

void loadFont() {
    SpaceFont = LoadFont("../assets/font/Monocraft.ttf");
}

void loadPlanets() {
    
    SunRaw = LoadTexture("../assets/planets/sun.png");
    MercuryRaw = LoadTexture("../assets/planets/mercury.png");
    VenusRaw = LoadTexture("../assets/planets/venus.png");
    EarthRaw = LoadTexture("../assets/planets/earth.png");
    MarsRaw = LoadTexture("../assets/planets/mars.png");
    JupiterRaw = LoadTexture("../assets/planets/jupiter.png");
    SaturnRaw = LoadTexture("../assets/planets/saturn.png");
    SaturnRingsRaw = LoadTexture("../assets/planets/saturnRings.png");
    UranusRaw = LoadTexture("../assets/planets/uranus.png");
    NeptuneRaw = LoadTexture("../assets/planets/neptune.png");
    PlutoRaw = LoadTexture("../assets/planets/pluto.png");
}

void loadMinorBodies() {
    
    CeresRaw = LoadTexture("../assets/minorBodies/ceres.png");
    ErisRaw = LoadTexture("../assets/minorBodies/eris.png");
    MakemakeRaw = LoadTexture("../assets/minorBodies/makemake.png");
    HaumeaRaw = LoadTexture("../assets/minorBodies/haumea.png");

}

void loadMoons() {
    
    MoonRaw = LoadTexture("../assets/moons/moon.png");
    PhobosRaw = LoadTexture("../assets/moons/phobos.png");
    IoRaw = LoadTexture("../assets/moons/io.png");
    EuropaRaw = LoadTexture("../assets/moons/europa.png");
    GanymedeRaw = LoadTexture("../assets/moons/ganymede.png");
    CallistoRaw = LoadTexture("../assets/moons/callisto.png");
    MimasRaw = LoadTexture("../assets/moons/mimas.png");
    EnceladusRaw = LoadTexture("../assets/moons/enceladus.png");
    TethysRaw = LoadTexture("../assets/moons/tethys.png");
    DioneRaw = LoadTexture("../assets/moons/dione.png");
    RheaRaw = LoadTexture("../assets/moons/rhea.png");
    TitanRaw = LoadTexture("../assets/moons/titan.png");
    IapetusRaw = LoadTexture("../assets/moons/iapetus.png");
    PhoebeRaw = LoadTexture("../assets/moons/phoebe.png");
    CharonRaw = LoadTexture("../assets/moons/charon.png");
}

void loadSpacecraft() {
    DawnGLB = LoadModel("../assets/spacecraft/Dawn.glb");
    JunoGLB = LoadModel("../assets/spacecraft/Juno.glb");
    New_HorizonsGLB = LoadModel("../assets/spacecraft/New_Horizons.glb");
    Osiris_RexGLB = LoadModel("../assets/spacecraft/Osiris_Rex.glb");
    PioneerGLB = LoadModel("../assets/spacecraft/Pioneer.glb");
    PSPGLB = LoadModel("../assets/spacecraft/PSP.glb");
    VoyagerGLB = LoadModel("../assets/spacecraft/Voyager.glb");
}

void loadFiles() {
    loadFont();
    loadPlanets();
    loadMinorBodies();
    loadMoons();
    loadSpacecraft();
}
