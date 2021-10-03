#pragma once
#include "Component.h"

class UpdateComponent : public Component {
private:
  const string m_Type = "update";
  bool m_Enabled = false;

public:
  virtual void update(float fps) = 0;

  string getType() override {
    return m_Type;
  }

  void disableComponent() override {
    m_Enabled = false;
  }

  void enableComponent() override {
    m_Enabled = true;
  }

  bool enabled() override {
    return m_Enabled;
  }

  void start(GameObjectSharer* gos, GameObject* self) override {}
};
