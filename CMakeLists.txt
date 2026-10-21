cmake_minimum_required(VERSION 3.16)
project(bakery_oop LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_library(bakery
    src/product.cpp
    src/bread.cpp
    src/pastry.cpp
    src/cake.cpp
    src/cart.cpp
    src/product_factory.cpp
)
target_include_directories(bakery PUBLIC include)

if(CMAKE_CXX_COMPILER_ID MATCHES "Clang|GNU")
    target_compile_options(bakery PRIVATE -Wall -Wextra -Wpedantic)
endif()

add_executable(bakery_demo src/main.cpp)
target_link_libraries(bakery_demo PRIVATE bakery)

include(CTest)
if(BUILD_TESTING)
    add_executable(bakery_tests tests/bakery_tests.cpp)
    target_link_libraries(bakery_tests PRIVATE bakery)
    add_test(NAME bakery_tests COMMAND bakery_tests)
endif()
