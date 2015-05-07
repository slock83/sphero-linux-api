#!/bin/bash

#Création de la lib
make -B

#Création de l'appli
cd apps
make -B

#Lancement de l'appli
cp Appli ../testAppLastBuild
chmod 777 ../testAppLastBuild
../testAppLastBuild
