#pragma once
#include <raylib.h>
#include "Player.h"
#include "Fire.h"
#include "TileMap.h"
#include "Object.h"
#include "Levels.h"

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
    bool getLevelOver();

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
    Camera2D camera;
    Music musicStage0;

    DebugMode debug;

    bool levelOver;
    Levels* lvlList;
};
