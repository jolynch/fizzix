#!/bin/bash
./local_libfizzix_compile.sh
cd fizzix
qmake local_fizzix.pro -spec macx-g++
make
