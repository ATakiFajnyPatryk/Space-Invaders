#pragma once
#include "UpdateComponent.h"
#include "TransformComponent.h"
#include "GameObjectSharer.h"
#include "RectColliderComponent.h"
#include "GameObject.h"
#include <memory>

class PlayerUpdateComponent : public UpdateComponent {
private:
  string m_SpecificType = "player";
  shared_ptr<TransformComponent> m_TC;
  shared_ptr<RectColliderComponent> m_RCC;
  float m_Speed = 50.0f;
  float m_XExtent = 0;
  float m_YExtent = 0;
  bool m_IsHoldingLeft = false;
  bool m_IsHoldingRight = false;
  bool m_IsHoldingUp = false;
  bool m_IsHoldingDown = false;

public:
  void updateShipTravelWithController(float x, float y);
  void moveLeft();
  void moveRight();
  void moveUp();
  void moveDown();
  void stopLeft();
  void stopRight();
  void stopUp();
  void stopDown();

  string getSpecificType() override {
    return m_SpecificType;
  }

  void start(GameObjectSharer* gos, GameObject* self) override {
    m_TC = static_pointer_cast<TransformComponent>(
            self->getComponentByTypeAndSpecificType("transform", "transform"));
    m_RCC = static_pointer_cast<RectColliderComponent>(
            self->getComponentByTypeAndSpecificType("collider", "rect"));
  }

  void update(float fps) override;
};
