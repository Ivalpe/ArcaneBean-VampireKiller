#pragma once
#include "Player.h"


enum class GameSequence { GAME_START, CASTLE_ENTRY, BOSS_DOOR_OPEN };
enum class StateSequence { IDLE, SEQUENCE };

class Sequence
{
public:
    Sequence(GameSequence type, AABB hitbox);

    void SetSequence(GameSequence gs);
    void SetStateSequence(StateSequence ss);
    GameSequence GetGameSequence();
    StateSequence GetStateSequence();
    AABB GetHitBox();
    void StartWaiting();
    void Update();
    int GetCont();
    void SetSequence(GameSequence gs, AABB hitbox, int contNext);

private:
    GameSequence gameSeq;
    StateSequence stateSeq;
    AABB hitboxEnd;
    int cont;
    bool wait;
};