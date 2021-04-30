#!/bin/bash


#check if an app name is specified
if [[ -z "$1" ]]
then
	echo "Please specify your app name, exiting..."
	exit 1
fi

if [ -z "$2" ]
then
#Activate the python environnement
. ./fprime-venv/bin/activate

#Install Wiring pi
sudo git clone https://github.com/WiringPi/WiringPi.git
cd WiringPi
sudo ./build
cd ..
fi

#purge an old app if it exists
cd $1
echo "purging..."; yes | fprime-util purge


#now exit on error
set -e

#build the app
echo "generating..."; fprime-util generate --ut
fprime-util check --all
