#ifndef ENTITYMANAGER_H
#define ENTITYMANAGER_H

#include "Entity.h"
#include "Component.h"
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
    void ListAllEntities() const;
    Entity& AddEntity(string entityName);
    virtual ~EntityManager(){};
};

#endif