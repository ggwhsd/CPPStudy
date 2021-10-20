#!/bin/sh

set -x
SOURCE_DIR=`pwd`
#如果没有定义过BUILD_DIR则使用../build，否则使用BUILD_DIR
BUILD_DIR=${BUILD_DIR:-./build}
BUILD_TYPE=${BUILD_TYPE:-release}
INSTALL_DIR=${INSTALL_DIR:-../${BUILD_TYPE}-install-cpp11}
CXX=${CXX:-g++}

#mkdir -p $BUILD_DIR/$BUILD_TYPE-cpp11 && cd $BUILD_DIR/$BUILD_TYPE-cpp11 

mkdir -p test

cmake -DCMAKE_BUILD_TYPE=$BUILD_TYPE \
      -DCMAKE_INSTALL_PREFIX=$INSTALL_DIR \
	  -DCMAKE_EXPORT_COMPILE_COMMANDS=ON \
	  $SOURCE_DIR 
