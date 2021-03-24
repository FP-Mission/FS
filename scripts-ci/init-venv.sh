#!/bin/bash

#stop on error
set -e

#create the venv
python3 -m venv ./fprime-venv

#activate the venv
. ./fprime-venv/bin/activate

#build the venv
pip install --upgrade wheel setuptools pip
cd fprime/
pip install ./Fw/Python
pip install ./Gds

#deactivate the venv
deactivate
