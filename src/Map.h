#ifndef MAP_H
#define MAP_H

#include <string>

using namespace std;

class Map
{
private:
    /* data */
    string textureID;
    int scale;
    int tileSize;

public:

    Map(string textureID, int scale, int tileSize);
    virtual ~Map(){};

    void LoadMap(string filePath, int mapSizeX, int mapSizeY);
    void AddTile(int sourceX, int sourceY, int x, int y);
};


#endif