cmake_minimum_required(VERSION 3.10.0)
project(Order-book LANGUAGES CXX)

add_executable(Order-book src/main.cpp src/OrderBook.cpp)
target_include_directories(Order-book PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/include")

