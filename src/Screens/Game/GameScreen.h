#pragma once
#include "../Screen.h"
#include "GameInputHandler.h"
#include "GameOverInputHandler.h"
#include "../../GameObjects/BulletSpawner.h"
#include "../../Engine/PhysicsEnginePlayMode.h"

class GameScreen : public Screen, public BulletSpawner {
private:
  ScreenManagerRemoteControl* m_ScreenManagerRemoteControl;
  shared_ptr<GameInputHandler> m_GIH;
  PhysicsEnginePlayMode m_PhysicsEnginePlayMode;
  int m_NumberInvadersInWorldFile = 0;
  vector<int> m_BulletObjectLocations;
  int m_NextBullet = 0;
  bool m_WaitingToSpawnBulletForPlayer = false;
  bool m_WaitingToSpawnBulletForInvader = false;
  Vector2f m_PlayerBulletSpawnLocation;
  Vector2f m_InvaderBulletSpawnLocation;
  Clock m_BulletClock;
  Texture m_BackgroundTexture;
  Sprite m_BackgroundSprite;

public:
  static bool m_GameOver;

  GameScreen(ScreenManagerRemoteControl* smrc, Vector2i res);
  void initialise() override;
  void update(float fps) override;
  void draw(RenderWindow& window) override;
  BulletSpawner* getBulletSpawner();
  void spawnBullet(Vector2f spawnLocation, bool forPlayer) override;
};
