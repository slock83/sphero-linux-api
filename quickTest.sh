#!/bin/bash

#Création de la lib
make -B -j16
sudo make install

#Création de l'appli
cd example-app
make -B -j16

#Lancement de l'appli
cp sphero-cli ../sphero-cli
chmod 777 ../sphero-cli
../sphero-cli
