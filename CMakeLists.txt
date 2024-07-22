cmake_minimum_required(VERSION 3.26)
project(Frisen 
        DESCRIPTION "Game engine development project, mainly based on two books : Game Engine Architecture by Jason Gregory and Modern CMake for C++ by Rafal Świdziński."  
        HOMEPAGE_URL https://github.com/tgrillon/Frisen.git 
        LANGUAGES CXX)

message(STATUS "Project URL : " ${PROJECT_HOMEPAGE_URL})
message(STATUS "Project Description : " ${PROJECT_DESCRIPTION})

# Setting the CXX standard support
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Interprocedural optimization
include(CheckIPOSupported)
check_ipo_supported(RESULT ipo_supported)
set(CMAKE_INTERPROCEDURAL_OPTIMIZATION ${ipo_supported})