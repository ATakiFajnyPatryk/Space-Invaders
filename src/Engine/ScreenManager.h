#pragma once
#include <SFML/Graphics.hpp>
#include <map>
#include "GameScreen.h"
#include "../Screens/ScreenManagerRemoteControl.h"
#include "SelectScreen.h"
//#include "LevelManager.h"
#include "BitmapStore.h"
#include <iostream>

using namespace sf;
using namespace std;

class ScreenManager : public ScreenManagerRemoteControl {
private:
  map<string, unique_ptr<Screen>> m_Screens;
  //LevelManager m_LevelManager;

protected:
  string m_CurrentScreen = "Select";

public:
  BitmapStore m_BS;

  ScreenManager(Vector2i res);
  void update(float fps);
  void draw(RederWindow& window);
  void handleInput(RenderWindow& window);

  /****************************************************
  *****************************************************
  From ScreenManagerRemoteControl interface
  *****************************************************
  ****************************************************/

  void SwitchScreens(string screenToSwitchTo) override {
    m_CurrentScreen = "" + screenToSwitchTo;
    m_Screens[m_CurrentScreen]->initialise();
  }

  void loadLevelInPlayMode(string screenToLoad) override {
    //m_LevelManager.getGameObjects.clear();
    //m_LevelManager.loadGameObjectsForPlayMode(screenToLoad);
    SwitchScreens("Game");
  }

  //vector<GameObject> & getGameObjects() override {
    //return m_LevelManager.getGameObjects()'
  //}

  //GameObjectsSharer& shareGameObjectSharer() override {
    //return LevelManager;
  //}
};

