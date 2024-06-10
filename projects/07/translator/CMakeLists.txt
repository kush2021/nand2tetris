cmake_minimum_required(VERSION 3.28)
project(translator)
set(CMAKE_CXX_STANDARD 17)

find_package(Boost 1.85.0 COMPONENTS algorithm)
include_directories(${Boost_INCLUDE_DIRS})

add_executable(translator
    parser.cpp
    parser.h
    commandType.h
    codeWriter.cpp
    codeWriter.h
    main.cpp)
target_link_libraries(translator ${Boost_LIBRARIES})

find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})

enable_testing()
add_executable(translator_test tests.cpp parser.cpp parser.h
    commandType.h
    codeWriter.cpp
    codeWriter.h)
target_link_libraries(translator_test ${GTEST_LIBRARIES} ${GTEST_MAIN_LIBRARIES})
