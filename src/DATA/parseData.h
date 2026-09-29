#ifndef PARSEDATA_H
#define PARSEDATA_H
#include <raylib.h>
#include "../../src/body/body.h"
#include <string.h>
#include <stdlib.h>

void linkTextures();

void readFile(char **wholeJsonStr);

void initData();
#endif