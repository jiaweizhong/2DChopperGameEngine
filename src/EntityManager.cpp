
#include <iostream>
#include "EntityManager.h"

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
    for(auto& entity:entities){
        entity->Render();
    }
}

bool EntityManager::HasNoEntities() const{
    return entities.size() == 0;
}

vector<Entity*> EntityManager::GetEntities()const{
    return entities;
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

Entity& EntityManager::AddEntity(string entityName){
    // pass this to owner pointer
    Entity *entity = new Entity(*this, entityName);
    entities.emplace_back(entity);
    // return pointer to the new created entity
    return *entity;
}