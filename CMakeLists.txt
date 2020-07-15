cmake_minimum_required(VERSION 3.15)
project(Pokemon)

set(CMAKE_CXX_STANDARD 14)
set(SFML_STATIC_LIBRARIES, TRUE)
find_package(SFML 2.5 COMPONENTS system window graphics REQUIRED)

add_subdirectory(Google_tests)
set(SOURCE_FILES Trainer.cpp Trainer.h Pokemon.cpp Pokemon.h Type.cpp Type.h Move.cpp Move.h Battle.cpp Battle.h debug.h GameState.cpp GameState.h Tile.cpp Tile.h Map.cpp Map.h Player.cpp Player.h Dice.cpp Dice.h)
add_executable(Pokemon main.cpp)
add_library(core ${SOURCE_FILES})
target_link_libraries(core sfml-system sfml-window sfml-graphics -static)
target_link_libraries(${PROJECT_NAME} core)





