
cmake_minimum_required(VERSION 3.20)

project(Lab5 LANGUAGES CXX)

# Sanitizers are opt-in to keep ordinary release builds unchanged.
option(ENABLE_SANITIZERS "Enable AddressSanitizer and UndefinedBehaviorSanitizer" OFF)
if(ENABLE_SANITIZERS)
    if(NOT CMAKE_CXX_COMPILER_ID MATCHES "^(Clang|GNU)$")
        message(FATAL_ERROR "ENABLE_SANITIZERS requires Clang or GCC")
    endif()
    if(NOT CMAKE_BUILD_TYPE STREQUAL "Debug")
        message(FATAL_ERROR "ENABLE_SANITIZERS requires CMAKE_BUILD_TYPE=Debug (assertions enabled)")
    endif()
    add_compile_options(-fsanitize=address,undefined -fno-omit-frame-pointer -fno-sanitize-recover=all)
    add_link_options(-fsanitize=address,undefined -fno-omit-frame-pointer -fno-sanitize-recover=all)
endif()

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