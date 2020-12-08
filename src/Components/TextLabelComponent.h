#ifndef TEXTLABELCOMPONENT_H
#define TEXTLABELCOMPONENT_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include "../FontManager.h"
#include "../EntityManager.h"
#include "../AssetManager.h"
#include "../Game.h"
using namespace std;

class TextLabelComponent: public Component
{
private:
    SDL_Rect position;
    string text;
    string fontFamily;
    SDL_Color color;
    SDL_Texture* texture;

public:
    TextLabelComponent(int x, int y, string text, string fontFamily, const SDL_Color color){
        this->position.x = x;
        this->position.y = y;
        this->text = text;
        this->fontFamily = fontFamily;
        this->color = color;
        
        SetLabelText(text, fontFamily);
    };
    virtual ~TextLabelComponent(){};

    void SetLabelText(string text, string fontFamily){
        SDL_Surface* surface = TTF_RenderText_Blended(Game::assetManager->GetFont(fontFamily),text.c_str(),color);
        texture = SDL_CreateTextureFromSurface(Game::m_renderer, surface);
        SDL_FreeSurface(surface);
        SDL_QueryTexture(texture, NULL, NULL, &position.w, &position.h);
    };

    void Render() override {
        FontManager::Draw(texture, position);
    }
};


#endif