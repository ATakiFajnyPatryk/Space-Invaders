#include "Screen.h"

void Screen::addPanel(unique_ptr<UIPanel> uip, ScreenManagerRemoteControl *smrc,
                      shared_ptr<InputHandler> ih) {
  ih->initaliseInputHandler(smrc, uip->getButtons(), &(uip->m_View), this);
  m_Panels.push_back(move(uip));
  m_InputHandlers.push_back(ih);
}

void Screen::initialise() {}

void Screen::update(float fps) {}

void Screen::draw(RenderWindow &window) {
  for (const auto& panel : m_Panels)
    panel->draw(window);
}

void Screen::handleInput(RenderWindow &window) {
  Event event;
  while (window.pollEvent(event))
    for (const auto& inputHandler : m_InputHandlers)
      inputHandler->handleInput(window, event);
}
