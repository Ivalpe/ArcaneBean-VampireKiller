#pragma once
#include "Entity.h"
#include "TileMap.h"

enum class EnemyLook { RIGHT, LEFT};

enum class EnemyType { KNIGHT, MEDUSA_HEAD };
enum class EnemyState { WALKING };
enum class EnemyAnim { WALKING_LEFT, WALKING_RIGHT, NUM_ANIMATIONS };

#define ENEMY_SPEED			1

class Enemy : public Entity
{
public:
	Enemy(float width, float height);
	~Enemy();

	AppStatus Initialise(Point& p, EnemyType et, EnemyState s, EnemyLook view, TileMap* tilemap, int width, int height);
	void Update();
	void DrawDebug(const Color& col) const;
	void Release();
	void Render();
	void MoveY();
	void MoveX();
	EnemyType getType() const;
	void Damaged(int dmg);
	int getLife() const;
	void StartInvincibility();
	void FinishInvincibility();
	int GetInvincibility();
	bool IsAlive() const;
	void Die();
	AABB GetHitbox() const;
	void MedusaSpawn(bool spawn);
	bool IsMedusaSpawn();
	

private:
	bool IsLookingRight() const;
	bool IsLookingLeft() const; 

	//Animation management
	void SetAnimation(int id);
	EnemyAnim GetAnimation();
	void RestartMedusa();

	EnemyState state;
	EnemyLook look;
	EnemyType type;
	TileMap* map;
	float time;
	int life, invincibility, initialX, initialY;
	bool alive, medusaSpawn;
};