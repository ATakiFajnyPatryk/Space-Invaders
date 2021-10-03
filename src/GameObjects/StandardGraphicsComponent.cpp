#include "StandardGraphicsComponent.h"
#include "../Engine/BitmapStore.h"
#include <iostream>

void StandardGraphicsComponent::draw(RenderWindow &window,
                                     shared_ptr<TransformComponent> t) {
  m_Sprite.setPosition(t->getLocation());
  window.draw(m_Sprite);
}

void StandardGraphicsComponent::initializeGraphics(string bitmapName,
                                                   Vector2f objectSize) {
  BitmapStore::addBitmap("resources/graphics/" + bitmapName + ".png");
  m_Sprite.setTexture(BitmapStore::getBitmap("resources/graphics/" + bitmapName
                                             + ".png"));
  auto textureSize = m_Sprite.getTexture()->getSize();
  m_Sprite.setScale(float(objectSize.x) / textureSize.x,
                    float(objectSize.y) / textureSize.y);
  m_Sprite.setColor(Color(0, 255, 0));
}
