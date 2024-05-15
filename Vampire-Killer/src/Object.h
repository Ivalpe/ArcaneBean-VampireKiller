#pragma once
#include "Entity.h"
#include "TileMap.h"

#define OBJECT_PHYSICAL_SIZE	10
#define OBJECT_FRAME_SIZE		16

#define POINTS_BIG_HEART	10
#define POINTS_SMALL_HEART	20

#define SPEED_FALLING	1

enum class ObjectType { HEART };

enum class HeartAnim { FALLING, IDLE };


class Object : public Entity
{
public:
	Object(const Point& p, ObjectType t, TileMap* tilemap);
	~Object();

	void DrawDebug(const Color& col) const;
	int Points() const;
	AppStatus Initialise();
	HeartAnim GetHeartState() const;
	void Update();
	AABB GetHitbox() const;

private:
	void SetAnimation(int id);

	ObjectType type;
	HeartAnim currentAnim;
	TileMap* map;
};
