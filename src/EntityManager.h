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
    bool HasNoEntities();
    Entity& AddEntity(string entityName);
    vector<Entity*> GetEntities() const;
    void ListAllEntities() const;
    unsigned int GetEntityCount();
    virtual ~EntityManager(){};
};

#endif