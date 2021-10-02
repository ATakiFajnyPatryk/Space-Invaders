#include "SelectInputHandler.h"
#include "../../Engine/SoundEngine.h"
#include "../../Engine/WorldState.h"
#include <iostream>

int WorldState::WAVE_NUMBER;

void SelectInputHandler::handleKeyPressed(Event &event, RenderWindow &window) {
  if (Keyboard::isKeyPressed(Keyboard::Escape))
    window.close();
}

void SelectInputHandler::handleLeftClick(string &buttonInteractWith,
                                         RenderWindow &window) {
  if (buttonInteractWith == "Play") {
    SoundEngine::playClick();
    WorldState::WAVE_NUMBER = 0;
    getPointerToScreenManagerRemoteControl()->loadLevelInPlayMode("level1");
  }

  if (buttonInteractWith == "Quit") {
    SoundEngine::playClick();
    window.close();
  }
}
