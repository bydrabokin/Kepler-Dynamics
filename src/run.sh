#!/bin/bash

gcc main.c input/input.c DATA/parseData.c draw/draw.c utilities/utilities.c camera/camera.c \
    -o main -lraylib -lm -lX11 -lcjson

if [ $? -eq 0 ]; then
    ./main
else
    read -p "Press Enter to close"
    exit 1
fi