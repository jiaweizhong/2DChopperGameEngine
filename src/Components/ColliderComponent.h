#ifndef COLLIDERCOMPONENT_H
#define COLLIDERCOMPONENT_H

#include "TransformComponent.h"
#include "../Game.h"
#include "../EntityManager.h"
using namespace std;

class ColliderComponent:public Component
{
private:
    /* data */
public:
    string colliderTag;
    SDL_Rect collider;
    SDL_Rect sourceRect;
    SDL_Rect targetRect;
    TransformComponent* transform;

    ColliderComponent(string tag, int x, int y, int w, int h){
        this->colliderTag = tag;
        // initialize the collider rect
        this->collider = {x, y, w, h};
    };
    ~ColliderComponent(){};

    void Init() override{
        if(owner->HasComponent<TransformComponent>()){
            transform = owner->GetComponent<TransformComponent>();
            sourceRect = {0, 0, transform->width, transform->height};
            targetRect = {collider.x, collider.y, collider.w, collider.h};
        }
    }

    void Update(float deltaTime) override {
        collider.x = static_cast<int>(transform->position.x);
        collider.y = static_cast<int>(transform->position.y);
        collider.w = transform->width * transform->scale;
        collider.h = transform->height * transform->scale;

        targetRect.x = collider.x - Game::camera.x;
        targetRect.y = collider.y - Game::camera.y;
    }
};


#endif