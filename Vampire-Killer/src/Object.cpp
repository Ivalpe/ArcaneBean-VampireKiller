#include "Object.h"
#include "StaticImage.h"
#include "Sprite.h"
#include "TileMap.h"

Object::Object(const Point& p, ObjectType t, TileMap* tilemap) : Entity(p, OBJECT_PHYSICAL_SIZE, OBJECT_PHYSICAL_SIZE, OBJECT_FRAME_SIZE, OBJECT_FRAME_SIZE)
{
	type = t;
	currentAnim = ItemAnim::BREAKING;
	const int n = TILE_SIZE;
	map = tilemap;
	floatTime = 30;
	Initialise();
}
AppStatus Object::Initialise()
{
	ResourceManager& data = ResourceManager::Instance();
	if (data.LoadTexture(Resource::IMG_ITEMS, "Assets/Sprites/Items.png") != AppStatus::OK)
	{
		return AppStatus::ERROR;
	}

	render = new Sprite(data.GetTexture(Resource::IMG_ITEMS));
	if (render == nullptr)
	{
		LOG("Failed to allocate memory for items sprite");
		return AppStatus::ERROR;
	}

	Sprite* sprite = dynamic_cast<Sprite*>(render);
	sprite->SetNumberAnimations((int)ItemAnim::NUM_ANIMATIONS);

	sprite->SetAnimationDelay((int)ItemAnim::BREAKING, 10);
	sprite->AddKeyFrame((int)ItemAnim::BREAKING, { 0, 0, OBJECT_FRAME_SIZE, OBJECT_FRAME_SIZE });
	sprite->AddKeyFrame((int)ItemAnim::BREAKING, { OBJECT_FRAME_SIZE, 0, OBJECT_FRAME_SIZE, OBJECT_FRAME_SIZE });
	sprite->AddKeyFrame((int)ItemAnim::BREAKING, { OBJECT_FRAME_SIZE * 2, 0, OBJECT_FRAME_SIZE, OBJECT_FRAME_SIZE });

	switch (type)
	{
	case ObjectType::HEART:
		sprite->SetAnimationDelay((int)ItemAnim::IDLE, 0);
		sprite->AddKeyFrame((int)ItemAnim::IDLE, { 0, OBJECT_FRAME_SIZE, OBJECT_FRAME_SIZE, OBJECT_FRAME_SIZE });
		sprite->SetAnimationDelay((int)ItemAnim::FALLING, 0);
		sprite->AddKeyFrame((int)ItemAnim::FALLING, { OBJECT_FRAME_SIZE * 2, OBJECT_FRAME_SIZE, OBJECT_FRAME_SIZE, OBJECT_FRAME_SIZE });
		break;
	case ObjectType::HEART_BIG:
		sprite->SetAnimationDelay((int)ItemAnim::IDLE, 0);
		sprite->AddKeyFrame((int)ItemAnim::IDLE, { OBJECT_FRAME_SIZE, OBJECT_FRAME_SIZE, OBJECT_FRAME_SIZE, OBJECT_FRAME_SIZE });
		sprite->SetAnimationDelay((int)ItemAnim::FALLING, 10);
		sprite->AddKeyFrame((int)ItemAnim::FALLING, { 0, 0, OBJECT_FRAME_SIZE, OBJECT_FRAME_SIZE });
		sprite->AddKeyFrame((int)ItemAnim::FALLING, { OBJECT_FRAME_SIZE, 0, OBJECT_FRAME_SIZE, OBJECT_FRAME_SIZE });
		sprite->AddKeyFrame((int)ItemAnim::FALLING, { OBJECT_FRAME_SIZE * 2, 0, OBJECT_FRAME_SIZE, OBJECT_FRAME_SIZE });
		break;
	case ObjectType::WHIPE:
		sprite->SetAnimationDelay((int)ItemAnim::IDLE, 0);
		sprite->AddKeyFrame((int)ItemAnim::IDLE, { 0, OBJECT_FRAME_SIZE * 2, OBJECT_FRAME_SIZE, OBJECT_FRAME_SIZE });
		sprite->SetAnimationDelay((int)ItemAnim::FALLING, 10);
		sprite->AddKeyFrame((int)ItemAnim::FALLING, { 0, 0, OBJECT_FRAME_SIZE, OBJECT_FRAME_SIZE });
		sprite->AddKeyFrame((int)ItemAnim::FALLING, { OBJECT_FRAME_SIZE, 0, OBJECT_FRAME_SIZE, OBJECT_FRAME_SIZE });
		sprite->AddKeyFrame((int)ItemAnim::FALLING, { OBJECT_FRAME_SIZE * 2, 0, OBJECT_FRAME_SIZE, OBJECT_FRAME_SIZE });
		break;
	default:
		break;
	}

	sprite->SetAnimation((int)ItemAnim::BREAKING);


	return AppStatus::OK;
}
Object::~Object()
{
}
void Object::DrawDebug(const Color& col) const
{
	AABB hitbox = GetHitbox();
	Entity::DrawHitbox(hitbox.pos.x, hitbox.pos.y + hitbox.height, hitbox.width, hitbox.height, col);  
}
AABB Object::GetHitbox() const
{
	Point p(pos.x - 1, pos.y - (height + 3));
	AABB objectHitbox(p, width, height);
	return objectHitbox;
}
void Object::Release()
{
	ResourceManager& data = ResourceManager::Instance();
	data.ReleaseTexture(Resource::IMG_ITEMS);

	render->Release();

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
ItemAnim Object::GetHeartState() const
{
	return currentAnim;
}
void Object::Update() {
	Sprite* sprite = dynamic_cast<Sprite*>(render);
	sprite->Update();

	AABB box = GetHitbox();
	if (currentAnim == ItemAnim::BREAKING)
	{
		floatTime--;
		if (floatTime <= 0)
		{
			currentAnim = ItemAnim::FALLING;
			SetAnimation((int)ItemAnim::FALLING);
		}
	}
	else if (currentAnim == ItemAnim::FALLING && !map->TestCollisionGround(box, &pos.y))
	{
		pos.y += SPEED_FALLING;
	}
	else
	{
		SetAnimation((int)ItemAnim::IDLE);
		currentAnim = ItemAnim::IDLE;
	}
}
void Object::SetAnimation(int id)
{
	Sprite* sprite = dynamic_cast<Sprite*>(render);
	sprite->SetAnimation(id);
}