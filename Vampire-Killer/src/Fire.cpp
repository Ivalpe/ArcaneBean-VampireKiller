#include "Sprite.h"
#include "Fire.h"

Fire::Fire(const Point& p, int width, int height, int pos) : Entity(p, width, height)
{
	posArray = pos;
}

AppStatus Fire::Initialise()
{

	ResourceManager& data = ResourceManager::Instance();
	if (data.LoadTexture(Resource::IMG_FIRE, "Assets/Sprites/Fire.png") != AppStatus::OK)
	{
		return AppStatus::ERROR;
	}

	render = new Sprite(data.GetTexture(Resource::IMG_FIRE));
	if (render == nullptr)
	{
		LOG("Failed to allocate memory for fire sprite");
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