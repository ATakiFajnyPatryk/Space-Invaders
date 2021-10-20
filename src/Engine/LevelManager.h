#pragma once
#include "../GameObjects/GameObject.h"
#include "../FileIO/GameObjectSharer.h"
#include <vector>
#include <string>

using namespace std;

class LevelManager : public GameObjectSharer {
private:
  vector<GameObject> m_GameObjects;
  const string WORLD_FOLDER = "resources/world";
  const std::string SLASH = "/";
  void runStartPhase();
  void activateAllGameObjects();

public:
  vector<GameObject>& getGameObjects();
  void loadGameObjectsForPlayMode(string screenToLoad);
  vector<GameObject>& getGameObjectsWithGOS() override;
  GameObject& findFirstObjectWithTag(string tag) override;
};
