
cmake_minimum_required(VERSION 3.20)

project(Lab5 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_executable(Lab5
    main.cpp
    BST.cpp
    node.cpp
)

# Enable compiler warnings
if(MSVC)
    target_compile_options(Lab5 PRIVATE /W4 /WX)
else()
    target_compile_options(Lab5 PRIVATE -Wall -Wextra -Werror)
endif()