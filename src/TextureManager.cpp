#include "TextureManager.h"

SDL_Texture* TextureManager::LoadTexture(const char* fileName) {
    // load texture image as collection of pixel
    SDL_Surface* surface = IMG_Load(fileName);
    // create texture from the img
    SDL_Texture* texture = SDL_CreateTextureFromSurface(Game::m_renderer, surface);
    // free the img
    SDL_FreeSurface(surface);
    return texture;
}

void TextureManager::Draw(SDL_Texture* texture, SDL_Rect sourceRectangle, SDL_Rect destinationRectangle, SDL_RendererFlip flip) {
    SDL_RenderCopyEx(Game::m_renderer, texture, &sourceRectangle, &destinationRectangle, 0.0, NULL, flip);
}
