#ifndef TILECOMPONENT_H
#define TILECOMPONENT_H

#include <SDL2/SDL.h>
#include "../EntityManager.h"
#include "../AssetManager.h"
#include "../../lib/glm/glm.hpp"

class TileComponent:public Component
{
private:
    /* data */
public:
    SDL_Texture *texture;
    SDL_Rect sourceRect;
    SDL_Rect targetRect;
    glm::vec2 position;

    TileComponent(int sourceRectX, int sourceRectY, int x, int y, int tileSize, int tileScale, string assetTextureID){
        // get the texture
        texture = Game::assetManager->GetTexture(assetTextureID);

        sourceRect.x = sourceRectX;
        sourceRect.y = sourceRectY;
        sourceRect.w = tileSize;
        sourceRect.h = tileSize;

        targetRect.x = x;
        targetRect.y = y;
        targetRect.w = tileSize * tileScale;
        targetRect.h = tileSize * tileScale;

        position.x = x;
        position.y = y;
    }
    virtual ~TileComponent(){
        SDL_DestroyTexture(texture);
    }

    void Update(float deltaTime) override{
        // update with camera moves
        targetRect.x = position.x - Game::camera.x;
        targetRect.y = position.y - Game::camera.y;
    }

    void Render() override{
        TextureManager::Draw(texture, sourceRect, targetRect, SDL_FLIP_NONE);
    }
};


#endif