cmake_minimum_required(VERSION 3.13)
project(FinalPorject)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

include_directories("C:/Users/xray0/allegro-5.0.10-mingw-4.7.0/include")
LINK_DIRECTORIES(  C:/Users/xray0/allegro-5.0.10-mingw-4.7.0/lib )
add_executable(FinalPorject main.cpp objects/character.cpp objects/character.h Interface/View.cpp Interface/View.h config.h Interface/Object.cpp Interface/Object.h)

file(GLOB LIBRARIES "C:/Users/xray0/allegro-5.0.10-mingw-4.7.0/bin/*debug.dll")
TARGET_LINK_LIBRARIES(FinalPorject  ${LIBRARIES})
