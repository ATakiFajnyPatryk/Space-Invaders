#pragma once
#include "Component.h"
#include "GraphicsComponent.h"
#include <string>

class Component;

using namespace sf;

class StandardGraphicsComponent : public GraphicsComponent {
private:
  Sprite m_Sprite;
  const string m_SpecificType = "standard";

public:
  string getSpecificType() override {
    return m_SpecificType;
  }

  void start(GameObjectSharer* gos, GameObject* self) override {}

  void draw(RenderWindow& window, shared_ptr<TransformComponent> t) override;
  void initializeGraphics(string bitmapName, Vector2f objectSize) override;
};
