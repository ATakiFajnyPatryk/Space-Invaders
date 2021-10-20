#include "ScreenManager.h"

#include <memory>

ScreenManager::ScreenManager(Vector2i res) {
  m_Screens["Game"] = std::make_unique<GameScreen>(this, res);
  m_Screens["Select"] = std::make_unique<SelectScreen>(this, res);
}

void ScreenManager::update(float fps) {
  m_Screens[m_CurrentScreen]->update(fps);
}

void ScreenManager::draw(RenderWindow& window) {
  m_Screens[m_CurrentScreen]->draw(window);
}

void ScreenManager::handleInput(RenderWindow &window) {
  m_Screens[m_CurrentScreen]->handleInput(window);
}

void ScreenManager::SwitchScreens(string screenToSwitchTo) {
  m_CurrentScreen = "" + screenToSwitchTo;
  m_Screens[m_CurrentScreen]->initialise();
}

void ScreenManager::loadLevelInPlayMode(string screenToLoad) {
  m_LevelManager.getGameObjects().clear();
  m_LevelManager.loadGameObjectsForPlayMode(screenToLoad);
  SwitchScreens("Game");
}

vector<GameObject>& ScreenManager::getGameObjects() {
  return m_LevelManager.getGameObjects();
}

GameObjectSharer& ScreenManager::shareGameObjectSharer() {
  return m_LevelManager;
}
