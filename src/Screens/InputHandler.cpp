#include "InputHandler.h"
#include <sstream>

using namespace sf;
using namespace std;


void InputHandler::initialiseInputHandler(ScreenManagerRemoteControl *sw,
                                         vector<shared_ptr<Button>> buttons,
                                         View *pointerToUIView,
                                         Screen *parentScreen) {
  m_ScreenManagerRemoteControl = sw;
  m_Buttons = buttons;
  m_PointerToUIPanelView = pointerToUIView;
  m_ParentScreen = parentScreen;
}

void InputHandler::handleInput(RenderWindow &window, Event &event) {
  if (event.type == Event::KeyPressed)
    handleKeyPressed(event, window);

  if (event.type == Event::KeyReleased)
    handleKeyReleased(event, window);

  if (event.type == Event::MouseButtonReleased) {
    for (const auto& button : m_Buttons) {
      if (button->m_Collider.contains(window.mapPixelToCoords
         (Mouse::getPosition(), (*getPointerToUIView())))) {
        handleLeftClick(button->m_Text, window);
        break;
      }
    }
  }

  handleGamepad();
}

// Do nothing unless handled by a derived class
void InputHandler::handleGamepad() {}

void InputHandler::handleKeyPressed(Event &event, RenderWindow &window) {}

void InputHandler::handleKeyReleased(Event &event, RenderWindow &window) {}

void InputHandler::handleLeftClick(string &buttonInteractedWith,
                                   RenderWindow &window) {}

View *InputHandler::getPointerToUIView() {
  return m_PointerToUIPanelView;
}

ScreenManagerRemoteControl *
  InputHandler::getPointerToScreenManagerRemoteControl() {
  return m_ScreenManagerRemoteControl;
}

Screen *InputHandler::getParentScreen() {
  return m_ParentScreen;
}
