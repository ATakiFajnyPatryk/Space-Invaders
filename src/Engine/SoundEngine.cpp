#include "SoundEngine.h"
#include <assert.h>

using namespace std;

SoundEngine::SoundEngine() {
  assert(m_s_Instance == nullptr);
  m_s_Instance = this;

  m_ShootBuffer.loadFromFile("resources/sound/shoot.ogg");
  m_PlayerExplodeBuffer.loadFromFile("resources/sound/playerexplode.ogg");
  m_InvaderExplodeBuffer.loadFromFile("resources/sound/invaderexplode.ogg");
  m_ClickBuffer.loadFromFile("resources/sound/click.ogg");

  m_ShootSound.setBuffer(m_ShootBuffer);
  m_PlayerExplodeSound.setBuffer(m_PlayerExplodeBuffer);
  m_InvaderExplodeSound.setBuffer(m_InvaderExplodeBuffer);
  m_ClickSound.setBuffer(m_ClickBuffer);
}

void SoundEngine::playShoot() {
  m_s_Instance->m_ShootSound.play();
}

void SoundEngine::playPlayerExplode() {
  m_s_Instance->m_PlayerExplodeSound.play();
}

void SoundEngine::playInvaderExplode() {
  m_s_Instance->m_InvaderExplodeSound.play();
}

void SoundEngine::playClick() {
  m_s_Instance->m_ClickSound.play();
}
