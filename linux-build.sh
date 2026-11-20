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
    source_files=(
        "./deps/glad/glad.c"
        "./source/debug/debug.c"
        "./source/input/input-state.c"
        "./deps/wayland/xdg-shell-protocol.c"
        "./source/window/linux/window-linux.c"
        "./source/graphics/linux/graphics-linux.c"
        "./deps/wayland/xdg-toplevel-icon-v1-protocol.c"
        "./deps/wayland/relative-pointer-unstable-v1-protocol.c"
        "./deps/wayland/pointer-constraints-unstable-v1-protocol.c"
    )

    includes="-L./deps/cglm -L./deps/core -I./deps/"
    linkages="-lwayland-client -lwayland-cursor -lwayland-egl -lGL -lEGL -lGLESv2 -lrt -lcglm -lm"
    cflags=""
    compiler="gcc"
    
    run "gcc -o ./build/fast-raymarch ./source/main.c  $includes -lcore $linkages"

fi

echo

run "./build/fast-raymarch"