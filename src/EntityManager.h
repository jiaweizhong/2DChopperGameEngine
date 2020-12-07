#ifndef ENTITYMANAGER_H
#define ENTITYMANAGER_H

#include "Entity.h"
#include "Component.h"
#include "Constants.h"
#include <vector>
using namespace std;

class EntityManager{
private:
    vector<Entity*> entities;
    
public:
    void ClearData(); // clear all entities
    void Update(float deltaTime);
    void Render();
    bool HasNoEntities() const;
    unsigned int GetEntityCount() const;
    vector<Entity*> GetEntities() const;
    vector<Entity*> GetEntitiesByLayer(LayerType layer) const;
    void ListAllEntities() const;
    Entity& AddEntity(string entityName, LayerType layer);
    CollisionType CheckEntityCollision() const;
    virtual ~EntityManager(){};
};

#endif