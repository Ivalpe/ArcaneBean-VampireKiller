#pragma once
#include "Entity.h"
#include "TileMap.h"

enum class EnemyLook { RIGHT, LEFT};

enum class EnemyType { KNIGHT };
enum class EnemyState { WALKING };
enum class EnemyAnim { WALKING_LEFT, WALKING_RIGHT, NUM_ANIMATIONS };

#define ENEMY_SPEED			1

class Enemy : public Entity
{
public:
	Enemy(const Point& p, EnemyState s, EnemyLook view, float width, float height);
	~Enemy();

	AppStatus Initialise();
	void Update();
	void DrawDebug(const Color& col) const;
	void Release();
	void Render();
	void MoveY();
	void MoveX();
	void SetTileMap(TileMap* tilemap);
	EnemyType getType();

private:
	bool IsLookingRight() const;
	bool IsLookingLeft() const; 

	//Animation management
	void SetAnimation(int id);
	EnemyAnim GetAnimation();

	EnemyState state;
	EnemyLook look;
	EnemyType type;
	TileMap* map;
	float w, h;
};