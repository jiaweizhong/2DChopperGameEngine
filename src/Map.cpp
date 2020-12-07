#include <fstream>
#include <iostream>
#include "Map.h"
#include "Game.h"
#include "EntityManager.h"
#include "./Components/TileComponent.h"
using namespace std;

extern EntityManager manager;

Map::Map(string textureID, int scale, int tileSize){
    this->textureID = textureID;
    this->scale = scale;
    this->tileSize = tileSize;
}


void Map::LoadMap(string filePath, int mapSizeX, int mapSizeY){
    // load the tile map (e.g. 21 - represent row 2 col 1 tile in tile png)
    fstream mapFile;
    mapFile.open(filePath);

    // sanity check
    if(mapFile.fail()){
        cerr << "Map file loading failed" << endl;
    }

    for(int y = 0; y < mapSizeY; y++){
        for(int x = 0; x < mapSizeX; x++){
            char ch;
            // get row digit
            mapFile.get(ch);
            int sourceRectY = atoi(&ch) * tileSize;
            // get col digit
            mapFile.get(ch);
            int sourceRectX = atoi(&ch) * tileSize;
            AddTile(sourceRectX, sourceRectY, x * (scale * tileSize), y * (scale * tileSize));
            // ignore comma
            mapFile.ignore();
        }
    }
    mapFile.close();
}


void Map::AddTile(int sourceRectX, int sourceRectY, int x, int y){
    Entity& newTile(manager.AddEntity("Tile", TILEMAP_LAYER));
    newTile.AddComponent<TileComponent>(sourceRectX, sourceRectY, x, y, tileSize, scale, textureID);
}

