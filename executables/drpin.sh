#!/bin/bash

DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" >/dev/null && pwd )"

DYNAMORIO_EXE=$DIR/../dynamorio/build/bin64/drrun
DRPIN_TOOL=$DIR/../drpin/build/libdrpin.so

$DYNAMORIO_EXE -c $DRPIN_TOOL $@
