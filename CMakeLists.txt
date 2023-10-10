cmake_minimum_required(VERSION 3.26)
project(CFrpController)

set(CMAKE_CXX_STANDARD 23)

add_library(CFrpController SHARED
        main.cpp
        cpptoml.h
        Classes.h
        Classes.cpp
        ProcessLauncher.h
        ProcessLauncher.cpp)