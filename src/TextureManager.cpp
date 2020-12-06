#include "TextureManager.h"

SDL_Texture* TextureManager::LoadTexture(const char* fileName){
    // load texture img as a collection of pixels
    SDL_Surface* surface = IMG_Load(fileName);
    // create texture from img
    SDL_Texture* texture = SDL_CreateTextureFromSurface(Game::m_renderer, surface);
    // free the img
    SDL_FreeSurface(surface);
    return texture;
}

void TextureManager::Draw(SDL_Texture* texture, SDL_Rect sourceRect, SDL_Rect targetRect, SDL_RendererFlip flip){
    // copy a portion of texture to current rendering target
    SDL_RenderCopyEx(Game::m_renderer, texture, &sourceRect, &targetRect, 0.0, NULL, flip);
}
