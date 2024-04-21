#pragma once
#include "Globals.h"
#include "Scene.h"

enum class GameState { MAIN_SCREEN, MAIN_MENU, PLAYING, SETTINGS, GAME_OVER};

class Game
{
public:
    Game();
    ~Game();

    AppStatus Initialise(float scale);
    AppStatus Update();
    void Render();
    void Cleanup();

private:
    AppStatus BeginPlay();
    void FinishPlay();

    AppStatus LoadResources();
    void UnloadResources();

    GameState state;
    Scene *scene;
    const Texture2D *img_menu;
    const Texture2D *img_mscreen;
    const Texture2D *img_gameover;

    //To work with original game units and then scale the result
    RenderTexture2D target;
    Rectangle src, dst;

    int holdTimer = 0;
    bool holdTimerStarted = false;
    int frameCount = 0;

   

};