cmake_minimum_required(VERSION 3.28)

project(ThePlazza LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(SRC
        src/Constants.cppm
        src/Reception.cpp
)

set(MAIN
        src/main.cpp
)

add_executable(plazza  ${SRC} ${MAIN})

target_include_directories(plazza PRIVATE include)
