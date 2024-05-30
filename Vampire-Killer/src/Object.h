#pragma once
#include "Entity.h"
#include "TileMap.h"

#define OBJECT_PHYSICAL_SIZE	10
#define OBJECT_FRAME_SIZE		16

#define POINTS_BIG_HEART	10
#define POINTS_SMALL_HEART	20

#define SPEED_FALLING	2

enum class ObjectType { HEART, HEART_BIG, WHIPE, BLUE_ORB, RING, KEY };

enum class ItemAnim { BREAKING, FALLING, IDLE, NUM_ANIMATIONS };


class Object : public Entity
{
public:
	Object(const Point& p, ObjectType t, TileMap* tilemap);
	~Object();

	void DrawDebug(const Color& col) const;
	int Points() const;
	AppStatus Initialise();
	ItemAnim GetHeartState() const;
	void Update();
	AABB GetHitbox() const;
	void Release();

private:
	void SetAnimation(int id);

	ObjectType type;
	ItemAnim currentAnim;
	TileMap* map;
	int floatTime;
};
