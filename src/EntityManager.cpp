
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

Entity& EntityManager::AddEntity(string entityName, LayerType layer){
    // pass this to owner pointer
    Entity *entity = new Entity(*this, entityName, layer);
    entities.emplace_back(entity);
    // return pointer to the new created entity
    return *entity;
}