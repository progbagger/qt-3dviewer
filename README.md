# 3D Viewer

## Description

**QT**-implemented **C/C++** application with basic GUI that allows to open `.obj` files and see its frames and vertexes.

## Installation

**Note** that this application runs only on **Linux** and **MacOS** systems.

### Required packages

To build this application on your PC you will need next packages and libraries:

- **QT** library (version 5+)
- **QMake** - make sure your `qmake6` takes place in QT library folder
- **gcc** and **g++** **C/C++** compilers
- packages **libgl1-mesa-dev** and **libglu1-mesa-dev** on **Linux**

### Makefile essential targets

- `make install` will create **App** folder where will be situated an executable of application
- `make uninstall` will delete this folder
- `make clean` deletes all build files
- `make dvi` opens documentation for application
- `make dist` creates an archive with all source code files

So, to create an executable and clean all junk just run `make install clean`.

## Tests

To run functional tests you will need **gtest** framework library for **C++** language.

To run style and other tests you will need **clang-format** and **valgrind** on Linux, **leaks** on MacOS executables.

For creating code coverage report you will need **lcov** package.
