#pragma once
#include "Entity.h"
#include "Object.h"

//Representation model size: 16x16
#define FIRE_FRAME_SIZE_WIDTH		16
#define FIRE_FRAME_SIZE_HEIGHT		16

#define ANIM_FIRE	10
#define ANIM_CANDLE 10


enum class FireType {
	FIRE,
	CANDLE
};

enum class FireAnim {
	IDLE
};

class Fire : public Entity
{
public:

	Fire(const Point& p, int width, int height, int pos, ObjectType ot, FireType type);

	AppStatus Initialise();
	void Update();
	int GetPosArray();
	void DrawDebug(const Color& col) const;
	void Release();
	ObjectType GetItemType() const;
private:
	int posArray;

	FireType type;
	ObjectType item;

};