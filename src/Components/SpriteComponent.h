#ifndef SPRITECOMPONENT_
#define SPRITECOMPONENT_

#include "../Component.h"
#include <SDL2/SDL.h>
#include <string>
#include "TransformComponent.h"
#include "../Game.h"

using namespace std;

class SpriteComponent: public Component
{
private:
    TransformComponent* transform;
    SDL_Texture* texture;
    SDL_Rect sourceRect;
    SDL_Rect targetRect;
public:
    SDL_RendererFlip flip = SDL_FLIP_NONE;
    SpriteComponent(const char* filePath){
        SetTexture(filePath);
    }
    void SetTexture(string assetTextureID){
        texture = Game::assetManager->GetTexture(assetTextureID);
    };
    void Init() override{
        transform = owner->GetComponent<TransformComponent>();
        sourceRect.x = 0;
        sourceRect.y = 0;
        sourceRect.w = transform->width;
        sourceRect.h = transform->height;
    };
    void Update(float deltaTime) override{
        targetRect.x = (int)transform->position.x;
        targetRect.y = (int)transform->position.y;
        targetRect.w = transform->width * transform->scale;
        targetRect.h = transform->height * transform->scale;

    };
    void Render() override{
        TextureManager::Draw(texture, sourceRect, targetRect,flip);
    };

    //virtual ~SpriteComponent(){};
};

#endif