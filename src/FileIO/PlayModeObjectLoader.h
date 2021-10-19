#pragma once
#include <vector>
#include <string>
#include "../GameObjects/GameObject.h"
#include "BlueprintObjectParser.h"
#include "GameObjectFactoryPlayMode.h"

using namespace std;

class PlayModeObjectLoader {
private:
  BlueprintObjectParser m_BOP;
  GameObjectFactoryPlayMode m_GameObjectFactoryPlayMode;

public:
  void loadGameObjectsForPlayMode(string pathToFile,
                                  vector<GameObject>& mGameObjects);
};
