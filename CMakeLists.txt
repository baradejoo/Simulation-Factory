cmake_minimum_required(VERSION 3.13)
project(Fabryka)

set(CMAKE_CXX_STANDARD 17)
add_compile_options(-Wall -Wextra -Werror -Wpedantic -pedantic-errors)

include_directories(
        include
)

set(SOURCE_FILES
        src/factory.cpp
        src/package.cpp
        src/storage_types.cpp
        src/nodes.cpp
        src/helpers.cpp)

add_executable(Fabryka__debug ${SOURCE_FILES} fabryka.cpp #src/storage_types.cpp#)
        )

target_compile_definitions(Fabryka__debug PUBLIC EXERCISE_ID=Exercise_id_nodes)

set(SOURCES_FILES_TESTS
        test/test_package.cpp
        test/test_nodes.cpp
        #test/test_Factory.cpp
        #test/test_factory_io.cpp
        #test/test_simulate.cpp
        test/test_storage_types.cpp)

add_executable(Fabryka__test ${SOURCE_FILES} ${SOURCES_FILES_TESTS} test/main_gtest.cpp)

target_include_directories(Fabryka__test PUBLIC
        ../../googletest-master/googlemock/include
        ../../googletest-master/googletest/include
        )

add_subdirectory(googletest-master)

target_link_libraries(Fabryka__test gmock)

