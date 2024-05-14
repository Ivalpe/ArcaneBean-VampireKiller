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

	sprite->SetAnimationDelay((int)EnemyAnim::WALKING_RIGHT, ANIM_DELAY);
	sprite->AddKeyFrame((int)EnemyAnim::WALKING_RIGHT, { 0, 0, w, h });
	sprite->AddKeyFrame((int)EnemyAnim::WALKING_RIGHT, { w, 0, w, h });
	sprite->AddKeyFrame((int)EnemyAnim::WALKING_RIGHT, { w * 2, 0, w, h });
	sprite->SetAnimationDelay((int)EnemyAnim::WALKING_LEFT, ANIM_DELAY);
	sprite->AddKeyFrame((int)EnemyAnim::WALKING_LEFT, { 0, 0, -w, h });
	sprite->AddKeyFrame((int)EnemyAnim::WALKING_LEFT, { w, 0, -w, h });
	sprite->AddKeyFrame((int)EnemyAnim::WALKING_LEFT, { w * 2, 0, -w, h });

}