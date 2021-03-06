#ifndef ENTITY_H
#define ENTITY_H

#include <vector>
#include <string>
#include <map>
#include "EntityManager.h"
#include "Component.h"
#include "Constants.h"
#include <typeinfo>

class EntityManager;
class Component;

using namespace std;

class Entity
{
private:
    EntityManager & manager;
    bool activeFlag;
    vector<Component*> components;
    map<const type_info*, Component*> componentTypeMap;

public:
    string name;
    LayerType layer;
    Entity(EntityManager& manager);
    Entity(EntityManager& manager, string name, LayerType layer);
    virtual ~Entity(){};
    
    void Update(float deltaTime);
    void Render();
    void Destroy();
    bool isActive() const;
    void ListAllComponents() const;


    template <typename T, typename... TArgs>
    T& AddComponent(TArgs&&... args){
        T* newComponent(new T(forward<TArgs>(args)...));
        // component owner is current entity
        newComponent->owner = this;
        // add components
        components.emplace_back(newComponent);
        // add to component-type map (deref newComponent)
        componentTypeMap[&typeid(*newComponent)] = newComponent;
        newComponent->Init();
        return *newComponent;
    }

    template <typename T>
    bool HasComponent() const{
        return componentTypeMap.count(&typeid(T));
    }

    template <typename T>
    T* GetComponent(){
        return static_cast<T*>(componentTypeMap[&typeid(T)]);
    }

};


#endif