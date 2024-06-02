cmake_minimum_required(VERSION 3.28)
project(hack_assembler)
set(CMAKE_CXX_STANDARD 17)

find_package(Boost 1.85.0 COMPONENTS algorithm)

include_directories(${Boost_INCLUDE_DIRS})

add_executable(hack_assembler main.cpp parser.h parser.cpp
    commandType.cpp
    commandType.h
    code.h
    code.cpp
    symbolTable.cpp
    symbolTable.h)

target_link_libraries(hack_assembler ${Boost_LIBRARIES})

find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})

enable_testing()
add_executable(assembler_test tests.cpp parser.h parser.cpp
    commandType.cpp
    commandType.h
    code.h
    code.cpp
    symbolTable.cpp
    symbolTable.h)
target_link_libraries(assembler_test ${GTEST_LIBRARIES} ${GTEST_MAIN_LIBRARIES})
