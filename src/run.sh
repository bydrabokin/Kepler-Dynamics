#!/bin/bash

gcc "$1" -o main -lraylib -lm -lX11

if [ $? -eq 0 ]; then
    ./main
else
    read -p "Press Enter to close"
    exit 1
fi