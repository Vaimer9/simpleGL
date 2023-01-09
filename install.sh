#! /bin/bash

mkdir build
cd build
cmake ..
make
sudo cp libgraphic.so /usr/lib/
cd ..
sudo mkdir /usr/include/graphic
cd include
sudo cp *.hpp /usr/include/graphic -r
sudo mv /usr/include/graphic/graphic.hpp /usr/include/
echo "Finished installation with package name \`graphic\`"
