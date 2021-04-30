# FS - F' Flight software

This is the main repository of the CHESS flight software. It uses the [NASA F' framework](https://github.com/nasa/fprime)

## Getting Started

Read [F´ Discerning User’s Guide](https://nasa.github.io/fprime/UsersGuide/guide.html) to discover the framework. [Tutorials](https://nasa.github.io/fprime/Tutorials/README.html) are a very good way to understand it.

More resources (Community Forum, Reference Application, F' Architecture Overview) are available on [nasa.github.io/fprime](https://nasa.github.io/fprime/)

Follow this guide to start with CHESS FS development : [Quick start guide](https://hackmd.io/@jonathanmichel/SyKt6xV9v)

### Prerequisites
- Linux based OS (Ubuntu 18.04 via [WSL2](https://docs.microsoft.com/en-us/windows/wsl/install-win10) in our case)
- GCC compiler GCC 7.5.0
- CMake 3.5 or newer (3.10.2 used)
- Python 3.5+, PIP and Python Virtual Environment

### Installing

See [Quick start guide](https://hackmd.io/@jonathanmichel/SyKt6xV9v) for details.

F' tools installation

```
python3 -m venv ./fprime-venv
. ./fprime-venv/bin/activate
python3 -m pip install --upgrade wheel setuptools pip
cd fprime
python3 -m pip install ./Fw/Python ./Gds
```

F' compilation

Before compiling, you need to know if the flight sofrware will be used with the FPrime GDS or PUS demonstrator.

In ./App/CMakeLists.txt comment and uncomment your choice

```cmake=
add_definitions(-D_PUS)     # to use PUS with GS
#add_definitions(-D_GDS)    # to use F' GDS (without PUS)
```
fprime-util generate
fprime-util build
```

Launch F' and GDS (Ground Software simulator)

Prerequisites
1. Run ADCS simulator
2. Run EPS simulator

```
fprime-gds
```

## simulators
### ADCS
#### Installing
​```bash
pip install python-statemachine
```
#### Running ADCS simulator
```bash
python3 ./simulators/ADCS/TcpMain.py
```

### EPS
#### Installing
```bash
pip install python-statemachine
sudo apt install libsocketcan-dev pkg-config libzmq3-dev 
```
#### Running EPS simulator
```bash
sudo chmod +x ./simulators/EPS/zmqproxy
sudo ./simulators/EPS/zmqproxy &
export LD_LIBRARY_PATH=./simulators/EPS/packages/csp/lib && python3 ./simulators/EPS/CspMain.py
```

## Demonstrator
### Prerequisites
1. Run ADCS simulator
2. Run EPS simulator

## Running Demonstrator
```bash
cd /gs/gs
cmake .
make 
./gs
```
The demonstrator is a TCP server. It will wait for a connection from Flight software and then, start sending and receiving packets
### Running flight software with demonstrator
```bash
./App/build-artifacts/Linux/bin/App -a 127.0.0.1 -p 27015
```

## Running the tests

In `05_FS/App` run

```
fprime-util check --all
```

## Deployment

FS can be build and deployed on a Raspberry Pi with 

```
fprime-util generate raspberrypi
fprime-util build raspberrypi
```

You will need [Raspberry Pi toolchain](https://github.com/raspberrypi/tools) in `/opt/rpi`.

Binary generated in `App/bin/arm-linux-gnueabihf/App` can be launched on the Pi after having started GDS without application on Linux

```
fprime-gds -n
```

See [GPS tutorial](https://nasa.github.io/fprime/Tutorials/GpsTutorial/Tutorial.html) for details.

F' also provide a custom topology RPI to test it on a Raspberry Pi, see [here](https://github.com/nasa/fprime/blob/master/RPI/README.md).

## Authors

  - **Jonathan Michel** - *HES-SO Master student* -
    [@jonathanmichel](https://github.com/jonathanmichel)
  - **Charles-Lewis Jaggi** - *HES-SO Master student* - [@lewisjaggi](https://github.com/lewisjaggi)
  - **Maxime Welcklen** - *HES-SO Bachelor student* - [@maximewel](https://github.com/maximewel)
