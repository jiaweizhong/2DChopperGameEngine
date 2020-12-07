#ifndef TRANSFORMCOMPONENT_H
#define TRANSFORMCOMPONENT_H

#include "../EntityManager.h"
#include "../../lib/glm/glm.hpp"
#include <SDL2/SDL.h>
#include "../Game.h"


// class to describe the sprite transform
class TransformComponent:public Component
{
private:
    /* data */
public:
    glm::vec2 position;
    glm::vec2 velocity;
    int width;
    int height;
    int scale;

    TransformComponent(int posX, int posY, int velX, int velY, int w, int h, int s){
        position = glm::vec2(posX, posY);
        velocity = glm::vec2(velX, velY);
        width = w;
        height = h;
        scale = s;
    }
    // override add checking for virtual function missing implementation
    void Init() override{

    }
    void Update(float deltaTime) override{
        position.x += velocity.x * deltaTime;
        position.y += velocity.y * deltaTime;
    }
    void Render() override{
        /* test object
        SDL_Rect transformRectangle = {
            (int)position.x,
            (int)position.y,
            width,
            height
        };
        // background white
        SDL_SetRenderDrawColor(Game::m_renderer,255,255,255,255);
        SDL_RenderFillRect(Game::m_renderer, &transformRectangle);
        */
    }
};

#endif