#!/bin/bash


#check if an app name is specified
if [[ -z "$1" ]]
then
	echo "Please specify your app name, exiting..."
	exit 1
fi

#activate the python environnement
. ./fprime-venv/bin/activate

#purge an old app if it exists
cd $1
echo "purging..."; yes | fprime-util purge

#build project
echo "building..."
sudo fprime-util generate
sudo fprime-util build


#now exit on error
set -e

#build the app
echo "generating..."; fprime-util generate --ut
fprime-util check --all
