### Libfizzix ###
Checkout and compile the code
```
svn checkout http://fizzix.googlecode.com/svn/trunk/ fizzix-read-only
cd fizzix-read-only
```
If you're on a mac, do the following:
```
./local_mac_compile.sh
```
Otherwise, read on:
```
cd libfizzix
./configure
make
```
Install:
If you have root permissions:
```
sudo make install
cd ../fizzix
qmake
make
sudo make install
```
And run:
```
fizzix
```
If not, do a local install (this assumes you're on a mac):
```
cd ../
./local_libfizzix_install.sh
cd fizzix
qmake local_fizzix.pro -spec macx-g++
make
```
And run:
```
./fizzix
```