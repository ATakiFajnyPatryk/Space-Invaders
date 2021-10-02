#pragma once
#include "../InputHandler.h"

using namespace std;

class SelectInputHandler : public InputHandler {
public:
  void handleKeyPressed(Event& event, RenderWindow& window) override;
  void handleLeftClick(string& buttonInteractWith, RenderWindow& window) override;
};
