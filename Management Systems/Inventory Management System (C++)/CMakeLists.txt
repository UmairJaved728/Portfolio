cmake_minimum_required(VERSION 3.21)
project(samaha)

set(CMAKE_CXX_STANDARD 14)

add_executable(samaha main.cpp BSTInventory.cpp Inventory.cpp BSTCustomer.cpp)
