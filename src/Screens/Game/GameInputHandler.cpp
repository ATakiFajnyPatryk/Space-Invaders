#include "GameInputHandler.h"
#include "../../Engine/SoundEngine.h"
#include "GameScreen.h"

void GameInputHandler::initialize() {

}

void GameInputHandler::handleGamepad() {

}

void GameInputHandler::handleKeyPressed(Event &event, RenderWindow &window) {
  if (event.key.code == Keyboard::Escape) {
    SoundEngine::playClick();
    getPointerToScreenManagerRemoteControl()->SwitchScreens("Select");
  }
}

void GameInputHandler::handleKeyReleased(Event &event, RenderWindow &window) {

}
