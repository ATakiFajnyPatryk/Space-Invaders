#include "../DevelopState.h"
#include "PhysicsEnginePlayMode.h"
#include <iostream>
#include "SoundEngine.h"
#include "WorldState.h"
#include "../GameObjects/InvaderUpdateComponent.h"
#include "../GameObjects/BulletUpdateComponent.h"

void PhysicsEnginePlayMode::detectInvaderCollisions(vector<GameObject> &objects,
                                                    const vector<int> &bulletPositions) {
  Vector2f offScreen(-1, -1);

  for (auto invaderIt = objects.begin(); invaderIt != objects.end(); invaderIt++) {
    if ((*invaderIt).isActive() && (*invaderIt).getTag() == "invader") {
      auto bulletIt = objects.begin();
      advance(bulletIt, bulletPositions[0]);
      for (bulletIt; bulletIt != objects.end(); bulletIt++) {
        if ((*invaderIt).getEncompassingRectCollider().intersects((*bulletIt).
             getEncompassingRectCollider()) && (*bulletIt).getTag() == "bullet"
             && static_pointer_cast<BulletUpdateComponent>(
                     (*bulletIt).getFirstUpdateComponent())->m_BelongsToPlayer) {
          SoundEngine::playInvaderExplode();
          (*invaderIt).getTransformComponent()->getLocation() = offScreen;
          (*bulletIt).getTransformComponent()->getLocation() = offScreen;
          WorldState::SCORE++;
          WorldState::NUM_INVADERS--;
          (*invaderIt).setInactive();
        }
      }
    }
  }
}

void PhysicsEnginePlayMode::detectPlayerCollisionsAndInvaderDirection(
        vector<GameObject> &objects, const vector<int> &bulletPositions) {
  Vector2f offScreen(-1, -1);
  FloatRect playerCollider = m_Player->getEncompassingRectCollider();
  shared_ptr<TransformComponent> playerTransform =
          m_Player->getTransformComponent();

  Vector2f playerLocation = playerTransform->getLocation();
  for (auto it3 = objects.begin(); it3 != objects.end(); it3++) {
    if ((*it3).isActive() && (*it3).hasCollider() && (*it3).getTag() != "Player") {
      FloatRect currentCollider = (*it3).getEncompassingRectCollider();
      if (currentCollider.intersects(playerCollider)) {
        if ((*it3).getTag() == "bullet") {
          SoundEngine::playPlayerExplode();
          WorldState::LIVES--;
          (*it3).getTransformComponent()->getLocation() = offScreen;
        }
        else if ((*it3).getTag() == "invader") {
          SoundEngine::playPlayerExplode();
          SoundEngine::playInvaderExplode();
          WorldState::LIVES--;
          (*it3).getTransformComponent()->getLocation() = offScreen;
          WorldState::SCORE++;
          (*it3).setInactive();
        }
      }

      shared_ptr<TransformComponent> currentTransform =
              (*it3).getTransformComponent();
      Vector2f currentLocation = currentTransform->getLocation();
      string currentTag = (*it3).getTag();
      Vector2f currentSize = currentTransform->getSize();

      if (currentTag == "invader") {
        if (!m_NeedToDropDownAndReverse && !m_InvaderHitWallThisFrame) {
          if (currentLocation.x >= WorldState::WORLD_WIDTH - currentSize.x) {
            if (static_pointer_cast<InvaderUpdateComponent>(
                    (*it3).getFirstUpdateComponent())->isMovingRight()) {
              m_InvaderHitWallThisFrame = true;
            }
          }
          else if (currentLocation.x < 0) {
            if (!static_pointer_cast<InvaderUpdateComponent>(
                    (*it3).getFirstUpdateComponent())->isMovingRight()) {
              m_InvaderHitWallThisFrame = true;
            }
          }
        }
        else if (m_NeedToDropDownAndReverse && !m_InvaderHitWallPreviousFrame) {
          if ((*it3).hasUpdateComponent()) {
            static_pointer_cast<InvaderUpdateComponent>(
                    (*it3).getFirstUpdateComponent())->dropDownAndReverse();
          }
        }
      }
    }
  }
}

void PhysicsEnginePlayMode::handleInvaderDirection() {
  if (m_InvaderHitWallThisFrame) {
    m_NeedToDropDownAndReverse = true;
    m_InvaderHitWallThisFrame = false;
  }
  else {
    m_NeedToDropDownAndReverse = false;
  }
}

void PhysicsEnginePlayMode::initialize(GameObjectSharer &gos) {
  m_PUC = static_pointer_cast<PlayerUpdateComponent>(
          gos.findFirstObjectWithTag("Player").
                  getComponentByTypeAndSpecificType("update", "player"));
  m_Player = &gos.findFirstObjectWithTag("Player");
}

void PhysicsEnginePlayMode::detectCollisions(vector<GameObject> &objects,
                                             const vector<int> &bulletPositions) {
  detectInvaderCollisions(objects, bulletPositions);
  detectPlayerCollisionsAndInvaderDirection(objects, bulletPositions);
  handleInvaderDirection();
}
