#include "Sequence.h"

Sequence::Sequence(GameSequence game, AABB hitbox)
{
	gameSeq = game;
	stateSeq = StateSequence::IDLE;
	hitboxEnd = hitbox;
	cont = 120;
	y = 0;
	wait = false;
}

void Sequence::SetSequence(GameSequence gs)
{
	gameSeq = gs;
}

void Sequence::SetStateSequence(StateSequence ss)
{
	stateSeq = ss;
}

GameSequence Sequence::GetGameSequence()
{
	return gameSeq;
}

StateSequence Sequence::GetStateSequence()
{
	return stateSeq;
}

AABB Sequence::GetHitBox()
{
	return hitboxEnd;
}

void Sequence::StartWaiting()
{
	wait = true;
}

void Sequence::Update()
{
	if (wait)
		cont--;

	if (gameSeq == GameSequence::BOSS_DOOR_OPEN && stateSeq == StateSequence::SEQUENCE)
		y--;
}

int Sequence::GetCont()
{
	return cont;
}

void Sequence::SetSequence(GameSequence gs, AABB hitbox, int contNext)
{
	gameSeq = gs;
	hitboxEnd = hitbox;
	stateSeq = StateSequence::IDLE;
	cont = contNext;
	wait = false;
}

void Sequence::SetY(int posy)
{
	y = posy;
}

int Sequence::GetY()
{
	return y;
}


