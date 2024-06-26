#include "Sprite.h"
#include "Fire.h"


Fire::Fire(const Point& p, int width, int height, int pos, ObjectType ot, FireType type) : Entity(p, width, height), type(type)
{
	posArray = pos;
	item = ot;
}

AppStatus Fire::Initialise()
{
	ResourceManager& data = ResourceManager::Instance();

	if (type == FireType::FIRE) {
		if (data.LoadTexture(Resource::IMG_FIRE, "Assets/Sprites/Fire.png") != AppStatus::OK) {
			return AppStatus::ERROR;
		}
		render = new Sprite(data.GetTexture(Resource::IMG_FIRE));
	}
	else if (type == FireType::CANDLE) {
		if (data.LoadTexture(Resource::IMG_CANDLE, "Assets/Sprites/Candle.png") != AppStatus::OK) {
			return AppStatus::ERROR;
		}
		render = new Sprite(data.GetTexture(Resource::IMG_CANDLE));
	}
	
	if (render == nullptr)
	{
		LOG("Failed to allocate memory for sprite");
		return AppStatus::ERROR;
	}

	Sprite* sprite = dynamic_cast<Sprite*>(render);
	sprite->SetNumberAnimations(1);

	sprite->SetAnimationDelay((int)FireAnim::IDLE, ANIM_FIRE);
	sprite->AddKeyFrame((int)FireAnim::IDLE, { 0, 0, FIRE_FRAME_SIZE_WIDTH, FIRE_FRAME_SIZE_HEIGHT });
	sprite->AddKeyFrame((int)FireAnim::IDLE, { FIRE_FRAME_SIZE_WIDTH, 0, FIRE_FRAME_SIZE_WIDTH, FIRE_FRAME_SIZE_HEIGHT });
	sprite->SetAnimation((int)FireAnim::IDLE);


	return AppStatus::OK;
}

void Fire::Update() {
	Sprite* sprite = dynamic_cast<Sprite*>(render);
	sprite->Update();
}

int Fire::GetPosArray() {
	return posArray;
}

void Fire::DrawDebug(const Color& col) const
{
	Entity::DrawHitbox(pos.x, pos.y, width, height, col);
}

void Fire::Release()
{
	ResourceManager& data = ResourceManager::Instance();
	data.ReleaseTexture(Resource::IMG_FIRE);

	render->Release();
}

ObjectType Fire::GetItemType() const
{
	return item;
}