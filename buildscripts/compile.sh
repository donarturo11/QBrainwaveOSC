#!/usr/bin/env bash

export ENV_FILE=${ENV_FILE:-$TMPDIR/environment.sh}
[[ -e $ENV_FILE ]] && . $ENV_FILE

SCRIPTS_DIR=${SCRIPTS_DIR:-$(cd $(dirname 0); pwd)}
CWD=${CWD:-$(pwd)}

SOURCE_DIR=${SOURCE_DIR:-$CWD}
BUILD_DIR=${BUILD_DIR:-$CWD/build}
cmake -S $SOURCE_DIR \
      -B $BUILD_DIR $CMAKE_OPTS
cmake --build $BUILD_DIR
