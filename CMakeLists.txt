cmake_minimum_required(VERSION 3.15)
project(Pokemon)

set(CMAKE_CXX_STANDARD 14)
set(SFML_STATIC_LIBRARIES, TRUE)
find_package(SFML 2.5 COMPONENTS system window graphics)

add_executable(Pokemon main.cpp TileMap.cpp TileMap.h Trainer.cpp Trainer.h Map.cpp Map.h CollisionMap.cpp CollisionMap.h)
target_link_libraries(Pokemon sfml-system sfml-window sfml-graphics -static)