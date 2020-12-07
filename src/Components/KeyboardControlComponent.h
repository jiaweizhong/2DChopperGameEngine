#ifndef KEYBOARDCONTROLCOMPONENT_H
#define KEYBOARDCONTROLCOMPONENT_H

#include "../Game.h"
#include "../EntityManager.h"
#include "TransformComponent.h"
#include "SpriteComponent.h"
#include <string>

using namespace std;

class KeyboardControlComponent : public Component
{
private:
    /* data */
public:
    string upKey;
    string downKey;
    string leftKey;
    string rightKey;
    string shootKey;
    TransformComponent* tranform;
    SpriteComponent* sprite;
    KeyboardControlComponent(){};
    KeyboardControlComponent(string u, string r, string d, string l, string s){
        // convert to SDL key code
        this->upKey = GetSDLKeyCode(u);
        this->rightKey = GetSDLKeyCode(r);
        this->downKey = GetSDLKeyCode(d);
        this->leftKey = GetSDLKeyCode(l);
        this->shootKey = GetSDLKeyCode(s);
    };
    ~KeyboardControlComponent(){};

    string GetSDLKeyCode(string in){
        // convert key string to SDL key code
        if(in.compare("up") == 0) return "1073741906";
        if(in.compare("down") == 0) return "1073741905";
        if(in.compare("left") == 0) return "1073741904";
        if(in.compare("right") == 0) return "1073741903";
        if(in.compare("space") == 0) return "32";
        // other keys : alphabets, digits etc.
        return to_string(static_cast<int>(in[0]));
    }

    void Init()override{
        tranform = owner->GetComponent<TransformComponent>();
        sprite = owner->GetComponent<SpriteComponent>();
    }

    void Update(float deltaTime)override{
        // key press
        if(Game::m_event.type == SDL_KEYDOWN){
            string keyCode = to_string(Game::m_event.key.keysym.sym);
            if(keyCode.compare(upKey) == 0){
                tranform->velocity.x = 0;
                tranform->velocity.y = -10;
                sprite->Play("UpAnimation");
            }
            if(keyCode.compare(rightKey) == 0){
                tranform->velocity.x = 10;
                tranform->velocity.y = 0;
                sprite->Play("RightAnimation");
            }
            if(keyCode.compare(downKey) == 0){
                tranform->velocity.x = 0;
                tranform->velocity.y = 10;
                sprite->Play("DownAnimation");
            }
            if(keyCode.compare(leftKey) == 0){
                tranform->velocity.x = -10;
                tranform->velocity.y = 0;
                sprite->Play("LeftAnimation");
            }
            if(keyCode.compare(shootKey) == 0){
                // TODO:
            }
        }
        // key release
        if(Game::m_event.type == SDL_KEYUP){
            string keyCode = to_string(Game::m_event.key.keysym.sym);
            if(keyCode.compare(upKey) == 0){
                tranform->velocity.y = 0;
            }
            if(keyCode.compare(rightKey) == 0){
                tranform->velocity.x = 0;
            }
            if(keyCode.compare(downKey) == 0){
                tranform->velocity.y = 0;
            }
            if(keyCode.compare(leftKey) == 0){
                tranform->velocity.x = 0;
            }
        }
    }
};



#endif