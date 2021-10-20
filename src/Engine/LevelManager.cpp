#include "LevelManager.h"
#include "../FileIO/PlayModeObjectLoader.h"
#include "../DevelopState.h"

void LevelManager::runStartPhase() {
  for (GameObject& gameObject : m_GameObjects) {
    gameObject.start(this);
  }

  activateAllGameObjects();
}

void LevelManager::activateAllGameObjects() {
  for (GameObject& gameObject : m_GameObjects) {
    gameObject.setActive();
  }
}

vector<GameObject> &LevelManager::getGameObjects() {
  return m_GameObjects;
}

void LevelManager::loadGameObjectsForPlayMode(string screenToLoad) {
  m_GameObjects.clear();

  string levelToLoad = "" + WORLD_FOLDER + SLASH + screenToLoad;
  PlayModeObjectLoader pmol;
  pmol.loadGameObjectsForPlayMode(levelToLoad, m_GameObjects);
  runStartPhase();
}

vector<GameObject>& LevelManager::getGameObjectsWithGOS() {
  return m_GameObjects;
}

GameObject& LevelManager::findFirstObjectWithTag(string tag) {
  for (GameObject& gameObject : m_GameObjects) {
    if (gameObject.getTag() == tag) {
      return gameObject;
    }
  }

#ifdef debuggingOnConsole
  cout << "LevelManager.h findFirstGameObjectWithTag()- TAG NOT FOUND ERROR!\n";
#endif
  return m_GameObjects[0];
}
