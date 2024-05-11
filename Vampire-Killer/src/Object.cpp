#include "Object.h"
#include "StaticImage.h"

Object::Object(const Point& p, ObjectType t) : Entity(p, OBJECT_PHYSICAL_SIZE, OBJECT_PHYSICAL_SIZE, OBJECT_FRAME_SIZE, OBJECT_FRAME_SIZE)
{
	type = t;
	isCreated = true;
	Rectangle rc;
	const int n = TILE_SIZE;
	switch (type)
	{
	case ObjectType::BIG_HEART: rc = { 0 * n, 10 * n, n, n }; break;
	case ObjectType::SMALL_HEART: rc = { n, 10 * n, n, n }; break;
	case ObjectType::FIRE: rc = { n * 2, 10 * n, n, n }; break;
	default: LOG("Internal error: object creation of invalid type");
	}

	ResourceManager& data = ResourceManager::Instance();
	render = new StaticImage(data.GetTexture(Resource::IMG_TILES), rc);
}
Object::~Object()
{
}
void Object::DrawDebug(const Color& col) const
{
	Entity::DrawHitbox(pos.x, pos.y, width, height, col);
}
int Object::Points() const
{
	if (type == ObjectType::BIG_HEART)		return POINTS_BIG_HEART;
	else if (type == ObjectType::SMALL_HEART)	return POINTS_SMALL_HEART;
	else
	{
		LOG("Internal error: object type invalid when giving points");
		return 0;
	}
}
