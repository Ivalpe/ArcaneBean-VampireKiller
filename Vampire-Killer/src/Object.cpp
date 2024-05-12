#include "Object.h"
#include "StaticImage.h"
#include "Sprite.h"
#include "TileMap.h"

Object::Object(const Point& p, ObjectType t, TileMap* tilemap) : Entity(p, OBJECT_PHYSICAL_SIZE, OBJECT_PHYSICAL_SIZE, OBJECT_FRAME_SIZE, OBJECT_FRAME_SIZE)
{
	type = t;
	currentAnim = HeartAnim::FALLING;
	const int n = TILE_SIZE;
	map = tilemap;
	Initialise();
}
AppStatus Object::Initialise()
{

	ResourceManager& data = ResourceManager::Instance();
	if (data.LoadTexture(Resource::IMG_ITEMS, "Assets/Sprites/Heart.png") != AppStatus::OK)
	{
		return AppStatus::ERROR;
	}

	render = new Sprite(data.GetTexture(Resource::IMG_ITEMS));
	if (render == nullptr)
	{
		LOG("Failed to allocate memory for heart sprite");
		return AppStatus::ERROR;
	}

	Sprite* sprite = dynamic_cast<Sprite*>(render);
	sprite->SetNumberAnimations(2);

	sprite->SetAnimationDelay((int)HeartAnim::IDLE, 0);
	sprite->AddKeyFrame((int)HeartAnim::IDLE, { 0, 0, OBJECT_FRAME_SIZE, OBJECT_FRAME_SIZE });
	sprite->SetAnimationDelay((int)HeartAnim::FALLING, 0);
	sprite->AddKeyFrame((int)HeartAnim::FALLING, { OBJECT_FRAME_SIZE, 0, OBJECT_FRAME_SIZE, OBJECT_FRAME_SIZE });

	sprite->SetAnimation((int)HeartAnim::FALLING);

	return AppStatus::OK;
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
	if (type == ObjectType::HEART)		return POINTS_BIG_HEART;
	else
	{
		LOG("Internal error: object type invalid when giving points");
		return 0;
	}
}

HeartAnim Object::GetHeartState() const
{
	return currentAnim;
}

void Object::Update() {
	AABB box = GetHitbox();
	if (!map->TestCollisionGround(box, &pos.y) && currentAnim == HeartAnim::FALLING)
		pos.y+=SPEED_FALLING;
	else 
		currentAnim = HeartAnim::IDLE;

	switch (currentAnim)
	{
	case HeartAnim::FALLING:	SetAnimation((int)HeartAnim::FALLING);
		break;
	case HeartAnim::IDLE:		SetAnimation((int)HeartAnim::IDLE);
		break;
	default:
		break;
	}

}

void Object::SetAnimation(int id)
{
	Sprite* sprite = dynamic_cast<Sprite*>(render);
	sprite->SetAnimation(id);
}