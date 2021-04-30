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

#purge an old app if it exists.
cd $1
base_directory=$(pwd)
echo "purging..."; yes | fprime-util purge

#now exit on error
set -e

#generate the build folder for UT
echo "generating..."; fprime-util generate --ut

echo "Searchign Unit Test on $base_directory..."
#get directories that have test in them
dirs=$((find $base_directory -type d -name "ut" -not -path "$base_directory/build-*" | sed -e 's/\<test\/ut\>//g'))
#number of dirs
processed_tests=${#dirs[@]}

echo -e "\n\n\nfound directories : "
for dir in "${dirs[@]}"
do
	echo -e "$dir"
done
echo -e "\n\n\n"

#iterate over directories to build their UT
for dir in "${dirs[@]}"
do
	cd $dir
	fprime-util build --ut
done

#iterate over directories to check their tests
for dir in "${dirs[@]}"
do
	echo -e "\n\nChecking component with unit test : $dir"
	cd $dir
	fprime-util check
done


echo -e "\n\nTotal : Checked $processed_tests components for unit tests"