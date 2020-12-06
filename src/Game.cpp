#include <iostream>
#include "Constants.h"
#include "Game.h"
#include "AssetManager.h"
#include "./Components/TransformComponent.h"
#include "./Components/SpriteComponent.h"
#include "../lib/glm/glm.hpp"

EntityManager manager;
AssetManager* Game::assetManager = new AssetManager(&manager);
SDL_Renderer* Game::m_renderer;


Game::Game() {
    this->runningFlag = false;
}

Game::~Game(){

}

bool Game::isRunning() const {
    return this->runningFlag;
}

void Game::Init(int width, int height){
    if(SDL_Init(SDL_INIT_EVERYTHING)!=0){
        cerr << "Error initializing SDL" << endl;
    }

    // init window pointer
    m_window = SDL_CreateWindow(
        NULL,
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        width,
        height,
        SDL_WINDOW_BORDERLESS);
    if(!m_window){
        cerr << "Error creating SDL window" << endl;
        return;
    }
    // init renderer
    m_renderer = SDL_CreateRenderer(m_window, -1,0);
    if(!m_renderer){
        cerr << "Error creating SDL renderer" << endl;
        return;
    }
    // TODO:
    LoadLevel(0);
    // setting init status
    runningFlag = true;
    if(runningFlag){
        cout << "Game obejct is initialized successfully" << endl;
    }
    return;
}

void Game::LoadLevel(int level){

    // start including new assets to the asset manager list
    string textureFilePath = "./assets/images/tank-big-right.png";
    assetManager->AddTexture("tank-image", textureFilePath.c_str());

    // start including entities and add components to them
    Entity& newEntity(manager.AddEntity("tank"));
    newEntity.addComponent<TransformComponent>(0, 0, 20, 20, 32, 32, 1);
    newEntity.addComponent<SpriteComponent>("tank-image");

}

void Game::ProcessInput(){
    SDL_Event m_event;
    SDL_PollEvent(&m_event);
    
    switch (m_event.type)
    {
        case SDL_QUIT:{
            runningFlag = false;
            break;
        }
        case SDL_KEYDOWN:{
            if(m_event.key.keysym.sym == SDLK_ESCAPE){
                runningFlag = false;
            }
        }
        
        default:
            break;
    }
}

void Game::Update(){
    // wait until interval of 2 frames = target time (frame refresh faster)
    int timeToWait = FRAME_TARGET_TIME - (SDL_GetTicks() - lastFrameTime);
    // use delay function, avoid using while loop
    if(timeToWait > 0 && timeToWait <= FRAME_TARGET_TIME){
        SDL_Delay(timeToWait);
    }
    // get the time difference between 2 frames (milli-seconds)
    float deltaTime = (SDL_GetTicks() - lastFrameTime) / 1000.0f;
    // clamp the deltaTime (e.g. for debug purpose)
    deltaTime = deltaTime > 0.05f ? 0.05f : deltaTime;
    // set the current lastFrameTime for next frame usage 
    lastFrameTime = SDL_GetTicks();
    // call entity manager update
    manager.Update(deltaTime);
}

void Game::Render(){

    // set the background color (RGBA)
    SDL_SetRenderDrawColor(m_renderer, 21, 21, 21, 255);
    // clear the back buffer (double buffer)
    SDL_RenderClear(m_renderer);

    if(manager.HasNoEntities()){
        return;
    }
    manager.Render();

    // swap front and back buffers
    SDL_RenderPresent(m_renderer);
}

void Game::Destroy(){
    // SDL destroy
    SDL_DestroyRenderer(m_renderer);
    SDL_DestroyWindow(m_window);
    SDL_Quit();
}
