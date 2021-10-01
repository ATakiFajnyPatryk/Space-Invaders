cmake_minimum_required(VERSION 3.10.2)
project(Space-Invaders)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -static-libstdc++ -static-libgcc")

set(SFML_INCLUDE_DIR "/home/Libraries/SFML-2.5.1-Compiled/include")
set(SFML_LIBRARY_DIR "/home/Libraries/SFML-2.5.1-Compiled/lib")
set(SFML_DIR "/home/Libraries/SFML-2.5.1-Compiled/lib/cmake/SFML")

link_directories(SFML_LIBRARY_DIR)
include_directories(SFML_INCLUDE_DIR)

find_package(SFML 2.5.1 COMPONENTS system window graphics network audio)

if(SFML_FOUND)
    message(STATUS "SFML_INCLUDE_DIR: ${SFML_INCLUDE_DIR}")
    message(STATUS "SFML_LIBRARIES: ${SFML_LIBRARIES}")
    message(STATUS "SFML_VERSION: ${SFML_VERSION}")
endif()

file(COPY resources DESTINATION ${CMAKE_BINARY_DIR})

set(SOURCE_FILES
        src/Engine/SpaceInvaders++.cpp
        src/DevelopState.h src/Engine/GameEngine.cpp src/Engine/GameEngine.h src/Engine/SoundEngine.cpp src/Engine/SoundEngine.h src/Engine/ScreenManager.cpp src/Engine/ScreenManager.h src/Engine/BitmapStore.cpp src/Engine/BitmapStore.h src/Screens/ScreenManagerRemoteControl.cpp src/Screens/ScreenManagerRemoteControl.h)

add_executable(Space-Invaders ${SOURCE_FILES})
target_link_libraries(Space-Invaders sfml-graphics sfml-window sfml-system sfml-audio)