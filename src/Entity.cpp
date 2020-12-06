
#include <iostream>
#include "Entity.h"

using namespace std;
// constructor -- initialization list
Entity::Entity(EntityManager& manager):manager(manager){

    this->activeFlag = true;

}

Entity::Entity(EntityManager& manager, string name):manager(manager), name(name){

    this->activeFlag = true;

}

void Entity::Update(float deltaTime){

    // iterator -- use auto for unknow component type
    for(auto& component: components){
        component -> Update(deltaTime);
    }

}

void Entity::Render(){
    // iterator -- use auto for unknow component type
    for(auto& component: components){
        component -> Render();
    }

}

void Entity::Destroy(){
    this->activeFlag = false;
}

bool Entity::isActive() const {

    return this->activeFlag;
}

void Entity::ListAllComponents() const {
    for (auto mapElement: componentTypeMap) {
        cout << "    Component<" << mapElement.first->name() << ">" << endl;
    }
}