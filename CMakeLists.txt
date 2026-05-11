cmake_minimum_required(VERSION 3.28)

project(ThePlazza)

set(SRC

)

set(MAIN
        src/main.cpp
)

add_executable(plazza ${SRC} ${MAIN})
target_include_directories(plazza PRIVATE include)
