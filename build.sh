#!/bin/bash
# because i am too lame to make a Makefile

SRC_DIR='src'
BINARY_DIR='bin'
BINARY_NAME='FetchBoy'
OBJECT_DIR='obj'

mkdir -p $BINARY_DIR
mkdir -p $OBJECT_DIR

echo 'compiling weather.o';
g++ -c $SRC_DIR/weather.cpp -o $OBJECT_DIR/weather.o

echo 'compiling fetchboy.o';
g++ -c $SRC_DIR/fetchboy.cpp -o $OBJECT_DIR/fetchboy.o

echo 'linking objects to exectuable' $BINARY_NAME;
g++ -o $BINARY_DIR/$BINARY_NAME $OBJECT_DIR/weather.o $OBJECT_DIR/fetchboy.o -lcurl
