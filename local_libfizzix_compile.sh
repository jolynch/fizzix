#!/bin/bash
cd local_install
fiz_installpath=$PWD
cd ../libfizzix
./configure --prefix=$fiz_installpath
make
make install
