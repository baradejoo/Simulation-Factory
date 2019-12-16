cmake_minimum_required(VERSION 3.13)
project(Fabryka)

set(CMAKE_CXX_STANDARD 17)
add_compile_options(-Wall -Wextra -Werror -Wpedantic -pedantic-errors)

include_directories(
        include
)

set(SOURCE_FILES
        src/package.cpp
        )

add_executable(Fabryka__debug ${SOURCE_FILES} fabryka.cpp)

#set(SOURCES_FILES_TESTS
#        test/test_vector.cpp
#        test/test_matrix.cpp
#        )

add_executable(Fabryka__test ${SOURCE_FILES} ${SOURCES_FILES_TESTS} test/main_gtest.cpp test/test_package.cpp)

target_include_directories(Fabryka__test PUBLIC
        ../../googletest-master/googlemock/include
        ../../googletest-master/googletest/include
        )

add_subdirectory(../googletest-master googletest-master)

target_link_libraries(Fabryka__test gmock)
