#ifndef SPRITECOMPONENT_H
#define SPRITECOMPONENT_H

#include <SDL2/SDL.h>
#include "../TextureManager.h"
#include "../AssetManager.h"
#include "../Animation.h"

using namespace std;

class SpriteComponent: public Component
{
private:
    TransformComponent* transform;
    SDL_Texture* texture;
    SDL_Rect sourceRect;
    SDL_Rect targetRect;
    // animation related fileds
    bool isAnimated;
    int numFrames; 
    int animationSpeed;
    bool isFixed; // fixed location
    map<string, Animation> animations;
    string currentAnimation;
    unsigned int animationIndex = 0;

public:
    SDL_RendererFlip flip = SDL_FLIP_NONE;
    SpriteComponent(string assetTextureID){
        isAnimated = false;
        isFixed = false;
        SetTexture(assetTextureID);
    }
    SpriteComponent(string assetTextureID, int numFrames, int animationSpeed, bool hasDirections, bool isFixed){
        this->numFrames = numFrames;
        this->animationSpeed = animationSpeed;
        this->isAnimated = isAnimated;
        this->isFixed = isFixed;
        if(hasDirections){
            // create 4 direction animations
            Animation down = Animation(0, numFrames, animationSpeed);
            Animation right = Animation(1, numFrames, animationSpeed);
            Animation left = Animation(2, numFrames, animationSpeed);
            Animation up = Animation(3, numFrames, animationSpeed);

            animations.emplace("DownAnimation", down);
            animations.emplace("RightAnimation", right);
            animations.emplace("LeftAnimation", left);
            animations.emplace("UpAnimation", up);
            // initial animation state
            this->animationIndex = 0;
            this->currentAnimation = "DownAnimation";
        }
        else{
            // create single animation
            Animation singleAnimation = Animation(0,numFrames,animationSpeed);
            animations.emplace("SingleAnimation", singleAnimation);
            this->animationIndex = 0;
            this->currentAnimation = "SingleAnimation";
        }

        // set all the animation params
        Play(this->currentAnimation);

        SetTexture(assetTextureID);
    }

    void Play(string animationName){
        numFrames = animations[animationName].numFrames;
        animationIndex = animations[animationName].index;
        animationSpeed = animations[animationName].animationSpeed;
        currentAnimation = animationName;
    }


    void SetTexture(string assetTextureID){
        texture = Game::assetManager->GetTexture(assetTextureID);
    }

    void Init() override{
        transform = owner->GetComponent<TransformComponent>();
        sourceRect.x = 0;
        sourceRect.y = 0;
        sourceRect.w = transform->width;
        sourceRect.h = transform->height;
    }
    void Update(float deltaTime) override{
        // update animation to change the frame
        if(isAnimated){
            sourceRect.x = sourceRect.w * static_cast<int>((SDL_GetTicks()/animationSpeed) %numFrames);
        }
        sourceRect.y = animationIndex * transform -> height;

        targetRect.x = static_cast<int>(transform->position.x);
        targetRect.y = static_cast<int>(transform->position.y);
        targetRect.w = transform->width * transform->scale;
        targetRect.h = transform->height * transform->scale;

    };
    void Render() override{
        TextureManager::Draw(texture, sourceRect, targetRect,flip);
    };

    virtual ~SpriteComponent(){};
};

#endif