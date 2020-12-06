#ifndef ASSETMANAGER_
#define ASSETMANAGER_
#include <map>
#include <string>
#include "EntityManager.h"
#include "TextureManager.h"
class AssetManager
{
private:
    EntityManager* manager;
    map<string, SDL_Texture*> textures;
public:
    AssetManager(EntityManager* manager);
    ~AssetManager(){};
    void ClearData();
    void AddTexture(string textureID, const char* filePath);
    SDL_Texture* GetTexture(string textureID);

};

#endif