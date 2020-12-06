#include "AssetManager.h"

void AssetManager::ClearData(){
    textures.clear();
}

void AssetManager::AddTexture(string textureID, const char* filePath){
    
    textures.emplace(textureID, TextureManager::LoadTexture(filePath));

}

SDL_Texture* AssetManager::GetTexture(string textureID){
    return textures[textureID];
}