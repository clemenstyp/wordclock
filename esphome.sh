#!/bin/bash
#
SCRIPT_DIR=$( cd -- "$( dirname -- "${BASH_SOURCE[0]}" )" &> /dev/null && pwd )
SCRIPT_NAME=$(basename "${BASH_SOURCE[0]}")
# echo "The script you are running has SCRIPT_NAME \"$SCRIPT_NAME\", SCRIPT_DIR \"$SCRIPT_DIR\""

cd "$SCRIPT_DIR"
# echo "The present working directory is `pwd`"


docker run --rm --privileged \
    -v "${PWD}":/config \
    -it ghcr.io/esphome/esphome \
    "$@"