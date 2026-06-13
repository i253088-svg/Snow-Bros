# target the libBlaze.a library


cmake_minimum_required(VERSION 3.16) 
project(SnowBros)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(SFML 2.5 COMPONENTS graphics window audio REQUIRED)

add_library(Blaze STATIC IMPORTED)
set_target_properties(Blaze PROPERTIES
    IMPORTED_LOCATION "${CMAKE_CURRENT_SOURCE_DIR}/build/libBlaze.a"
    INTERFACE_INCLUDE_DIRECTORIES "${CMAKE_CURRENT_SOURCE_DIR}/engine"
)

add_executable(SnowBros 
    gameplay/main.cpp
    gameplay/src/vfx.cpp
    gameplay/src/states.cpp
    gameplay/src/menu.cpp
    gameplay/src/hashing.cpp
    gameplay/src/player.cpp
)

target_link_libraries(SnowBros PRIVATE Blaze sfml-graphics sfml-window sfml-audio)


#code to recompile library

#[[
cmake_minimum_required(VERSION 3.16) 
project(SnowBros)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(SFML 2.5 COMPONENTS graphics window audio REQUIRED)

add_library(Blaze 
engine/animation.cpp 
engine/asset.cpp 
engine/level.cpp 
engine/system.cpp 
engine/ui.cpp
)
add_executable(SnowBros gameplay/main.cpp)
target_link_libraries(SnowBros PRIVATE sfml-graphics sfml-window sfml-audio)
]]