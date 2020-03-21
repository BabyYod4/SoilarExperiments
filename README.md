# VSCode Remote Workspace 

## Introduction:
This is a cmake workspace for working with a RaspberryPi and Wiring Pi. The folder structure is as followed
```bash
├── bin --> contains executables
├── build --> contains build files makde by cmake 
├── lib --> contain generated and used library files
└── src --> conains all base source code
    ├── CMakeLists.txt --> used to configure libary to work with source code 
    └── main.cpp
├── run --> used to compile and execute code
├── CMakeLists.txt --> contain global variables, etc
```

## Before Usage:

### Installing WiringPi
`sudo apt-get install wiringpi`

### Installing CMake
`sudo apt-get install cmake`

### Making CMake find WiringPi
1. `cd /usr/share/cmake-XXX/Modules`
    - Here cmake-XXX is the version of cmake installed 
2. `sudo nano FindWiringPi.cmake`
    - Add the following to the file and save with `Ctrl + X`: 
    ```bash
    find_library(WIRINGPI_LIBRARIES NAMES wiringPi)
    find_path(WIRINGPI_INCLUDE_DIRS NAMES wiringPi.h)

    include(FindPackageHandleStandardArgs)
    find_package_handle_standard_args(wiringPi DEFAULT_MSG WIRINGPI_LIBRARIES WIRINGPI_INCLUDE_DIRS)
    ```

### *optional* Changing project name
To use the workspace, you should take do the following. 

In the workspace folder: 
- Open the file 'run' and change {A NAME HERE} in the line "EXEC_NAME={A NAME HERE}"
to a custom executable name. In this guide we will refer to this name as 'UNAME'.

- Open the file 'CMakeLists.txt' and change "CmakeTest" in the line "set ( PROJECT_NAME_ "CmakeTest" )" to the UNAME.


## Usage:
To test the program or use the build envoirments execute the following commands into the cloned folder

```bash
### Only need to be performed once if no build folder present!
mkdir build
cd build 
cmake ..

cd ..

### Needs to be performed anytime you updated the code. 

## Compiling and Running the executable 
./run 

## if you get a premission error 
sudo chmod +x run
./run

```

You can use source and header files from the sub folder in the following ways:
```c++
#include "foo.hpp"
#include "test/test.hpp"
```

## Example Code

```c++
// foo.hpp
#ifndef FOO_HPP
#define FOO_HPP

class foo{
private:
    int bar;
public: 
    foo();
    int test();

};

#endif //FOO_HPP

// test/test.hpp
#ifndef TEST_HPP
#define TEST_HPP

class test
private:
    int num;
public: 
    test();
    int print();

};

#endif //TEST_HPP

// main.cpp
#include "foo.hpp"
#include "test/test.hpp"

int main(){
    foo bar;
    test t;
    
    std::cout << foo.test();
    std::cout << t.print();

    return 0;
}
``` 
