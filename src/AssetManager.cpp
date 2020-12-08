#include "AssetManager.h"
#include "./Components/TransformComponent.h"

AssetManager::AssetManager(EntityManager* manager): manager(manager) {

}

void AssetManager::ClearData(){
    textures.clear();
    fonts.clear();
}

void AssetManager::AddTexture(string textureID, const char* filePath){
    
    textures.emplace(textureID, TextureManager::LoadTexture(filePath));

}

void AssetManager::AddFont(string fontID, const char* filePath, int fontsize){

    fonts.emplace(fontID, FontManager::LoadFont(filePath, fontsize));

}

SDL_Texture* AssetManager::GetTexture(string textureID){
    return textures[textureID];
}

TTF_Font* AssetManager::GetFont(string fontID){

    return fonts[fontID];
}