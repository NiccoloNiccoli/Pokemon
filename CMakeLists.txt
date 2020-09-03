cmake_minimum_required(VERSION 3.15)
project(Pokemon)

set(CMAKE_CXX_STANDARD 20)
set(SFML_STATIC_LIBRARIES, TRUE)
find_package(SFML 2.5 COMPONENTS system window graphics REQUIRED)

add_subdirectory(Google_tests)
set(SOURCE_FILES Trainer.cpp Trainer.h Pokemon.cpp Pokemon.h Type.cpp Type.h Move.cpp Move.h Battle.cpp Battle.h Tile.cpp Tile.h Map.cpp Map.h Player.cpp Player.h Dice.cpp Dice.h Game.cpp Game.h State.h StateBattle.cpp StateBattle.h StatePokemonCenter.cpp StatePokemonCenter.h StateMap.cpp StateMap.h AnimatedSprite.cpp AnimatedSprite.h StateMainMenu.cpp StateMainMenu.h NPC.cpp NPC.h BattleUIStates.cpp BattleUIStates.h StatePauseMenu.cpp StatePauseMenu.h)
add_executable(Pokemon main.cpp)
add_library(core ${SOURCE_FILES})
target_link_libraries(core sfml-system sfml-window sfml-graphics sfml-audio)
target_link_libraries(${PROJECT_NAME} core)







