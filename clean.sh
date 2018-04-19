#!/bin/bash
# because i am too lame to make a Makefile

BINARY_DIR='bin'
BINARY_NAME='FetchBoy'
OBJECT_DIR='obj'

echo 'cleaning binary';
rm $BINARY_DIR/$BINARY_NAME

echo 'cleaning objects';
rm $OBJECT_DIR/*.o

