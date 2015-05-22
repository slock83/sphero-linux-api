#!/bin/bash

#Création de la lib
make -B

#Création de l'appli
cd example-app
make -B

#Lancement de l'appli
cp sphero-cli ../sphero-cli
chmod 777 ../sphero-cli
../sphero-cli
