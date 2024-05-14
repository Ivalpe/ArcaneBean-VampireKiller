#include "Enemy.h"
#include "Sprite.h"
#include "TileMap.h"
#include "Globals.h"
#include <raymath.h>
#include <iostream>

Enemy::Enemy(const Point& p, EnemyState s, EnemyLook view, float width, float height) :
	Entity(p, width, height, width, height)
{
	w = width;
	h = height;
	state = s;
	look = view;
}

Enemy::~Enemy()
{
}

AppStatus Enemy::Initialise()
{
	ResourceManager& data = ResourceManager::Instance();
	if (data.LoadTexture(Resource::IMG_KNIGHT, "Assets/Sprites/Knight.png") != AppStatus::OK)
	{
		return AppStatus::ERROR;
	}

	render = new Sprite(data.GetTexture(Resource::IMG_KNIGHT));
	if (render == nullptr)
	{
		LOG("Failed to allocate memory for player sprite");
		return AppStatus::ERROR;
	}

	Sprite* sprite = dynamic_cast<Sprite*>(render);
	sprite->SetNumberAnimations((int)EnemyAnim::NUM_ANIMATIONS);

	
	sprite->SetAnimationDelay((int)EnemyAnim::WALKING_RIGHT, ANIM_DELAY * 2);
	sprite->AddKeyFrame((int)EnemyAnim::WALKING_RIGHT, { 0, 0, w, h });
	sprite->AddKeyFrame((int)EnemyAnim::WALKING_RIGHT, { w, 0, w, h });
	sprite->AddKeyFrame((int)EnemyAnim::WALKING_RIGHT, { w * 2, 0, w, h });
	sprite->SetAnimationDelay((int)EnemyAnim::WALKING_LEFT, ANIM_DELAY * 2);
	sprite->AddKeyFrame((int)EnemyAnim::WALKING_LEFT, { 0, 0, -w, h });
	sprite->AddKeyFrame((int)EnemyAnim::WALKING_LEFT, { w, 0, -w, h });
	sprite->AddKeyFrame((int)EnemyAnim::WALKING_LEFT, { w * 2, 0, -w, h });
	
	sprite->SetAnimation((int)EnemyAnim::WALKING_RIGHT);
}
void Enemy::Update() {
	Sprite* sprite = dynamic_cast<Sprite*>(render);
	sprite->Update();
}
void Enemy::Render() {
	Point p = GetRenderingPosition();
	render->Draw(pos.x, pos.y);
}
void Enemy::DrawDebug(const Color& col) const
{
	Entity::DrawHitbox(pos.x, pos.y, width, height, col);

	DrawPixel(pos.x, pos.y, WHITE);
}
void Enemy::Release()
{
	ResourceManager& data = ResourceManager::Instance();
	data.ReleaseTexture(Resource::IMG_PLAYER);

	render->Release();
}
bool Enemy::IsLookingRight() const
{
	return look == EnemyLook::RIGHT;
}
bool Enemy::IsLookingLeft() const
{
	return look == EnemyLook::LEFT;
}
void Enemy::SetAnimation(int id)
{
	Sprite* sprite = dynamic_cast<Sprite*>(render);
	sprite->SetAnimation(id);
}
EnemyAnim Enemy::GetAnimation()
{
	Sprite* sprite = dynamic_cast<Sprite*>(render);
	return (EnemyAnim)sprite->GetAnimation();
}