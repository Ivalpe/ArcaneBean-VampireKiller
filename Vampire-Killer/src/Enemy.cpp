#include "Enemy.h"
#include "Sprite.h"
#include "TileMap.h"
#include "Globals.h"
#include <raymath.h>
#include <iostream>
#include <cmath>

Enemy::Enemy(float width, float height) :
	Entity({ 0,0 }, width, height, width, height)
{
	map = nullptr;
	alive = false;
	medusaSpawn = false;
	invincibility = 0;
	time = 0;
}

Enemy::~Enemy()
{
}

AppStatus Enemy::Initialise(Point& p, EnemyType et, EnemyState s, EnemyLook view, TileMap* tilemap, int width, int height)
{
	ResourceManager& data = ResourceManager::Instance();
	Sprite* sprite;

	pos.x = p.x;
	pos.y = p.y;
	initialY = p.y;
	initialX = p.x;


	Entity::SetWidth(width);
	Entity::SetHeight(height);

	map = tilemap;
	type = et;
	state = s;
	look = view;
	alive = true;

	float w = width, h = height;

	switch (type)
	{
	case EnemyType::KNIGHT:

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

		sprite = dynamic_cast<Sprite*>(render);
		sprite->SetNumberAnimations((int)EnemyAnim::NUM_ANIMATIONS - 2);

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
		break;
	case EnemyType::MEDUSA_HEAD:
		if (data.LoadTexture(Resource::IMG_MEDUSA_HEAD, "Assets/Sprites/MedusaHead.png") != AppStatus::OK)
		{
			return AppStatus::ERROR;
		}

		render = new Sprite(data.GetTexture(Resource::IMG_MEDUSA_HEAD));
		if (render == nullptr)
		{
			LOG("Failed to allocate memory for player sprite");
			return AppStatus::ERROR;
		}

		sprite = dynamic_cast<Sprite*>(render);
		sprite->SetNumberAnimations((int)EnemyAnim::NUM_ANIMATIONS - 2);

		sprite->SetAnimationDelay((int)EnemyAnim::WALKING_RIGHT, ANIM_DELAY * 2);
		sprite->AddKeyFrame((int)EnemyAnim::WALKING_RIGHT, { 0, 0, -w, h });
		sprite->AddKeyFrame((int)EnemyAnim::WALKING_RIGHT, { w, 0, -w, h });
		sprite->SetAnimationDelay((int)EnemyAnim::WALKING_LEFT, ANIM_DELAY * 2);
		sprite->AddKeyFrame((int)EnemyAnim::WALKING_LEFT, { 0, 0, w, h });
		sprite->AddKeyFrame((int)EnemyAnim::WALKING_LEFT, { w, 0, w, h });

		if (look == EnemyLook::RIGHT)
			sprite->SetAnimation((int)EnemyAnim::WALKING_RIGHT);
		else
			sprite->SetAnimation((int)EnemyAnim::WALKING_LEFT);

		life = 1;
		break;
	case EnemyType::BAT:
		if (data.LoadTexture(Resource::IMG_MEDUSA_HEAD, "Assets/Sprites/Bat.png") != AppStatus::OK)
		{
			return AppStatus::ERROR;
		}

		render = new Sprite(data.GetTexture(Resource::IMG_MEDUSA_HEAD));
		if (render == nullptr)
		{
			LOG("Failed to allocate memory for player sprite");
			return AppStatus::ERROR;
		}

		sprite = dynamic_cast<Sprite*>(render);
		sprite->SetNumberAnimations((int)EnemyAnim::NUM_ANIMATIONS);

		sprite->SetAnimationDelay((int)EnemyAnim::WALKING_RIGHT, ANIM_DELAY * 2);
		sprite->AddKeyFrame((int)EnemyAnim::WALKING_RIGHT, { w, 0, -w, h });
		sprite->AddKeyFrame((int)EnemyAnim::WALKING_RIGHT, { w * 2, 0, -w, h });
		sprite->AddKeyFrame((int)EnemyAnim::WALKING_RIGHT, { w * 3, 0, -w, h });
		sprite->SetAnimationDelay((int)EnemyAnim::WALKING_LEFT, ANIM_DELAY * 2);
		sprite->AddKeyFrame((int)EnemyAnim::WALKING_LEFT, { w, 0, w, h });
		sprite->AddKeyFrame((int)EnemyAnim::WALKING_LEFT, { w * 2, 0, w, h });
		sprite->AddKeyFrame((int)EnemyAnim::WALKING_LEFT, { w * 3, 0, w, h });
		sprite->SetAnimationDelay((int)EnemyAnim::IDLE, ANIM_DELAY);
		sprite->AddKeyFrame((int)EnemyAnim::IDLE, { 0, 0, w, h });

		sprite->SetAnimation((int)EnemyAnim::IDLE);

		life = 1;
		break;
	default:
		LOG("Failed to load Enemy");
		return AppStatus::ERROR;
		break;
	}
}
void Enemy::Update()
{
	if (type == EnemyType::KNIGHT || type == EnemyType::BAT || (type == EnemyType::MEDUSA_HEAD && medusaSpawn))
	{
		Sprite* sprite = dynamic_cast<Sprite*>(render);
		sprite->Update();

		MoveY();
		if (type == EnemyType::KNIGHT)
			map->TestCollisionGround(GetHitbox(), &pos.y);

		MoveX();

		if (invincibility > 0) invincibility++;

		if (invincibility >= 15)
			FinishInvincibility();
	}
}
void Enemy::MoveY()
{
	if (type == EnemyType::KNIGHT)
		pos.y += ENEMY_SPEED;
	else if (type == EnemyType::MEDUSA_HEAD || (type == EnemyType::BAT && GetAnimation() != EnemyAnim::IDLE))
		pos.y = initialY + 20 * sin(time);
}
void Enemy::MoveX()
{
	int prev_x = pos.x;
	AABB box;

	switch (type)
	{
	case EnemyType::KNIGHT:

		if (look == EnemyLook::LEFT)	pos.x -= ENEMY_SPEED;
		else							pos.x += ENEMY_SPEED;

		box = GetHitbox();

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
		if ((!map->TestCollisionGroundRight(box) && look == EnemyLook::RIGHT) || pos.x >= WINDOW_WIDTH - TILE_SIZE)
		{
			SetAnimation((int)EnemyAnim::WALKING_LEFT);
			look = EnemyLook::LEFT;
		}
		if ((!map->TestCollisionGroundLeft(box) && look == EnemyLook::LEFT) || pos.x <= 0)
		{
			SetAnimation((int)EnemyAnim::WALKING_RIGHT);
			look = EnemyLook::RIGHT;
		}
		break;
	case EnemyType::MEDUSA_HEAD:
		if (look == EnemyLook::LEFT)	pos.x -= ENEMY_SPEED;
		else							pos.x += ENEMY_SPEED;

		time += 0.1;
		break;
	case EnemyType::BAT:
		if (GetAnimation() != EnemyAnim::IDLE)
		{
			if (look == EnemyLook::LEFT)	pos.x -= ENEMY_SPEED;
			else							pos.x += ENEMY_SPEED;
		}

		time += 0.1;
		break;
	default:
		break;
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

	if (type == EnemyType::BAT)
	{
		Color c = RED;
		c.a = 128;
		AABB box = GetAttackRadius();
		DrawRectangle(box.pos.x, box.pos.y, box.width, box.height, c);
	}


	DrawText(TextFormat("%d", getLife()), box.pos.x + (box.width / 2), box.pos.y + (box.height / 2), 1, WHITE);
}
void Enemy::Release()
{
	ResourceManager& data = ResourceManager::Instance();
	if (type == EnemyType::KNIGHT)
		data.ReleaseTexture(Resource::IMG_KNIGHT);
	else if (type == EnemyType::MEDUSA_HEAD)
		data.ReleaseTexture(Resource::IMG_MEDUSA_HEAD);
	else
		data.ReleaseTexture(Resource::IMG_BAT);
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
bool Enemy::IsAlive() const
{
	return alive;
}
void Enemy::Die()
{
	alive = false;
}
AABB Enemy::GetHitbox() const
{
	if (type == EnemyType::KNIGHT)
	{
		Point p(pos.x, pos.y - (height - 1));
		AABB hitbox(p, width, height);
		return hitbox;
	}
	else
	{
		Point p(pos.x, pos.y - (height - 1));
		AABB hitbox(p, width, height);
		return hitbox;
	}

}
AABB Enemy::GetAttackRadius() const
{
	Point p(pos.x - 50, pos.y - (height - 1) - 50);
	AABB hitbox(p, width + 100, height + 100);
	return hitbox;
}
void Enemy::MedusaSpawn(bool spawn)
{
	medusaSpawn = spawn;
	if (!spawn)
		RestartMedusa();
}
bool Enemy::IsMedusaSpawn()
{
	return medusaSpawn;
}
void Enemy::RestartMedusa()
{
	pos.x = initialX;
	pos.y = initialY;
}
void Enemy::SetState(EnemyState es)
{
	state = es;
	look == EnemyLook::RIGHT;
	SetAnimation((int)EnemyAnim::WALKING_RIGHT);
}
EnemyState Enemy::GetState()
{
	return state;
}