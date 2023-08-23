#! /bin/bash

BLUE="\e[34m"
GREEN="\e[32m"
ENDCOLOR="\e[0m"

if [ ! -d build ]
then
    mkdir build
fi
cd build
cmake ..
make
sudo cp libsimpleGL.so /usr/lib/
cd ..

if [ ! -d /usr/include/simpleGL ]
then
    sudo mkdir /usr/include/simpleGL
fi

cd include
sudo cp *.hpp /usr/include/simpleGL -r
sudo mv /usr/include/simpleGL/simpleGL.hpp /usr/include/
printf " --> ${BLUE} SimpleGL installation finished!${ENDCOLOR}\n"
printf " --> ${BLUE} Use library name \`${GREEN}simpleGL${BLUE}\` to link into your projects!${ENDCOLOR}\n"
