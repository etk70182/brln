#!/bin/bash

DIST=dist
FRAMEWORKS=brln.app/Contents/Frameworks
EXE=brln.app/Contents/MacOS

mkdir -p $DIST
mkdir -p $DIST/$FRAMEWORKS

cp $1/bin/brln $DIST/$EXE
cp $1/_deps/libpd-src/libs/libpd.so  $DIST/$FRAMEWORKS

