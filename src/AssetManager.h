#ifndef ASSETMANAGER_H
#define ASSETMANAGER_H
#include <map>
#include <string>
#include <SDL2/SDL_ttf.h>
#include "EntityManager.h"
#include "TextureManager.h"
#include "FontManager.h"
class AssetManager
{
private:
    EntityManager* manager;
    map<string, SDL_Texture*> textures;
    map<string, TTF_Font*> fonts;
public:
    AssetManager(EntityManager* manager);
    ~AssetManager(){};
    void ClearData();
    void AddTexture(string textureID, const char* filePath);
    SDL_Texture* GetTexture(string textureID);
    void AddFont(string fontID, const char* filePath, int fontsize);
    TTF_Font* GetFont(string fontID);

};

#endif