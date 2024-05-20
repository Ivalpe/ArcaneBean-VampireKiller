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
	map = nullptr;
	type = EnemyType::KNIGHT;
	invincibility = 0;
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
	sprite->AddKeyFrame((int)EnemyAnim::WALKING_RIGHT, { 0, 0, -w, h });
	sprite->AddKeyFrame((int)EnemyAnim::WALKING_RIGHT, { w, 0, -w, h });
	sprite->AddKeyFrame((int)EnemyAnim::WALKING_RIGHT, { w * 2, 0, -w, h });
	sprite->SetAnimationDelay((int)EnemyAnim::WALKING_LEFT, ANIM_DELAY * 2);
	sprite->AddKeyFrame((int)EnemyAnim::WALKING_LEFT, { 0, 0, w, h });
	sprite->AddKeyFrame((int)EnemyAnim::WALKING_LEFT, { w, 0, w, h });
	sprite->AddKeyFrame((int)EnemyAnim::WALKING_LEFT, { w * 2, 0, w, h });
	
	sprite->SetAnimation((int)EnemyAnim::WALKING_LEFT);

	life = 8;
}
void Enemy::Update() 
{
	Sprite* sprite = dynamic_cast<Sprite*>(render);
	sprite->Update();

	MoveY();
	map->TestCollisionGround(GetHitbox(), &pos.y);

	MoveX();

	if (invincibility > 0) invincibility++;

	if (invincibility >= 15)
		FinishInvincibility();

}
void Enemy::MoveY() 
{
	pos.y += ENEMY_SPEED;
}
void Enemy::MoveX()
{
	int prev_x = pos.x;

	if (look == EnemyLook::LEFT)	pos.x -= ENEMY_SPEED;
	else							pos.x += ENEMY_SPEED;

	AABB box = GetHitbox();
	
	if (map->TestCollisionWallLeft(box) || pos.x <= 0)
	{
		pos.x = prev_x;
		SetAnimation((int)EnemyAnim::WALKING_RIGHT);
		look = EnemyLook::RIGHT;
	}

	if (map->TestCollisionWallRight(box) || pos.x >= WINDOW_WIDTH - 16)
	{
		pos.x = prev_x;
		SetAnimation((int)EnemyAnim::WALKING_LEFT);
		look = EnemyLook::LEFT;
	}

	if (!map->TestCollisionGroundRight(box) && look == EnemyLook::RIGHT)
	{
		SetAnimation((int)EnemyAnim::WALKING_LEFT);
		look = EnemyLook::LEFT;
	}
	if (!map->TestCollisionGroundLeft(box) && look == EnemyLook::LEFT)
	{
		SetAnimation((int)EnemyAnim::WALKING_RIGHT);
		look = EnemyLook::RIGHT;
	}

	if (pos.x >= WINDOW_WIDTH - TILE_SIZE)
	{
		SetAnimation((int)EnemyAnim::WALKING_LEFT);
		look = EnemyLook::LEFT;
	}
	else if (pos.x <= 0)
	{
		SetAnimation((int)EnemyAnim::WALKING_RIGHT);
		look = EnemyLook::RIGHT;
	}
}
void Enemy::Render() {
	Point p = GetRenderingPosition();
	render->Draw(pos.x, pos.y);
}
void Enemy::DrawDebug(const Color& col) const
{
	Entity::DrawHitbox(pos.x, pos.y, width, height, col);
	DrawPixel(pos.x, pos.y, WHITE);

	AABB box = GetHitbox();
	DrawRectangle(box.pos.x + box.width, box.pos.y + box.height + 2, 1, 1, BLACK);

	DrawText(TextFormat("%d", getLife()), box.pos.x + (box.width / 2), box.pos.y + (box.height / 2), 1, WHITE);
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
void Enemy::SetTileMap(TileMap* tilemap)
{
	map = tilemap;
}
EnemyType Enemy::getType() const
{
	return type;
}
void Enemy::Damaged(int dmg)
{
	life -= dmg;
}
int Enemy::getLife() const
{
	return life;
}
void Enemy::StartInvincibility() {
	invincibility = 1;
}
void Enemy::FinishInvincibility() {
	invincibility = 0;
}
int Enemy::GetInvincibility()
{
	return invincibility;
}