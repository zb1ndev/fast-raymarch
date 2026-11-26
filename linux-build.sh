#!/bin/bash

run() {

    local command="$1"
    echo "linux-build.sh: $command"
    $command

}

set -e
run_only=0
install_dependencies=0

for arg in "$@"; do

    if [[ "$arg" == "-i" ]]; then
        
        install_dependencies=1
    
    elif [[ "$arg" == "-r" ]]; then
        
        run_only=1
    
    fi

done

if [[ $install_dependencies -eq 1 ]]; then

    sudo apt-get update
    sudo apt-get install -y libwayland-dev libwayland-bin libgl-dev libegl-dev libgles-dev libcglm-dev wayland-protocols
    
fi

if [[ $run_only -eq 0 ]]; then

    object_files=()
    source_files="
        ./source/main.c 
        ./source/scene/scene.c 
        ./source/application/application.c
    "

    includes="-L./deps/cglm -L./deps/core -I./deps/ -I./source"
    linkages="-lwayland-client -lwayland-cursor -lwayland-egl -lGL -lEGL -lGLESv2 -lrt -lcglm -lm"
    cflags=""
    compiler="gcc"
    
    run "gcc -o ./build/fast-raymarch $source_files $includes -lcore $linkages"

fi

echo

run "./build/fast-raymarch -fps"