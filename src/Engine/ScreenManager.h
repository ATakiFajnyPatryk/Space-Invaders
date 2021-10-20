#pragma once
#include <SFML/Graphics.hpp>
#include <map>
#include "../Screens/Game/GameScreen.h"
#include "../Screens/ScreenManagerRemoteControl.h"
#include "../Screens/Select/SelectScreen.h"
#include "LevelManager.h"
#include "BitmapStore.h"
#include <iostream>

using namespace sf;
using namespace std;

class ScreenManager : public ScreenManagerRemoteControl {
private:
  map<string, unique_ptr<Screen>> m_Screens;
  LevelManager m_LevelManager;

protected:
  string m_CurrentScreen = "Select";

public:
  BitmapStore m_BS;

  ScreenManager(Vector2i res);
  void update(float fps);
  void draw(RenderWindow& window);
  void handleInput(RenderWindow& window);

  void SwitchScreens(string screenToSwitchTo) override;

  void loadLevelInPlayMode(string screenToLoad) override;

  vector<GameObject>& getGameObjects() override;

  GameObjectSharer& shareGameObjectSharer() override;
};

