#include <iostream>
#include "Constants.h"
#include "Game.h"
using namespace std;

int main(int argc, char *args[]){
    
    Game *game = new Game();
    // game initialization
    game->Init(WINDOW_WIDTH, WINDOW_HEIGHT);


    while(game->isRunning()){
        // game loop
        game->ProcessInput();
        game->Update();
        game->Render();
    }

    // destructor
    game->Destroy();

    return 0;
}