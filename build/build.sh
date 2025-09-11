#!/usr/bin/env bash
# This is a general purpose build script for C/C++ projects.
# It compiles all .c and .cpp files in the ../src directory,
# includes headers from ../lib, and links against libraries in ../lib.
# !!!!!!!!!!!!!* it assumes it is placed in a build/ directory next to src/ and lib/ directories. *!!!!!!!!!!!!!!!

libDir="../lib"
srcDir="../src"
buildDir="."
# Find all source files
  cppFiles=$(find ${srcDir} -name "*.cpp" | tr '\n' ' ')
    cFiles=$(find ${srcDir} -name "*.c" | tr '\n' ' ')
    hFiles=$(find "$(cd ${srcDir}; pwd)" -name "*.h" | tr '\n' ' ' | sed 's|/[^/]*\.h||g' | sed 's| /| -I/|g' | sed 's/^/-I/' )
 hLibFiles=$(find "$(cd ${libDir}; pwd)" -name "*.h" | tr '\n' ' ' | sed 's|/[^/]*\.h||g' | sed 's| /| -I/|g' | sed 's/^/-I/' )
soLibFiles=$(find "$(cd ${libDir}; pwd)" -name "*.so" | tr '\n' ' ' | sed 's|/[^/]*\.so||g' | sed 's| /| -L/|g' | sed 's/^/-L/' )
 aLibFiles=$(find ${libDir} -name "*.a" | tr '\n' ' ')

# Compile with proper include paths and link against raylib

g++ ${cFiles} ${cppFiles} ${aLibFiles} ${hLibFiles} ${hFiles} ${soLibFiles} -g3 -o ${buildDir}/'app'
#g++ ${cFiles} ${cppFiles} ${aLibFiles} ${hLibFiles} ${hFiles} ${soLibFiles} -g0 -o ${buildDir}/'app'
