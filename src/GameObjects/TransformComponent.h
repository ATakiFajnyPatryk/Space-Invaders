#pragma once
#include "Component.h"
#include <SFML/Graphics.hpp>

using namespace sf;

class TransformComponent : public Component {
private:
  const string m_Type = "transform";
  Vector2f  m_Location;
  float m_Height;
  float m_Width;

public:
  TransformComponent(float width, float height, Vector2f location);
  Vector2f& getLocation();
  Vector2f getSize();

  string getType() override {
    return m_Type;
  }

  string getSpecificType() override {
    return m_Type;
  }

  void disableComponent() override {}

  void enableComponent() override {}

  bool enabled() override {
    return false;
  }

  void start(GameObjectSharer* gos, GameObject* self) override {}
};
