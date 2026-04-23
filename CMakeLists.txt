cmake_minimum_required(VERSION 3.26)
project(search_lab)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O2")

add_executable(search_lab
        src/main.cpp
        src/resident.hpp
        src/linear.hpp
        src/util.hpp
        src/binary_tree.hpp
        src/rb_tree.hpp
        src/hash_table.hpp
)