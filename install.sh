#! /bin/bash

mkdir build
cd build
cmake ..
make
sudo cp libsimpleGL.so /usr/lib/
cd ..
sudo mkdir /usr/include/simpleGL
cd include
sudo cp *.hpp /usr/include/simpleGL -r
sudo mv /usr/include/simpleGL/simpleGL.hpp /usr/include/
echo "Finished installation with package name \`simpleGL\`"
