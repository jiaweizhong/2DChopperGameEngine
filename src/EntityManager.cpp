
#include <iostream>
#include "EntityManager.h"
#include "Collision.h"
#include "./Components/ColliderComponent.h"

void EntityManager::ClearData(){
    for(auto& entity:entities){
        entity->Destroy();
    }
}

void EntityManager::Update(float deltaTime){
    for(auto& entity:entities){
        entity->Update(deltaTime);
    }
}

void EntityManager::Render(){
    for (int layerNumber = 0; layerNumber < NUM_LAYERS; layerNumber++){
        // render entity by layer
        for(auto& entity:GetEntitiesByLayer(static_cast<LayerType>(layerNumber))){
            entity->Render();
        }
    }
}

bool EntityManager::HasNoEntities() const{
    return entities.size() == 0;
}

vector<Entity*> EntityManager::GetEntities()const{
    return entities;
}

vector<Entity*> EntityManager::GetEntitiesByLayer(LayerType layer)const{
    vector<Entity*> selectedEntities;
    for(auto& entity:entities){
        if(entity->layer == layer){
            selectedEntities.emplace_back(entity);
        }
    }
    return selectedEntities;
}

unsigned int EntityManager::GetEntityCount() const{

    return entities.size();
}

void EntityManager::ListAllEntities() const {
    unsigned int i = 0;
    for (auto& entity: entities) {
        std::cout << "Entity[" << i << "]: " << entity->name << std::endl;
        entity->ListAllComponents();
        i++;
    }
}

CollisionType EntityManager::CheckEntityCollision() const {
    // loop through all entities in the list
    for(auto& thisEntity:entities){
        if(thisEntity->HasComponent<ColliderComponent>()){
            // get the collider for current entity
            ColliderComponent* thisCollider = thisEntity->GetComponent<ColliderComponent>();
            // loop through remaining entities for collision
            for(auto& thatEntity:entities){
                // collision check skip the current entity & the other entity has collider
                if(thisEntity->name.compare(thatEntity->name)!=0 && thatEntity->HasComponent<ColliderComponent>()){
                    // get the other collider
                    ColliderComponent* thatCollider = thatEntity->GetComponent<ColliderComponent>();
                    if(Collision::CheckRectCollision(thisCollider->collider, thatCollider->collider)){
                        // list all collider combinations
                        // 1. player - enenmy
                        if(thisCollider->colliderTag.compare("PLAYER") == 0 &&
                           thatCollider->colliderTag.compare("ENEMY") == 0){
                               return PLAYER_ENEMY_COLLISION;
                        }
                        // 2. player - projecttile
                        if(thisCollider->colliderTag.compare("PLAYER") == 0 &&
                           thatCollider->colliderTag.compare("PROJECTTILE") == 0){
                               return PLAYER_PROJECTTILE_COLLISION;
                        }
                        // 3. enemy - friend projecttile
                        if(thisCollider->colliderTag.compare("ENEMY") == 0 &&
                           thatCollider->colliderTag.compare("FRIENDLY_PROJECTTILE") == 0){
                               return ENEMY_PROJECTTILE_COLLISION;
                        }
                        // 4. player - level complete
                        if(thisCollider->colliderTag.compare("PLAYER") == 0 &&
                           thatCollider->colliderTag.compare("LEVEL_COMPLETE") == 0){
                               return PLAYER_LEVEL_COMPLETE_COLLISION;
                        }
                    }
                }
            }
        }
    }
    // return no collision enum
    return NO_COLLISION;
}

Entity& EntityManager::AddEntity(string entityName, LayerType layer){
    // pass this to owner pointer
    Entity *entity = new Entity(*this, entityName, layer);
    entities.emplace_back(entity);
    // return pointer to the new created entity
    return *entity;
}