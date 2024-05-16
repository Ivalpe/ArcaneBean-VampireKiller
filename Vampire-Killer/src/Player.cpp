#include "Player.h"
#include "Sprite.h"
#include "TileMap.h"
#include "Globals.h"
#include <raymath.h>
#include <iostream>
#include "Enemy.h"

Player::Player(const Point& p, State s, Look view) :
	Entity(p, PLAYER_PHYSICAL_WIDTH, PLAYER_PHYSICAL_HEIGHT, PLAYER_FRAME_SIZE_WIDTH, PLAYER_FRAME_SIZE_HEIGHT)
{
	state = s;
	look = view;
	jump_delay = PLAYER_JUMP_DELAY;
	map = nullptr;
	life = 20;
	invincibility = 0;
}
Player::~Player()
{
}
AppStatus Player::Initialise()
{
	attacking = 0;

	int i;
	const int nw = PLAYER_FRAME_SIZE_WIDTH, nh = PLAYER_FRAME_SIZE_HEIGHT;

	ResourceManager& data = ResourceManager::Instance();
	if (data.LoadTexture(Resource::IMG_PLAYER, "Assets/Sprites/Simon.png") != AppStatus::OK)
	{
		return AppStatus::ERROR;
	}

	render = new Sprite(data.GetTexture(Resource::IMG_PLAYER));
	if (render == nullptr)
	{
		LOG("Failed to allocate memory for player sprite");
		return AppStatus::ERROR;
	}

	Sprite* sprite = dynamic_cast<Sprite*>(render);
	sprite->SetNumberAnimations((int)PlayerAnim::NUM_ANIMATIONS);

	sprite->SetAnimationDelay((int)PlayerAnim::IDLE_RIGHT, ANIM_DELAY);
	sprite->AddKeyFrame((int)PlayerAnim::IDLE_RIGHT, { 0, 0, nw, nh });
	sprite->SetAnimationDelay((int)PlayerAnim::IDLE_LEFT, ANIM_DELAY);
	sprite->AddKeyFrame((int)PlayerAnim::IDLE_LEFT, { 0, 0, -nw, nh });

	sprite->SetAnimationDelay((int)PlayerAnim::WALKING_RIGHT, ANIM_DELAY);
	for (i = 0; i < 3; ++i)
		sprite->AddKeyFrame((int)PlayerAnim::WALKING_RIGHT, { (float)i * nw, 0, nw, nh });
	sprite->SetAnimationDelay((int)PlayerAnim::WALKING_LEFT, ANIM_DELAY);
	for (i = 0; i < 3; ++i)
		sprite->AddKeyFrame((int)PlayerAnim::WALKING_LEFT, { (float)i * nw, 0, -nw, nh });

	sprite->SetAnimationDelay((int)PlayerAnim::FALLING_RIGHT, ANIM_DELAY);
	sprite->AddKeyFrame((int)PlayerAnim::FALLING_RIGHT, { 6 * nw, 0, nw, nh });
	sprite->AddKeyFrame((int)PlayerAnim::FALLING_RIGHT, { 7 * nw, 0, nw, nh });
	sprite->SetAnimationDelay((int)PlayerAnim::FALLING_LEFT, ANIM_DELAY);
	sprite->AddKeyFrame((int)PlayerAnim::FALLING_LEFT, { 6 * nw, 0, -nw, nh });
	sprite->AddKeyFrame((int)PlayerAnim::FALLING_LEFT, { 7 * nw, 0, -nw, nh });

	sprite->SetAnimationDelay((int)PlayerAnim::JUMPING_RIGHT, ANIM_DELAY);
	sprite->AddKeyFrame((int)PlayerAnim::JUMPING_RIGHT, { 3 * nw, 0, nw, nh });
	sprite->SetAnimationDelay((int)PlayerAnim::JUMPING_LEFT, ANIM_DELAY);
	sprite->AddKeyFrame((int)PlayerAnim::JUMPING_LEFT, { 3 * nw, 0, -nw, nh });

	sprite->SetAnimationDelay((int)PlayerAnim::CLIMBING, ANIM_LADDER_DELAY);
	for (i = 0; i < 4; ++i)
		sprite->AddKeyFrame((int)PlayerAnim::CLIMBING, { (float)i * nw, 6 * nh, nw, nh });
	sprite->SetAnimationDelay((int)PlayerAnim::CLIMBING_PRE_TOP, ANIM_DELAY);
	sprite->AddKeyFrame((int)PlayerAnim::CLIMBING_PRE_TOP, { 4 * nw, 6 * nh, nw, nh });
	sprite->SetAnimationDelay((int)PlayerAnim::CLIMBING_TOP, ANIM_DELAY);
	sprite->AddKeyFrame((int)PlayerAnim::CLIMBING_TOP, { 5 * nw, 6 * nh, nw, nh });

	sprite->SetAnimationDelay((int)PlayerAnim::CROUCHING_LEFT, ANIM_DELAY);
	sprite->AddKeyFrame((int)PlayerAnim::CROUCHING_LEFT, { 3 * nw, 0, -nw, nh });
	sprite->SetAnimationDelay((int)PlayerAnim::CROUCHING_RIGHT, ANIM_DELAY);
	sprite->AddKeyFrame((int)PlayerAnim::CROUCHING_RIGHT, { 3 * nw, 0, nw, nh });

	//Charging
	sprite->SetAnimationDelay((int)PlayerAnim::ATTACKING_GROUND_LEFT, 0);
	sprite->AddKeyFrame((int)PlayerAnim::ATTACKING_GROUND_LEFT, { 0,	nw * 2,	-nw * 4, nh });
	sprite->AddKeyFrame((int)PlayerAnim::ATTACKING_GROUND_LEFT, { nw * 4, nw * 2, -nw * 4, nh });
	sprite->AddKeyFrame((int)PlayerAnim::ATTACKING_GROUND_LEFT, { nw * 8, nw * 2, -nw * 4, nh });
	sprite->SetAnimationDelay((int)PlayerAnim::ATTACKING_GROUND_RIGHT, 0);
	sprite->AddKeyFrame((int)PlayerAnim::ATTACKING_GROUND_RIGHT, { 0,	nw * 2,	nw * 4, nh });
	sprite->AddKeyFrame((int)PlayerAnim::ATTACKING_GROUND_RIGHT, { nw * 4, nw * 2, nw * 4, nh });
	sprite->AddKeyFrame((int)PlayerAnim::ATTACKING_GROUND_RIGHT, { nw * 8, nw * 2, nw * 4, nh });

	sprite->SetAnimationDelay((int)PlayerAnim::ATTACKING_AIR_LEFT, ANIM_DELAY);
	sprite->AddKeyFrame((int)PlayerAnim::ATTACKING_AIR_LEFT, { nw * 4, nw * 4, -nw * 4, nh });
	sprite->AddKeyFrame((int)PlayerAnim::ATTACKING_AIR_LEFT, { nw * 8, nw * 4, -nw * 4, nh });
	sprite->SetAnimationDelay((int)PlayerAnim::ATTACKING_AIR_RIGHT, ANIM_DELAY);
	sprite->AddKeyFrame((int)PlayerAnim::ATTACKING_AIR_RIGHT, { nw * 4, nw * 4, nw * 4, nh });
	sprite->AddKeyFrame((int)PlayerAnim::ATTACKING_AIR_RIGHT, { nw * 8, nw * 4, nw * 4, nh });

	sprite->SetAnimationDelay((int)PlayerAnim::ATTACKING_CROUCH_LEFT, ANIM_DELAY);
	sprite->AddKeyFrame((int)PlayerAnim::ATTACKING_CROUCH_LEFT, { nw * 4, nw * 6, -nw * 4, nh });
	sprite->AddKeyFrame((int)PlayerAnim::ATTACKING_CROUCH_LEFT, { nw * 8, nw * 6, -nw * 4, nh });
	sprite->SetAnimationDelay((int)PlayerAnim::ATTACKING_CROUCH_RIGHT, ANIM_DELAY);
	sprite->AddKeyFrame((int)PlayerAnim::ATTACKING_CROUCH_RIGHT, { nw * 4, nw * 6, nw * 4, nh });
	sprite->AddKeyFrame((int)PlayerAnim::ATTACKING_CROUCH_RIGHT, { nw * 8, nw * 6, nw * 4, nh });

	sprite->SetAnimation((int)PlayerAnim::IDLE_RIGHT);

	return AppStatus::OK;
}
void Player::InitScore()
{
	score = 0;
}
void Player::IncrScore(int n)
{
	score += n;
}
int Player::GetScore()
{
	return score;
}
State Player::GetState()
{
	return state;
}
void Player::SetTileMap(TileMap* tilemap)
{
	map = tilemap;
}
bool Player::IsLookingRight() const
{
	return look == Look::RIGHT;
}
bool Player::IsLookingLeft() const
{
	return look == Look::LEFT;
}
bool Player::IsAscending() const
{
	return dir.y < -PLAYER_LEVITATING_SPEED;
}
bool Player::IsDescending() const
{
	return dir.y > PLAYER_LEVITATING_SPEED;
}
bool Player::IsInFirstHalfTile() const
{
	return pos.y % TILE_SIZE < TILE_SIZE / 2;
}
bool Player::IsInSecondHalfTile() const
{
	return pos.y % TILE_SIZE >= TILE_SIZE / 2;
}
void Player::SetAnimation(int id)
{
	Sprite* sprite = dynamic_cast<Sprite*>(render);
	sprite->SetAnimation(id);
}
PlayerAnim Player::GetAnimation()
{
	Sprite* sprite = dynamic_cast<Sprite*>(render);
	return (PlayerAnim)sprite->GetAnimation();
}
void Player::Stop()
{
	dir = { 0,0 };
	state = State::IDLE;
	if (IsLookingRight())	SetAnimation((int)PlayerAnim::IDLE_RIGHT);
	else					SetAnimation((int)PlayerAnim::IDLE_LEFT);
}
void Player::StartWalkingLeft()
{
	state = State::WALKING;
	look = Look::LEFT;
	SetAnimation((int)PlayerAnim::WALKING_LEFT);
}
void Player::StartWalkingRight()
{
	state = State::WALKING;
	look = Look::RIGHT;
	SetAnimation((int)PlayerAnim::WALKING_RIGHT);
}
void Player::StartFalling()
{
	dir.y = PLAYER_SPEED;
	state = State::FALLING;
	if (IsLookingRight())	SetAnimation((int)PlayerAnim::FALLING_RIGHT);
	else					SetAnimation((int)PlayerAnim::FALLING_LEFT);
}
void Player::StartJumping()
{
	dir.y = -PLAYER_JUMP_FORCE;
	state = State::JUMPING;
	if (IsLookingRight())	SetAnimation((int)PlayerAnim::JUMPING_RIGHT);
	else					SetAnimation((int)PlayerAnim::JUMPING_LEFT);
	jump_delay = PLAYER_JUMP_DELAY;
}
void Player::StartClimbingUp()
{
	state = State::CLIMBING;
	SetAnimation((int)PlayerAnim::CLIMBING);
	Sprite* sprite = dynamic_cast<Sprite*>(render);
	sprite->SetManualMode();
}
void Player::StartClimbingDown()
{
	state = State::CLIMBING;
	SetAnimation((int)PlayerAnim::CLIMBING_TOP);
	Sprite* sprite = dynamic_cast<Sprite*>(render);
	sprite->SetManualMode();
}
void Player::ChangeAnimRight()
{
	look = Look::RIGHT;
	if (state != State::ATTACKING)
	{
		switch (state)
		{
		case State::IDLE:		SetAnimation((int)PlayerAnim::IDLE_RIGHT);    break;
		case State::WALKING:	SetAnimation((int)PlayerAnim::WALKING_RIGHT); break;
		case State::JUMPING:	SetAnimation((int)PlayerAnim::JUMPING_RIGHT); break;
		case State::FALLING:	SetAnimation((int)PlayerAnim::FALLING_RIGHT); break;
		case State::CROUCHING:	SetAnimation((int)PlayerAnim::CROUCHING_RIGHT); break;
		}
	}
}
void Player::ChangeAnimLeft()
{
	look = Look::LEFT;
	if (state != State::ATTACKING)
	{
		switch (state)
		{
		case State::IDLE:		SetAnimation((int)PlayerAnim::IDLE_LEFT);    break;
		case State::WALKING:	SetAnimation((int)PlayerAnim::WALKING_LEFT); break;
		case State::JUMPING:	SetAnimation((int)PlayerAnim::JUMPING_LEFT); break;
		case State::FALLING:	SetAnimation((int)PlayerAnim::FALLING_LEFT); break;
		case State::CROUCHING:	SetAnimation((int)PlayerAnim::CROUCHING_LEFT); break;
		}
	}
}
void Player::Update()
{
	//Player doesn't use the "Entity::Update() { pos += dir; }" default behaviour.
	//Instead, uses an independent behaviour for each axis.

	if (IsKeyPressed(KEY_SPACE))
	{
		if (state == State::JUMPING || state == State::FALLING)
		{
			/*
			if (look == Look::LEFT)		SetAnimation((int)PlayerAnim::ATTACKING_AIR_LEFT);
			else						SetAnimation((int)PlayerAnim::ATTACKING_AIR_RIGHT);
			 THIS FAIL BECAUSE CHANGING THE STATE CHANGE THE GRAVITY OF THE PLAYER
			state = State::ATTACKING;
			Sprite* sprite = dynamic_cast<Sprite*>(render);
			sprite->SetManualMode();
			*/
		}
		else if (state == State::CROUCHING)
		{
			/*
			if (look == Look::LEFT)		SetAnimation((int)PlayerAnim::ATTACKING_AIR_LEFT);
			else						SetAnimation((int)PlayerAnim::ATTACKING_AIR_RIGHT);
			 THIS FAIL BECAUSE THE STATE CROUCHING AND THE STATE ATTACKING CANT BE ACTIVATE
			state = State::ATTACKING;
			Sprite* sprite = dynamic_cast<Sprite*>(render);
			sprite->SetManualMode();
			*/
		}
		else
		{
			if (look == Look::LEFT)		SetAnimation((int)PlayerAnim::ATTACKING_GROUND_LEFT);
			else						SetAnimation((int)PlayerAnim::ATTACKING_GROUND_RIGHT);
			state = State::ATTACKING;
			Sprite* sprite = dynamic_cast<Sprite*>(render);
			sprite->SetManualMode();
		}
	}

	MoveX();
	MoveY();
	if (state == State::ATTACKING)
		Attack();

	if (invincibility > 0) invincibility++;

	if (invincibility >= 120)
		FinishInvincibility();

	Sprite* sprite = dynamic_cast<Sprite*>(render);
	sprite->Update();
}
void Player::MoveX()
{
	AABB box;
	int prev_x = pos.x;

	//We can only go up and down while climbing
	if (state == State::CLIMBING)	return;

	if (IsKeyDown(KEY_LEFT) && !IsKeyDown(KEY_RIGHT))
	{
		if (state != State::CROUCHING && state != State::ATTACKING) pos.x += -PLAYER_SPEED;
		if (state == State::IDLE) StartWalkingLeft();
		else
		{
			if (IsLookingRight()) ChangeAnimLeft();
		}

		box = GetHitbox().first;
		if (map->TestCollisionWallLeft(box) || pos.x <= 0)
		{
			pos.x = prev_x;
			if (state == State::WALKING) Stop();
		}
	}
	else if (IsKeyDown(KEY_RIGHT))
	{
		if (state != State::CROUCHING && state != State::ATTACKING) pos.x += PLAYER_SPEED;
		if (state == State::IDLE) StartWalkingRight();
		else
		{
			if (IsLookingLeft()) ChangeAnimRight();
		}

		box = GetHitbox().first;
		if (map->TestCollisionWallRight(box) || pos.x >= WINDOW_WIDTH - PLAYER_PHYSICAL_WIDTH)
		{
			pos.x = prev_x;
			if (state == State::WALKING) Stop();
		}
	}
	else
	{
		if (state == State::WALKING) Stop();
	}
}
void Player::MoveY()
{
	AABB box;

	if (state == State::JUMPING)
	{
		LogicJumping();
	}
	else if (state == State::CLIMBING)
	{
		LogicClimbing();
	}
	else //idle, walking, falling
	{
		pos.y += PLAYER_SPEED;
		box = GetHitbox().first;

		if (map->TestCollisionGround(box, &pos.y))
		{
			if (state == State::FALLING) Stop();

			if (IsKeyDown(KEY_UP))
			{
				box = GetHitbox().first;
				if (map->TestOnLadder(box, &pos.x))
					StartClimbingUp();
				else
					StartJumping();
			}
			else if (IsKeyDown(KEY_DOWN))
			{
				//To Crouch
				state = State::CROUCHING;
				if (IsLookingLeft()) ChangeAnimLeft();
				else ChangeAnimRight();

				//To climb up the ladder, we need to check the control point (x, y)
				//To climb down the ladder, we need to check pixel below (x, y+1) instead
				box = GetHitbox().first;
				box.pos.y++;
				if (map->TestOnLadderTop(box, &pos.x))
				{
					StartClimbingDown();
					pos.y += PLAYER_LADDER_SPEED;
				}

			}
			else
			{
				//To stop Crouching
				if (state == State::CROUCHING) Stop();
			}
		}
		//To Climb the stairs in the air
		else if (state == State::FALLING)
		{
			if (IsKeyDown(KEY_UP))
			{
				box = GetHitbox().first;
				if (map->TestOnLadder(box, &pos.x))
					StartClimbingUp();
			}
			else if (IsKeyDown(KEY_DOWN))
			{
				//To climb up the ladder, we need to check the control point (x, y)
				//To climb down the ladder, we need to check pixel below (x, y+1) instead
				box = GetHitbox().first;
				box.pos.y++;
				if (map->TestOnLadderTop(box, &pos.x))
				{
					StartClimbingDown();
					pos.y += PLAYER_LADDER_SPEED;
				}

			}
		}
		else
		{
			if (state != State::FALLING) StartFalling();
		}

	}
}
void Player::Attack() {
	Sprite* sprite = dynamic_cast<Sprite*>(render);
	if (attacking == 2)
	{
		sprite->NextFrame();
		attacking++;
	}
	else if (attacking == 4)
	{
		sprite->NextFrame();
		attacking++;
	}
	else if (attacking == 10) {
		Stop();
		sprite->SetAutomaticMode();
		attacking = 0;
		state = State::IDLE;
	}
	else {
		attacking++;
	}
}
void Player::Draw()
{
	Point p = Entity::GetRenderingPosition();
	switch (state)
	{
	case State::ATTACKING:
		if (look == Look::RIGHT)
			render->Draw(p.x - 16, p.y);
		else
			render->Draw(p.x - 32, p.y);
		break;
	default:
		render->Draw(p.x, p.y);
		break;
	}

}
std::pair<AABB, AABB> Player::GetHitbox() const
{
	AABB playerHitbox, whipHitbox;

	if (state == State::ATTACKING)
	{
		Point p(pos.x, pos.y - (height - 1));
		playerHitbox.Set(p, width, height);

		//Whip
		Point whipPoint(pos.x + (IsLookingLeft() ? -(width * 2) - 3 : width), (pos.y - 15));
		whipHitbox.Set(whipPoint, width * 2.3f, height / 3);
	}
	else if (state == State::CROUCHING)
	{
		Point p(pos.x, pos.y - (height - 10));
		playerHitbox.Set(p, width, height - 9);
	}
	else
	{
		Point p(pos.x, pos.y - (height - 1));
		playerHitbox.Set(p, width, height);
	}

	return { playerHitbox, whipHitbox };
}
void Player::DrawDebug(const Color& col) const
{
	AABB hitbox = GetHitbox().first;
	Entity::DrawHitbox(hitbox.pos.x, hitbox.pos.y + hitbox.height, hitbox.width, hitbox.height, col);

	if (state == State::ATTACKING && attacking >= 4)
	{
		AABB hitbox = GetHitbox().second;
		Entity::DrawHitbox(hitbox.pos.x, hitbox.pos.y, hitbox.width, hitbox.height, col);
	}

	DrawText(TextFormat("Position: (%d,%d)\nSize: %dx%d\nFrame: %dx%d", pos.x, pos.y, width, height, frame_width, frame_height), 8 * 16, 0, 8, LIGHTGRAY);
	DrawText(TextFormat("Attack: %d", attacking), 8 * 16, 16 * 4, 8, LIGHTGRAY);

	DrawPixel(pos.x, pos.y, WHITE);
void Player::Damaged(EnemyType enemy)
{
	switch (enemy)
	{
	case EnemyType::KNIGHT:
		life = life - 2;
		break;
	default:
		break;
	}
}
int Player::GetLife()
{
	return life;
}
void Player::StartInvincibility() {
	invincibility = 1;
}
void Player::FinishInvincibility() {
	invincibility = 0;
}
int Player::GetInvincibility()
{
	return invincibility;
}
void Player::LogicJumping()
{
	AABB box, prev_box;
	int prev_y;

	jump_delay--;
	if (jump_delay == 0)
	{
		prev_y = pos.y;
		prev_box = GetHitbox().first;

		pos.y += dir.y;
		dir.y += GRAVITY_FORCE;
		jump_delay = PLAYER_JUMP_DELAY;

		//Is the jump finished?
		if (dir.y > PLAYER_JUMP_FORCE)
		{
			dir.y = PLAYER_SPEED;
			StartFalling();
		}
		else
		{
			//Jumping is represented with 3 different states
			if (IsAscending())
			{
				if (IsLookingRight())	SetAnimation((int)PlayerAnim::JUMPING_RIGHT);
				else					SetAnimation((int)PlayerAnim::JUMPING_LEFT);
			}
			else if (IsDescending())
			{
				if (IsLookingRight())	SetAnimation((int)PlayerAnim::FALLING_RIGHT);
				else					SetAnimation((int)PlayerAnim::FALLING_LEFT);
			}
		}
		//We check ground collision when jumping down
		if (dir.y >= 0)
		{
			box = GetHitbox().first;

			//A ground collision occurs if we were not in a collision state previously.
			//This prevents scenarios where, after levitating due to a previous jump, we found
			//ourselves inside a tile, and the entity would otherwise be placed above the tile,
			//crossing it.
			if (!map->TestCollisionGround(prev_box, &prev_y) &&
				map->TestCollisionGround(box, &pos.y))
			{
				Stop();
			}
		}
	}
}
void Player::LogicClimbing()
{
	AABB box;
	Sprite* sprite = dynamic_cast<Sprite*>(render);
	int tmp;

	if (IsKeyDown(KEY_UP))
	{
		pos.y -= PLAYER_LADDER_SPEED;
		sprite->NextFrame();
	}
	else if (IsKeyDown(KEY_DOWN))
	{
		pos.y += PLAYER_LADDER_SPEED;
		sprite->PrevFrame();
	}
	else if (IsKeyDown(KEY_RIGHT) || IsKeyDown(KEY_LEFT))
	{
		StartFalling();
	}
	else if (IsKeyDown(KEY_SPACE))
	{
		StartJumping();
	}

	//It is important to first check LadderTop due to its condition as a collision ground.
	//By doing so, we ensure that we don't stop climbing down immediately after starting the descent.
	if (state == State::CLIMBING)
	{
		box = GetHitbox().first;
		if (map->TestOnLadderTop(box, &tmp))
		{
			if (IsInSecondHalfTile())		SetAnimation((int)PlayerAnim::CLIMBING_PRE_TOP);
			else if (IsInFirstHalfTile())	SetAnimation((int)PlayerAnim::CLIMBING_TOP);
			else					LOG("Internal error, tile should be a LADDER_TOP, coord: (%d,%d)", box.pos.x, box.pos.y);
		}
		else if (map->TestCollisionGround(box, &pos.y))
		{
			//Case leaving the ladder descending.
			Stop();
			sprite->SetAutomaticMode();
		}
		else if (!map->TestOnLadder(box, &tmp))
		{
			//Case leaving the ladder ascending.
			//If we are not in a LadderTop, colliding ground or in the Ladder it means we are leaving
			//ther ladder ascending.
			Stop();
			sprite->SetAutomaticMode();
		}
		else
		{
			if (GetAnimation() != PlayerAnim::CLIMBING)	SetAnimation((int)PlayerAnim::CLIMBING);
		}
	}
}
=======
void Player::DrawDebug(const Color& col) const
{
	Entity::DrawHitbox(pos.x, pos.y, width, height, col);

	DrawText(TextFormat("Position: (%d,%d)\nSize: %dx%d\nFrame: %dx%d", pos.x, pos.y, width, height, frame_width, frame_height), 8 * 16, 0, 8, LIGHTGRAY);
	DrawText(TextFormat("Attack: %d", attacking), 8 * 16, 16 * 4, 8, LIGHTGRAY);
	DrawText(TextFormat("Inv: %d", invincibility), 8 * 16, 16 * 5, 8, LIGHTGRAY);

	DrawPixel(pos.x, pos.y, WHITE);
}
void Player::Release()
{
	ResourceManager& data = ResourceManager::Instance();
	data.ReleaseTexture(Resource::IMG_PLAYER);

	render->Release();
}
