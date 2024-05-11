#pragma once
#include "Entity.h"

//Representation model size: 16x16
#define FIRE_FRAME_SIZE_WIDTH		16
#define FIRE_FRAME_SIZE_HEIGHT		16

#define ANIM_FIRE	10

enum class FireAnim {
	IDLE
};

class Fire : public Entity
{
public:
	Fire(const Point& p, int width, int height, int pos);
	AppStatus Initialise();
	void Update();
	int GetPosArray();

private:
	int posArray;
};