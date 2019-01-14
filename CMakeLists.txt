cmake_minimum_required(VERSION 3.9.6)
project(FinalPorject)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

include_directories("/usr/local/include")
LINK_DIRECTORIES(  "/usr/local/Cellar/allegro/5.2.4.0/lib" )
add_executable(FinalPorject main.cpp objects/character.cpp
        objects/character.h Interface/View.cpp Interface/View.h
        objects/Hud.cpp objects/Hud.h
        config.h Interface/Object.cpp Interface/Object.h)

file(GLOB LIBRARIES "/usr/local/Cellar/allegro/5.2.4.0/lib/*5.2.4.dylib")
TARGET_LINK_LIBRARIES(FinalPorject  ${LIBRARIES})
