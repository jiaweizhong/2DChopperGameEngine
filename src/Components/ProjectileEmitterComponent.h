#ifndef PROJECTILEEMITTERCOMPONENT_H
#define PROJECTILEEMITTERCOMPONENT_H

#include "../Component.h"
#include "../EntityManager.h"
#include "../../lib/glm/glm.hpp"
#include "../Components/TransformComponent.h"

class ProjectileEmitterComponent:public Component
{
private:
    TransformComponent* transform;
    glm::vec2 origin;
    int speed;
    int range;
    float angleRad;
    bool shootLoop;

public:
    ProjectileEmitterComponent(int speed, int angle, int range, bool shootLoop){
        this->speed = speed;
        this->range = range;
        this->shootLoop = shootLoop;
        this->angleRad = glm::radians(static_cast<float>(angle)); // store as radians
        this->shootLoop = shootLoop;
    }
    virtual ~ProjectileEmitterComponent(){};

    void Init() override {
        transform = owner->GetComponent<TransformComponent>();
        origin = glm::vec2(transform->position.x, transform->position.y);
        // calculation the transform based on speed
        transform->velocity = glm::vec2(glm::cos(angleRad)*speed, glm::sin(angleRad)*speed);
    }

    void Update(float deltaTime) override {
        // check out of range 
        if(glm::distance(transform->position, origin) > range){
            // set to origin position if it's a loop
            if(shootLoop){
                transform->position.x = origin.x;
                transform->position.y = origin.y;
            }else{
                // destroy the projectile
                owner->Destroy();
            }
        }
    }
};


#endif