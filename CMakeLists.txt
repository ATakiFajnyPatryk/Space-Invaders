cmake_minimum_required(VERSION 3.10.2)
project(Space-Invaders)

set(CMAKE_CXX_STANDARD 17)
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
        src/Engine/WorldState.h
        src/DevelopState.h
        src/Engine/GameEngine.cpp
        src/Engine/GameEngine.h
        src/Engine/SoundEngine.cpp
        src/Engine/SoundEngine.h
        src/Engine/ScreenManager.cpp
        src/Engine/ScreenManager.h
        src/Engine/BitmapStore.cpp
        src/Engine/BitmapStore.h
        src/Screens/ScreenManagerRemoteControl.cpp
        src/Screens/ScreenManagerRemoteControl.h
        src/Screens/Button.cpp
        src/Screens/Button.h
        src/Screens/UIPanel.cpp
        src/Screens/UIPanel.h
        src/Screens/InputHandler.cpp
        src/Screens/InputHandler.h
        src/Screens/Screen.cpp
        src/Screens/Screen.h
        src/Screens/Select/SelectScreen.cpp
        src/Screens/Select/SelectScreen.h
        src/Screens/Select/SelectInputHandler.cpp
        src/Screens/Select/SelectInputHandler.h
        src/Screens/Select/SelectUIPanel.cpp
        src/Screens/Select/SelectUIPanel.h
        src/Screens/Game/GameScreen.cpp
        src/Screens/Game/GameScreen.h
        src/Screens/Game/GameInputHandler.cpp
        src/Screens/Game/GameInputHandler.h
        src/Screens/Game/GameUIPanel.cpp
        src/Screens/Game/GameUIPanel.h
        src/Screens/Game/GameOverInputHandler.cpp
        src/Screens/Game/GameOverInputHandler.h
        src/Screens/Game/GameOverUIPanel.cpp
        src/Screens/Game/GameOverUIPanel.h
        src/GameObjects/Component.cpp
        src/GameObjects/Component.h
        src/GameObjects/ColliderComponent.cpp
        src/GameObjects/ColliderComponent.h
        src/GameObjects/RectColliderComponent.cpp
        src/GameObjects/RectColliderComponent.h
        src/GameObjects/GraphicsComponent.cpp
        src/GameObjects/GraphicsComponent.h
        src/GameObjects/StandardGraphicsComponent.cpp
        src/GameObjects/StandardGraphicsComponent.h
        src/GameObjects/TransformComponent.cpp
        src/GameObjects/TransformComponent.h
        src/GameObjects/UpdateComponent.cpp
        src/GameObjects/UpdateComponent.h
        src/GameObjects/BulletUpdateComponent.cpp
        src/GameObjects/BulletUpdateComponent.h
        src/GameObjects/InvaderUpdateComponent.cpp
        src/GameObjects/InvaderUpdateComponent.h
        src/GameObjects/PlayerUpdateComponent.cpp
        src/GameObjects/PlayerUpdateComponent.h
        src/GameObjects/GameObject.cpp
        src/GameObjects/GameObject.h
        src/FileIO/GameObjectBlueprint.cpp
        src/FileIO/GameObjectBlueprint.h
        src/FileIO/ObjectTags.cpp
        src/FileIO/ObjectTags.h
        src/FileIO/BlueprintObjectParser.cpp
        src/FileIO/BlueprintObjectParser.h
        src/FileIO/PlayModeObjectLoader.cpp
        src/FileIO/PlayModeObjectLoader.h
        src/FileIO/GameObjectFactoryPlayMode.cpp
        src/FileIO/GameObjectFactoryPlayMode.h
        src/FileIO/GameObjectSharer.cpp
        src/FileIO/GameObjectSharer.h
        src/Engine/LevelManager.cpp
        src/Engine/LevelManager.h
        src/GameObjects/BulletSpawner.cpp
        src/GameObjects/BulletSpawner.h
        src/Engine/PhysicsEnginePlayMode.cpp
        src/Engine/PhysicsEnginePlayMode.h)

add_executable(Space-Invaders ${SOURCE_FILES})
target_link_libraries(Space-Invaders sfml-graphics sfml-window sfml-system sfml-audio)