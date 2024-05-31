#pragma once
#include "Entity.h"
#include "TileMap.h"
#include "Enemy.h"

//Representation model size: 32x32
#define PLAYER_FRAME_SIZE_WIDTH		16
#define PLAYER_FRAME_SIZE_HEIGHT	32

//Logical model size: 12x28
#define PLAYER_PHYSICAL_WIDTH	12
#define PLAYER_PHYSICAL_HEIGHT	28

//Horizontal speed and vertical speed while falling down
#define PLAYER_SPEED			2

//Vertical speed while on a ladder
#define PLAYER_LADDER_SPEED		1

//Frame animation delay while on a ladder
#define ANIM_LADDER_DELAY		(2*ANIM_DELAY)

//When jumping, initial jump speed and maximum falling speed
#define PLAYER_JUMP_FORCE		8

//Frame delay for updating the jump velocity
#define PLAYER_JUMP_DELAY		2

//Player is levitating when abs(speed) <= this value
#define PLAYER_LEVITATING_SPEED	4

//Gravity affects jumping velocity when jump_delay is 0
#define GRAVITY_FORCE			1

//Logic states
enum class State { IDLE, WALKING, JUMPING, FALLING, CLIMBING, DEAD, CROUCHING };
enum class Look { RIGHT, LEFT };
enum class AttackState { NO_ATTACKING, ATTACKING};

//Rendering states
enum class PlayerAnim {
	IDLE_LEFT, IDLE_RIGHT,
	WALKING_LEFT, WALKING_RIGHT,
	JUMPING_LEFT, JUMPING_RIGHT,
	FALLING_LEFT, FALLING_RIGHT,
	CLIMBING,
	CROUCHING_LEFT, CROUCHING_RIGHT,
	ATTACKING_GROUND_LEFT, ATTACKING_GROUND_RIGHT,
	ATTACKING_AIR_LEFT, ATTACKING_AIR_RIGHT,
	ATTACKING_CROUCH_LEFT, ATTACKING_CROUCH_RIGHT,
	LOOKING_AHEAD,
	NUM_ANIMATIONS
};

class Player : public Entity
{
public:
	Player(const Point& p, State s, Look view);
	~Player();

	AppStatus Initialise();
	void SetTileMap(TileMap* tilemap);
	void Update();
	void DrawDebug(const Color& col) const;
	void Release();
	State GetState();
	AttackState GetAttackState();
	std::pair<AABB, AABB> GetHitbox() const;
	void Draw();
	void InitScore();
	void IncrScore(int n);
	int GetScore();
	void Damaged(EnemyType enemyType);
	void Healed();
	int GetLife();
	void ClampLife();
	void UpDamage();
	void StartInvincibility();
	void FinishInvincibility();
	int GetInvincibility();
	int GetDmg() const;
	void MoveAuto(bool move);
	void BlockMovement(bool m);
	void LookAhead(bool trigger);
	void ChangeLook(Look l);
	void Stop();

private:
	bool IsLookingRight() const;
	bool IsLookingLeft() const;

	//Player mechanics
	void MoveX();
	void MoveY();
	void Attack();
	void LogicJumping();
	void LogicClimbing();

	//Animation management
	void SetAnimation(int id);
	PlayerAnim GetAnimation();
	void StartWalkingLeft();
	void StartWalkingRight();
	void StartFalling();
	void StartJumping();
	void StartClimbing();
	void ChangeAnimRight();
	void ChangeAnimLeft();
	void Move(Look l, AABB box, int prev_x);

	//Jump steps
	bool IsAscending() const;
	bool IsDescending() const;

	//Ladder get in/out steps
	bool IsInFirstHalfTile() const;
	bool IsInSecondHalfTile() const;

	State state, prev_state;
	Look look;
	AttackState staAtt;
	bool move, blockMovement;
	int jump_delay;
	int attacking;

	TileMap* map;
	int score, life, invincibility, dmg;
};