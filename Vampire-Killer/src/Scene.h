#pragma once
#include <raylib.h>
#include "Player.h"
#include "Fire.h"
#include "TileMap.h"
#include "Object.h"
#include "Levels.h"
#include "Enemy.h"
#include "Bar.h"
#include "StaticImage.h"
#include "Sequence.h"

enum class DebugMode { OFF, SPRITES_AND_HITBOXES, ONLY_HITBOXES, SIZE };

class Scene
{
public:
    Scene();
    ~Scene();

    AppStatus Init();
    void Update();
    void Render();
    void Release();
    bool getLevelOver() const;
    bool getLevelWin() const;

private:
    AppStatus LoadLevel(int stage, int direction);

    void CheckCollisions();

    void RenderObjects() const;
    void RenderObjectsDebug(const Color& col) const;
    void LoadNextLevel();
    void RenderGUI() const;
    Player* player;
    TileMap* level;

    std::vector<Object*> objects;
    std::vector<Fire*> fires; 
    std::vector<Enemy*> enemies;

    Camera2D camera;
    Music musicStage;
    Sound hurt, enter, lati, pick;

    DebugMode debug;

    bool levelOver, gameWin;
    Levels* lvlList;
    Bar* playerBar;
    Bar* bossBar;
    Texture2D ui, gameStart, falseTile, door, cloud;
    Sequence* seq;
    int score, stage, hearts, life, contDie, medusaSpawnRate, posCloud;
    int moveCloud;
};
