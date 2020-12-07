#ifndef GAME_H
#define GAME_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include "Entity.h"
#include "Component.h"
#include "EntityManager.h"

class AssetManager;

class Game {

    private:
        bool runningFlag;
        SDL_Window *m_window;

    public:
        int lastFrameTime = 0;
        // static renderer
        static SDL_Renderer *m_renderer;
        static AssetManager* assetManager;
        static SDL_Event m_event;
        static SDL_Rect camera;  // camera of viewer
        Game();
        ~Game();
        void LoadLevel(int levelNumber);
        // check running status
        bool isRunning() const;
        // init function
        void Init(int width, int height);
        // process input
        void ProcessInput();
        // update game status
        void Update();
        // render the window
        void Render();
        void Destroy();
        void HandleCameraMove();
        void CheckCollision();
        void ProcessGameOver();
        void ProcessNextLevel(int level);


};

#endif