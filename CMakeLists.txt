cmake_minimum_required(VERSION 3.28)

project(ThePlazza)
option(ENABLE_ASAN "Enable AddressSanitizer" OFF)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(ASAN_FLAGS -fsanitize=address -fno-omit-frame-pointer)

set(SRC
        src/Kitchen/Kitchen.cpp
        src/Kitchen/Stock.cpp
        src/Ingredients/Tomato.cpp
)

set(TESTS_SRC
    tests/test.cpp
)

set(MAIN
    src/main.cpp
)

add_executable(plazza ${SRC} ${MAIN})
target_include_directories(plazza PRIVATE include)

add_executable(unit_tests EXCLUDE_FROM_ALL
    ${SRC}
    ${TESTS_SRC}
)

target_include_directories(unit_tests PRIVATE
    ../include
    src
)

add_custom_target(remove_coverage
    COMMAND find -name "*.gc*" -delete
)

add_custom_target(all_tests
    DEPENDS remove_coverage unit_tests
)

add_custom_target(coverage
    DEPENDS unit_tests
    COMMAND $<TARGET_FILE:unit_tests> && gcovr --root ".." --txt-metric=branch --exclude-unreachable-branches --html-details --html-theme github.dark-green --html-medium-threshold 60 --gcov-executable "llvm-cov gcov" -o coverage/result.html --exclude tests --exclude ../build
)

target_compile_options(unit_tests PRIVATE --coverage -g -O1)
target_link_options(unit_tests PRIVATE --coverage -g -O1)

target_link_libraries(unit_tests criterion)
add_test(NAME unit_tests COMMAND unit_tests)

if (ENABLE_ASAN)
    add_compile_options(${ASAN_FLAGS})
    add_link_options(${ASAN_FLAGS})
endif ()

