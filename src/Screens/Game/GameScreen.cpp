#include "GameScreen.h"
#include "GameUIPanel.h"
#include "GameOverUIPanel.h"
#include "../../Engine/WorldState.h"
#include "../../GameObjects/GameObject.h"
#include "../../GameObjects/BulletUpdateComponent.h"
#include "../../GameObjects/InvaderUpdateComponent.h"

class BulltetSpawner;

int WorldState::WORLD_HEIGHT;
int WorldState::NUM_INVADERS;
int WorldState::NUM_INVADERS_AT_START;
int WorldState::LIVES;
int WorldState::SCORE;

bool GameScreen::m_GameOver = false;

GameScreen::GameScreen(ScreenManagerRemoteControl *smrc, Vector2i res) {
  m_GIH = make_shared<GameInputHandler>();
  auto guip = make_unique<GameUIPanel>(res);
  addPanel(move(guip), smrc, m_GIH);

  auto m_GOIH = make_shared<GameOverInputHandler>();
  auto gouip = make_unique<GameOverUIPanel>(res);
  addPanel(move(gouip), smrc, m_GOIH);

  m_ScreenManagerRemoteControl = smrc;

  float screenRatio = VideoMode::getDesktopMode().width /
          VideoMode::getDesktopMode().height;
  WorldState::WORLD_HEIGHT = WorldState::WORLD_WIDTH / screenRatio;
  m_View.setSize(WorldState::WORLD_WIDTH, WorldState::WORLD_HEIGHT);
  m_View.setCenter(Vector2f(WorldState::WORLD_WIDTH / 2,
                            WorldState::WORLD_HEIGHT / 2));

  m_BackgroundTexture.loadFromFile("resources/graphics/background.png");
  m_BackgroundSprite.setTexture(m_BackgroundTexture);
  auto textureSize = m_BackgroundSprite.getTexture()->getSize();
  m_BackgroundSprite.setScale(float(m_View.getSize().x) / textureSize.x,
                              float(m_View.getSize().y) / textureSize.y);
}

void GameScreen::initialise() {
  m_GIH->initialize();
  m_PhysicsEnginePlayMode.initialize(m_ScreenManagerRemoteControl->
                                     shareGameObjectSharer());
  WorldState::NUM_INVADERS = 0;
  int i = 0;
  for (GameObject& object : m_ScreenManagerRemoteControl->getGameObjects()) {
    if (object.getTag() == "bullet") {
      m_BulletObjectLocations.push_back(i);
    }
    if (object.getTag() == "invader") {
      static_pointer_cast<InvaderUpdateComponent>(
              object.getFirstUpdateComponent())->initializeBulletSpawner(
                      getBulletSpawner(), i);
      WorldState::NUM_INVADERS++;
    }
    i++;
  }
  m_GameOver = false;
  if (WorldState::WAVE_NUMBER == 0) {
    WorldState::NUM_INVADERS_AT_START = WorldState::NUM_INVADERS;
    WorldState::WAVE_NUMBER = 1;
    WorldState::LIVES = 3;
    WorldState::SCORE = 0;
  }
}

void GameScreen::update(float fps) {
  Screen::update(fps);
  if (!m_GameOver) {
    if (m_WaitingToSpawnBulletForPlayer) {
      static_pointer_cast<BulletUpdateComponent>(m_ScreenManagerRemoteControl->
        getGameObjects()[m_BulletObjectLocations[m_NextBullet]].
          getFirstUpdateComponent())->spawnForPlayer(m_PlayerBulletSpawnLocation);
      m_WaitingToSpawnBulletForPlayer = false;
      m_NextBullet = (m_NextBullet + 1) % (int)m_BulletObjectLocations.size();
    }
    if (m_WaitingToSpawnBulletForInvader) {
      static_pointer_cast<BulletUpdateComponent>(m_ScreenManagerRemoteControl->
        getGameObjects()[m_BulletObjectLocations[m_NextBullet]].
          getFirstUpdateComponent())->spawnForInvader(m_InvaderBulletSpawnLocation);
      m_WaitingToSpawnBulletForInvader = false;
      m_NextBullet = (m_NextBullet + 1) % (int)m_BulletObjectLocations.size();
    }

    for (GameObject& object : m_ScreenManagerRemoteControl->getGameObjects()) {
      object.update(fps);
    }

    m_PhysicsEnginePlayMode.detectCollisions(
            m_ScreenManagerRemoteControl->getGameObjects(),
            m_BulletObjectLocations);

    if (WorldState::NUM_INVADERS <= 0) {
      WorldState::WAVE_NUMBER++;
      m_ScreenManagerRemoteControl->loadLevelInPlayMode("level1");
    }
    if (WorldState::LIVES <= 0)
      m_GameOver = true;
  }
}

void GameScreen::draw(RenderWindow &window) {
  window.setView(m_View);
  window.draw(m_BackgroundSprite);
  for (GameObject object : m_ScreenManagerRemoteControl->getGameObjects()) {
    object.draw(window);
  }
  Screen::draw(window);
}

BulletSpawner *GameScreen::getBulletSpawner() {
  return this;
}

void GameScreen::spawnBullet(Vector2f spawnLocation, bool forPlayer) {
  if (forPlayer) {
    Time elapsedTime = m_BulletClock.getElapsedTime();
    if (elapsedTime.asMilliseconds() > 500) {
      m_PlayerBulletSpawnLocation.x = spawnLocation.x;
      m_PlayerBulletSpawnLocation.y = spawnLocation.y;
      m_WaitingToSpawnBulletForPlayer = true;
      m_BulletClock.restart();
    }
  }
  else {
    m_InvaderBulletSpawnLocation.x = spawnLocation.x;
    m_InvaderBulletSpawnLocation.y = spawnLocation.y;
    m_WaitingToSpawnBulletForInvader = true;
  }
}
