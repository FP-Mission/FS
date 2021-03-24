#!/bin/bash

#check if an app name is specified
if [[ -z "$1" ]]
then
	echo "Please specify your app name, exiting..."
	exit 1
fi

#Activate the python environnement
. ./fprime-venv/bin/activate

#purge an old app if it exists
cd $1
echo "purging..."; yes | fprime-util purge $2

#now exit on error
set -e

#build the app
echo "generating..."; fprime-util generate $2
echo "building..."; fprime-util build $2

#start the gds if "start" is an argument
if [[ "$1" == "start" ]]
then
	if  [[ $? -eq 0 ]]
	then
		echo "starting gds..."
		fprime-gds
	else
		echo "build failed, gds start aborted"
	fi
fi