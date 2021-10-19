#include "GameObjectFactoryPlayMode.h"
#include <iostream>
#include <memory>
#include "../GameObjects/TransformComponent.h"
#include "../GameObjects/StandardGraphicsComponent.h"
#include "../GameObjects/PlayerUpdateComponent.h"
#include "../GameObjects/RectColliderComponent.h"
#include "../GameObjects/InvaderUpdateComponent.h"
#include "../GameObjects/BulletUpdateComponent.h"

void GameObjectFactoryPlayMode::buildGameObject(GameObjectBlueprint &bp,
                                                vector<GameObject> &gameObjects) {
  GameObject gameObject;
  gameObject.setTag(bp.getName());
  auto it = bp.getComponentList().begin();
  for (it; it != bp.getComponentList().end(); ++it) {
    if (*it == "Transform") {
      gameObject.addComponent(make_shared<TransformComponent>(
                                          bp.getWidth(),
                                          bp.getHeight(),
                                          Vector2f(bp.getLocationX(),
                                                   bp.getLocationY())));
    }
    else if (*it == "Player Update") {
      gameObject.addComponent(make_shared<PlayerUpdateComponent>());
    }
    else if (*it == "Invader Update") {
      gameObject.addComponent(make_shared<InvaderUpdateComponent>());
    }
    else if (*it == "Bullet Update") {
      gameObject.addComponent(make_shared<BulletUpdateComponent>());
    }
    else if (*it == "Standard Graphics") {
      shared_ptr<StandardGraphicsComponent> sgp =
              make_shared<StandardGraphicsComponent>();
      gameObject.addComponent(sgp);
      sgp->initializeGraphics(bp.getBitmapName(),
                              Vector2f(bp.getHeight(), bp.getHeight()));
    }

    if (bp.getEncompassingRectCollider()) {
      shared_ptr<RectColliderComponent> rcc =
              make_shared<RectColliderComponent>(bp.getEncompassingRectColliderLabel());
      gameObject.addComponent(rcc);
      rcc->setOrMoveCollider(bp.getLocationY(), bp.getLocationY(),
                             bp.getWidth(), bp.getHeight());
    }

    gameObjects.push_back(gameObject);
  }
}
