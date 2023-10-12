cmake_minimum_required(VERSION 3.26)
project(CFrpController)

set(CMAKE_CXX_STANDARD 23)

add_library(CFrpController SHARED
        main.cpp
        lib/cpptoml.h
        lib/Classes.h
        lib/Classes.cpp
        lib/ProcessLauncher.h
        lib/ProcessLauncher.cpp)