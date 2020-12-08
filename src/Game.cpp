#include <iostream>
#include "Constants.h"
#include "Game.h"
#include "AssetManager.h"
#include "Map.h"
#include "./Components/TransformComponent.h"
#include "./Components/SpriteComponent.h"
#include "./Components/KeyboardControlComponent.h"
#include "./Components/ColliderComponent.h"
#include "./Components/TextLabelComponent.h"
#include "./Components/ProjectileEmitterComponent.h"
#include "../lib/glm/glm.hpp"

EntityManager manager;
AssetManager* Game::assetManager = new AssetManager(&manager);
SDL_Renderer* Game::m_renderer;
SDL_Event Game::m_event;
// camera = window size
SDL_Rect Game::camera = {0,0, WINDOW_WIDTH, WINDOW_HEIGHT};
Map* m_map;
// initialize the chopper player 
Entity* chopperPlayer = NULL;

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
        return;
    }
    // initialized ttf
    if(TTF_Init()!=0){
        cerr << "Error initializing SDL TTF" << endl;
        return;
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
    LoadLevel(1);
    // setting init status
    runningFlag = true;
    if(runningFlag){
        cout << "Game obejct is initialized successfully" << endl;
    }
    return;
}

void Game::LoadLevel(int level){

    // using sol lib to access Lua scripts
    sol::state lua;
    lua.open_libraries(sol::lib::base, sol::lib::os, sol::lib::math);
    // using Lua scripts to manage and configure assets
    string levelName = "Level" + to_string(level);
    lua.script_file("./assets/scripts/" + levelName + ".lua");
    // parse the lua script
    sol::table levelData = lua[levelName];
    sol::table levelAssets = levelData["assets"];
    /*********************************************/
    /*  LOAD ASSETS FROM LUA CONFIG FILE */
    /********************************************/
    unsigned int assetIndex = 0;
    while(true){
        sol::optional<sol::table> existsAssetIndexNode = levelAssets[assetIndex];
        if(existsAssetIndexNode == sol::nullopt){
            // reach lua EOF 
            break;
        }else{
            sol::table asset = levelAssets[assetIndex];
            string assetType = asset["type"];
            // get texture data
            if(assetType.compare("texture") == 0){
                string assetID = asset["id"];
                string assetFile = asset["file"];
                // add to assetManager
                assetManager->AddTexture(assetID, assetFile.c_str());
            }
        }
        assetIndex++; // incr
        cout<< "Assets " + to_string(assetIndex) + " is loaded successfully" << endl;
    }
    /*********************************************/
    /*  LOAD THE MAP FROM LUA CONFIG FILE */
    /********************************************/
    sol::table levelMap = levelData["map"];
    string mapTextureID = levelMap["textureAssetId"];
    string mapFile = levelMap["file"];
    m_map = new Map(mapTextureID, 
                    static_cast<int>(levelMap["scale"]),
                    static_cast<int>(levelMap["tileSize"]));
    m_map->LoadMap(mapFile,
                   static_cast<int>(levelMap["mapSizeX"]),
                   static_cast<int>(levelMap["mapSizeY"]));
    /*********************************************/
    /*  LOAD THE ENTITIES & COMPONENTS FROM LUA CONFIG FILE */
    /********************************************/
    sol::table levelEntities = levelData["entities"];
    unsigned int entityIndex = 0;
    while (true) {
        sol::optional<sol::table> existsEntityIndexNode = levelEntities[entityIndex];
        if (existsEntityIndexNode == sol::nullopt) {
            break;
        }
        else {
            sol::table entity = levelEntities[entityIndex];
            std::string entityName = entity["name"];
            LayerType entityLayerType = static_cast<LayerType>(static_cast<int>(entity["layer"]));

            // Add new entity
            auto& newEntity(manager.AddEntity(entityName, entityLayerType));

            // Add Transform Component
            sol::optional<sol::table> existsTransformComponent = entity["components"]["transform"];
            if (existsTransformComponent != sol::nullopt) {
                newEntity.AddComponent<TransformComponent>(
                    static_cast<int>(entity["components"]["transform"]["position"]["x"]),
                    static_cast<int>(entity["components"]["transform"]["position"]["y"]),
                    static_cast<int>(entity["components"]["transform"]["velocity"]["x"]),
                    static_cast<int>(entity["components"]["transform"]["velocity"]["y"]),
                    static_cast<int>(entity["components"]["transform"]["width"]),
                    static_cast<int>(entity["components"]["transform"]["height"]),
                    static_cast<int>(entity["components"]["transform"]["scale"])
                );
            }

            // Add sprite component
            sol::optional<sol::table> existsSpriteComponent = entity["components"]["sprite"];
            if (existsSpriteComponent != sol::nullopt) {
                std::string textureId = entity["components"]["sprite"]["textureAssetId"];
                bool isAnimated = entity["components"]["sprite"]["animated"];
                if (isAnimated) {
                    newEntity.AddComponent<SpriteComponent>(
                        textureId,
                        static_cast<int>(entity["components"]["sprite"]["frameCount"]),
                        static_cast<int>(entity["components"]["sprite"]["animationSpeed"]),
                        static_cast<bool>(entity["components"]["sprite"]["hasDirections"]),
                        static_cast<bool>(entity["components"]["sprite"]["fixed"])
                    );
                } else {
                    newEntity.AddComponent<SpriteComponent>(textureId, false);
                }
            }

            // Add input control component
            sol::optional<sol::table> existsInputComponent = entity["components"]["input"];
            if (existsInputComponent != sol::nullopt) {
                sol::optional<sol::table> existsKeyboardInputComponent = entity["components"]["input"]["keyboard"];
                if (existsKeyboardInputComponent != sol::nullopt) {
                    std::string upKey = entity["components"]["input"]["keyboard"]["up"];
                    std::string rightKey = entity["components"]["input"]["keyboard"]["right"];
                    std::string downKey = entity["components"]["input"]["keyboard"]["down"];
                    std::string leftKey = entity["components"]["input"]["keyboard"]["left"];
                    std::string shootKey = entity["components"]["input"]["keyboard"]["shoot"];
                    newEntity.AddComponent<KeyboardControlComponent>(upKey, rightKey, downKey, leftKey, shootKey);
                }
            }

            // Add collider component
            sol::optional<sol::table> existsColliderComponent = entity["components"]["collider"];
            if (existsColliderComponent != sol::nullopt) {
                std::string colliderTag = entity["components"]["collider"]["tag"];
                newEntity.AddComponent<ColliderComponent>(
                    colliderTag,
                    static_cast<int>(entity["components"]["transform"]["position"]["x"]),
                    static_cast<int>(entity["components"]["transform"]["position"]["y"]),
                    static_cast<int>(entity["components"]["transform"]["width"]),
                    static_cast<int>(entity["components"]["transform"]["height"])
                );
            }

            // Add projectile emitter component
            sol::optional<sol::table> existsProjectileEmitterComponent = entity["components"]["projectileEmitter"];
            if (existsProjectileEmitterComponent != sol::nullopt) {
                int parentEntityXPos = entity["components"]["transform"]["position"]["x"];
                int parentEntityYPos = entity["components"]["transform"]["position"]["y"];
                int parentEntityWidth = entity["components"]["transform"]["width"];
                int parentEntityHeight = entity["components"]["transform"]["height"];
                int projectileWidth = entity["components"]["projectileEmitter"]["width"];
                int projectileHeight = entity["components"]["projectileEmitter"]["height"];
                int projectileSpeed = entity["components"]["projectileEmitter"]["speed"];
                int projectileRange = entity["components"]["projectileEmitter"]["range"];
                int projectileAngle = entity["components"]["projectileEmitter"]["angle"];
                bool projectileShouldLoop = entity["components"]["projectileEmitter"]["shouldLoop"];
                std::string textureAssetId = entity["components"]["projectileEmitter"]["textureAssetId"];
                Entity& projectile(manager.AddEntity("projectile", PROJECTILE_LAYER));
                projectile.AddComponent<TransformComponent>(
                    parentEntityXPos + (parentEntityWidth / 2),
                    parentEntityYPos + (parentEntityHeight / 2),
                    0,
                    0,
                    projectileWidth,
                    projectileHeight,
                    1
                );
                projectile.AddComponent<SpriteComponent>(textureAssetId);
                projectile.AddComponent<ProjectileEmitterComponent>(
                    projectileSpeed,
                    projectileAngle,
                    projectileRange,
                    projectileShouldLoop
                );
                projectile.AddComponent<ColliderComponent>(
                    "PROJECTILE",
                    parentEntityXPos,
                    parentEntityYPos,
                    projectileWidth,
                    projectileHeight
                );
            }
        }
        entityIndex++;
    }
    // get chopper player
    chopperPlayer = manager.GetEntityByName("player");
    
}

void Game::ProcessInput(){
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
        
        default:{
            break;
        }
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
    // handle camera
    HandleCameraMove();
    // check collision
    CheckCollision();
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

void Game::HandleCameraMove(){
    // if chopperPlayer is initialized
    if(chopperPlayer){
        TransformComponent* mainPlayerTrans = chopperPlayer->GetComponent<TransformComponent>();
        // camera need to follow the chopper player
        camera.x = mainPlayerTrans->position.x - (WINDOW_WIDTH / 2);
        camera.y = mainPlayerTrans->position.y - (WINDOW_HEIGHT / 2);
        // clamp the camera
        camera.x = camera.x < 0 ? 0 : camera.x;
        camera.y = camera.y < 0 ? 0 : camera.y;
        camera.x = camera.x > camera.w ? camera.w : camera.x;
        camera.y = camera.y > camera.h ? camera.h : camera.y;
    }
}

void Game::CheckCollision(){
    // let the manager to check collision
    CollisionType collisionTagType = manager.CheckEntityCollision();
    if(collisionTagType == PLAYER_ENEMY_COLLISION){
        // collision with enemy game over
        ProcessGameOver();
    }
    if(collisionTagType == PLAYER_PROJECTILE_COLLISION){
        // collision with projectile game over
        ProcessGameOver();
    }
    if(collisionTagType == PLAYER_LEVEL_COMPLETE_COLLISION){
        // next level game
        ProcessNextLevel(1);
    }
}

void Game::ProcessGameOver(){
    cout << "Game Over" << endl;
    runningFlag = false;
}

void Game::ProcessNextLevel(int level){
    cout << "Next Level" << endl;
    runningFlag = false;
}

void Game::Destroy(){
    // SDL destroy
    SDL_DestroyRenderer(m_renderer);
    SDL_DestroyWindow(m_window);
    SDL_Quit();
}
