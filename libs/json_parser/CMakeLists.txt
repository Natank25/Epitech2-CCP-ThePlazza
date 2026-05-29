cmake_minimum_required(VERSION 3.10)

project(json_parser LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(JSON_PARSER_SOURCES
        src/Json.cpp
        src/JsonCore.cpp
        src/JsonString.cpp
        src/JsonNumber.cpp
        src/JsonArray.cpp
        src/JsonObject.cpp
)

add_library(json_parser STATIC ${JSON_PARSER_SOURCES})

target_include_directories(json_parser
        PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        $<INSTALL_INTERFACE:include>
)

target_compile_options(json_parser PRIVATE -Wall -Wextra -Werror -g3)

set_target_properties(json_parser PROPERTIES
        OUTPUT_NAME json_parser
)
