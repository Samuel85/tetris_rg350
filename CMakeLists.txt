cmake_minimum_required (VERSION 3.5)

SET(CMAKE_SYSTEM_NAME Linux)
# MIPS compiler
SET(CMAKE_C_COMPILER   "/opt/gcw0-toolchain/usr/bin/mipsel-gcw0-linux-uclibc-gcc")
SET(CMAKE_CXX_COMPILER "/opt/gcw0-toolchain/usr/bin/mipsel-gcw0-linux-uclibc-g++")
SET(CMAKE_RANLIB "/opt/gcw0-toolchain/usr/bin/mipsel-gcw0-linux-uclibc-ranlib")
SET(CMAKE_LINKER "/opt/gcw0-toolchain/usr/bin/mipsel-gcw0-linux-uclibc-ld")
SET(CMAKE_FIND_ROOT_PATH  /opt/gcw0-toolchain/usr/mipsel-gcw0-linux-uclibc/sysroot)
SET(CMAKE_FIND_ROOT_PATH_MODE_PROGRAM NEVER)
SET(CMAKE_FIND_ROOT_PATH_MODE_LIBRARY ONLY)
SET(CMAKE_FIND_ROOT_PATH_MODE_INCLUDE ONLY)
#
project (tetris)
set(BIN_DIR ${tetris_SOURCE_DIR}/bin)
add_subdirectory(src)

install(TARGETS tetris RUNTIME DESTINATION ${BIN_DIR} )
