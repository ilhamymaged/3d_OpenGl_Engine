#!/bin/bash

SOURCE_DIR="$(dirname "$0")/.."
BUILD_DIR="$(dirname "$0")/build"

if [ ! -d "$BUILD_DIR" ]; then
    mkdir "$BUILD_DIR"
fi

cd "$BUILD_DIR" || exit 1 # Exit if cd fails

echo "Running CMake in $BUILD_DIR..."
cmake "$SOURCE_DIR" || exit 1 

echo "Building project..."
make || exit 1 

echo "Build complete."

echo "Running project.."
./CMakeTarget
