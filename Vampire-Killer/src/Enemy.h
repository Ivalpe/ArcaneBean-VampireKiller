#pragma once
#include "Entity.h"

enum class EnemyLook { RIGHT, LEFT};

enum class EnemyState { WALKING };
enum class EnemyAnim { WALKING_LEFT, WALKING_RIGHT, NUM_ANIMATIONS };



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

private:
	bool IsLookingRight() const;
	bool IsLookingLeft() const; 

	//Animation management
	void SetAnimation(int id);
	EnemyAnim GetAnimation();

	EnemyState state;
	EnemyLook look;
	float w, h;
};