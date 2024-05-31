#include "Scene.h"
#include <stdio.h>
#include "Globals.h"

Scene::Scene()
{
	player = nullptr;
	level = nullptr;
	levelOver = false;
	playerBar = nullptr;
	bossBar = nullptr;

	camera.target = { 0, 0 };				//Center of the screen
	camera.offset = { 0, MARGIN_GUI_Y };	//Offset from the target (center of the screen)
	camera.rotation = 0.0f;					//No rotation
	camera.zoom = 1.0f;						//Default zoom

	medusaSpawnRate = 120;

	debug = DebugMode::OFF;
	score = 0,
		stage = 0,
		hearts = 0,
		life = 3;
}
Scene::~Scene()
{
	if (player != nullptr)
	{
		player->Release();
		delete player;
		player = nullptr;
	}
	if (level != nullptr)
	{
		level->Release();
		delete level;
		level = nullptr;
	}
}
AppStatus Scene::Init()
{
	seq = new Sequence(GameSequence::GAME_START, { { WINDOW_WIDTH / 2 - 10, 0 }, 3, WINDOW_HEIGHT });
	seq->SetStateSequence(StateSequence::SEQUENCE);

	lvlList = new Levels();
	lvlList->Initialise();

	ResourceManager& rm = ResourceManager::Instance();
	musicStage0 = rm.GetMusic(MusicResource::MUSIC_STAGE0);
	musicStage2 = rm.GetMusic(MusicResource::MUSIC_STAGE2);

	//Create player
	player = new Player({ 0,0 }, State::IDLE, Look::LEFT);
	if (player == nullptr)
	{
		LOG("Failed to allocate memory for Player");
		return AppStatus::ERROR;
	}
	//Initialise player
	if (player->Initialise() != AppStatus::OK)
	{
		LOG("Failed to initialise Player");
		return AppStatus::ERROR;
	}

	//Create level 
	level = new TileMap();
	if (level == nullptr)
	{
		LOG("Failed to allocate memory for Level");
		return AppStatus::ERROR;
	}
	//Initialise level
	if (level->Initialise() != AppStatus::OK)
	{
		LOG("Failed to initialise Level");
		return AppStatus::ERROR;
	}
	//Load level
	if (LoadLevel(1, 101) != AppStatus::OK)
	{
		LOG("Failed to load Level 1");
		return AppStatus::ERROR;
	}
	//Assign the tile map reference to the player to check collisions while navigating
	player->SetTileMap(level);
	player->InitScore();

	//UI
	ui = LoadTexture("Assets/Ui.png");

	//Game Start
	gameStart = LoadTexture("Assets/GameStart.png");

	//False Tile
	falseTile = LoadTexture("Assets/FalseTile.png");

	//Door
	door = LoadTexture("Assets/Door.png");

	Point pos = Point(61, -18);
	playerBar = new Bar(16, { 255, 192, 150, 255 }, pos, 64, 4);
	pos = Point(61, -9);
	bossBar = new Bar(16, { 251, 31, 46, 255 }, pos, 64, 4);

	//Init Enemies
	enemies = std::vector<Enemy*>(5);
	for (size_t i = 0; i < enemies.size(); i++)
		enemies[i] = new Enemy(16, 16);

	player->MoveAuto(true);
	player->BlockMovement(true);

	return AppStatus::OK;
}
AppStatus Scene::LoadLevel(int stage, int direction)
{
	int size;
	int x, y, i;
	Tile tile;
	Point pos;
	Object* obj;
	Fire* ent;

	while (!objects.empty())
		objects.pop_back();

	while (!fires.empty())
		fires.pop_back();

	for (size_t i = 0; i < enemies.size(); i++)
	{
		enemies[i]->Die();
	}

	lvlList->SetLvl(stage);

	size = LEVEL_WIDTH * LEVEL_HEIGHT;
	//Get map of the stage
	std::vector<int> map = lvlList->getMap();

	//Get entities of the stage
	std::vector<int> mapEnt = lvlList->getEnt();
	int mapTmp[176], entities[176];

	for (size_t i = 0; i < map.size(); i++)
		mapTmp[i] = map[i];

	for (size_t i = 0; i < map.size(); i++)
		entities[i] = mapEnt[i];

	i = 0;
	for (y = 0; y < LEVEL_HEIGHT; ++y)
	{
		for (x = 0; x < LEVEL_WIDTH; ++x)
		{

			pos.x = x * TILE_SIZE;
			pos.y = y * TILE_SIZE + TILE_SIZE - 1;
			tile = (Tile)entities[i];
			if ((direction == 100 && tile == Tile::PLAYERUP) ||
				(direction == 101 && tile == Tile::PLAYERRIGHT) ||
				(direction == 102 && tile == Tile::PLAYERDOWN) ||
				(direction == 103 && tile == Tile::PLAYERLEFT))
			{
				player->SetPos(pos);
			}
			else if (tile == Tile::ITEM_FIRE_HEART || tile == Tile::ITEM_FIRE_HEART_BIG || tile == Tile::ITEM_FIRE_WHIPE || tile == Tile::ITEM_CANDLE_HEART)
			{
				if (tile == Tile::ITEM_FIRE_HEART)
					ent = new Fire(pos, 16, 16, i, ObjectType::HEART, FireType::FIRE);
				else if (tile == Tile::ITEM_FIRE_HEART_BIG)
					ent = new Fire(pos, 16, 16, i, ObjectType::HEART_BIG, FireType::FIRE);
				else if (tile == Tile::ITEM_FIRE_WHIPE)
					ent = new Fire(pos, 16, 16, i, ObjectType::WHIPE, FireType::FIRE);
				else
					ent = new Fire(pos, 16, 16, i, ObjectType::HEART, FireType::CANDLE);
				ent->Initialise();
				fires.push_back(ent);
			}
			else if (tile == Tile::ENEMY_KNIGHT)
			{
				for (size_t i = 0; i < enemies.size(); i++)
				{
					if (!enemies[i]->IsAlive())
					{
						enemies[i]->Initialise(pos, EnemyType::KNIGHT, EnemyState::WALKING, EnemyLook::LEFT, level, 16, 32);
						break;
					}
				}
			}
			else if (tile == Tile::ENEMY_MEDUSA_HEAD_LEFT || tile == Tile::ENEMY_MEDUSA_HEAD_RIGHT)
			{
				for (size_t i = 0; i < enemies.size(); i++)
				{
					if (!enemies[i]->IsAlive())
					{
						if (tile == Tile::ENEMY_MEDUSA_HEAD_LEFT)
							enemies[i]->Initialise(pos, EnemyType::MEDUSA_HEAD, EnemyState::WALKING, EnemyLook::LEFT, level, 16, 16);
						else
							enemies[i]->Initialise(pos, EnemyType::MEDUSA_HEAD, EnemyState::WALKING, EnemyLook::RIGHT, level, 16, 16);
						break;
					}
				}
			}
			else if (tile == Tile::ENEMY_BAT)
			{
				for (size_t i = 0; i < enemies.size(); i++)
				{
					if (!enemies[i]->IsAlive())
					{
						enemies[i]->Initialise(pos, EnemyType::BAT, EnemyState::IDLE, EnemyLook::RIGHT, level, 16, 16);
						break;
					}
				}
			}
			++i;
		}
	}

	PlayMusicStream(musicStage0);

	//Tile map
	posTp posTp = lvlList->getTp();
	level->Load(mapTmp, LEVEL_WIDTH, LEVEL_HEIGHT, posTp.top, posTp.right, posTp.down, posTp.left);

	return AppStatus::OK;
}
void Scene::Update()
{
	Point p1, p2;
	AABB box;

	UpdateMusicStream(musicStage0);
	UpdateMusicStream(musicStage2);

	//Change level if player gets off the screen
	LoadNextLevel();

	//Switch between the different debug modes: off, on (sprites & hitboxes), on (hitboxes) 
	if (IsKeyPressed(KEY_F1))
	{
		debug = (DebugMode)(((int)debug + 1) % (int)DebugMode::SIZE);
	}

	//Debug
	if (IsKeyPressed(KEY_F2))
	{
		levelOver = true;
	}

	level->Update();
	player->Update();

	for (size_t i = 0; i < objects.size(); i++)
	{
		objects[i]->Update();
	}

	for (size_t i = 0; i < fires.size(); i++)
	{
		fires[i]->Update();
	}

	for (size_t i = 0; i < enemies.size(); i++)
	{
		if (enemies[i]->IsAlive() && enemies[i]->getType() == EnemyType::MEDUSA_HEAD)
		{
			medusaSpawnRate--;
			break;
		}
	}

	int middle = (WINDOW_HEIGHT - TP_TILE - MARGIN_GUI_Y) / 2;
	for (size_t i = 0; i < enemies.size(); i++)
	{
		if (enemies[i]->IsAlive() && (enemies[i]->getType() == EnemyType::KNIGHT || enemies[i]->getType() == EnemyType::BAT))
			enemies[i]->Update();

		if (medusaSpawnRate == 0 && enemies[i]->IsAlive() && enemies[i]->getType() == EnemyType::MEDUSA_HEAD && !enemies[i]->IsMedusaSpawn())
		{
			if ((enemies[i]->GetPos().y >= middle && player->GetPos().y >= middle) || (enemies[i]->GetPos().y <= middle && player->GetPos().y <= middle))
				enemies[i]->MedusaSpawn(true);
			medusaSpawnRate = 120;
		}
		if (enemies[i]->IsAlive() && enemies[i]->getType() == EnemyType::MEDUSA_HEAD && enemies[i]->IsMedusaSpawn())
			enemies[i]->Update();

		if (enemies[i]->GetPos().x <= -16 || enemies[i]->GetPos().x >= WINDOW_WIDTH)
		{
			if (enemies[i]->getType() == EnemyType::MEDUSA_HEAD)
				enemies[i]->MedusaSpawn(false);
			else
				enemies[i]->Die();
		}

	}

	//Debug Level
	if (debug == DebugMode::SPRITES_AND_HITBOXES || debug == DebugMode::ONLY_HITBOXES)
	{
		for (int i = KEY_ONE; i <= KEY_NINE; i++) {
			if (IsKeyDown(i)) {
				LoadLevel(i - KEY_ZERO, 103);
			}
		}
	}

	seq->Update();

	if (seq->GetCont() == 0)
	{
		//Sequence for Game Start
		if (seq->GetGameSequence() == GameSequence::GAME_START)
		{
			LoadLevel(2, 103);
			seq->SetStateSequence(StateSequence::IDLE);
			seq->SetSequence(GameSequence::CASTLE_ENTRY, { {221, 0}, 3, WINDOW_HEIGHT }, 60);
			player->BlockMovement(false);
			player->LookAhead(false);
		}
		//Sequence for Castle Entry
		else if (seq->GetGameSequence() == GameSequence::CASTLE_ENTRY)
		{
			LoadLevel(5, 103);
			seq->SetStateSequence(StateSequence::IDLE);
			seq->SetSequence(GameSequence::BOSS_DOOR_OPEN, { {29, 16}, 3, 48 }, 240);
			seq->SetY(16);
			falseTile = LoadTexture("Assets/FalseWall.png");	//Change the texture for the wall
			player->BlockMovement(false);
			player->MoveAuto(false);
			player->LookAhead(false);
		}
		//Sequence for Boss Door
		else if (seq->GetGameSequence() == GameSequence::BOSS_DOOR_OPEN)
		{
			LoadLevel(11, 101);
			seq->SetStateSequence(StateSequence::IDLE);
			seq->SetSequence(GameSequence::BOSS_DOOR_OPEN, { {0, 0}, 0, 0 }, 10);
			player->BlockMovement(false);
			player->MoveAuto(false);
			player->LookAhead(false);
		}
	}

	if (seq->GetCont() == 120 && seq->GetGameSequence() == GameSequence::BOSS_DOOR_OPEN)
	{
		player->MoveAuto(true);
		player->ChangeLook(Look::LEFT);
	}

	CheckCollisions();


}
void Scene::LoadNextLevel() {
	if (player->GetPos().x + PLAYER_FRAME_SIZE_WIDTH >= WINDOW_WIDTH - TP_TILE)
	{
		int lvl = level->GetTpMap(2);
		if (lvl != 0)	LoadLevel(lvl, 103);
	}
	else if (player->GetPos().x <= 0 + TP_TILE)
	{
		int lvl = level->GetTpMap(4);
		if (lvl != 0)	LoadLevel(lvl, 101);
	}
	else if (player->GetPos().y >= WINDOW_HEIGHT - TP_TILE - MARGIN_GUI_Y)
	{
		int lvl = level->GetTpMap(3);
		if (lvl != 0)	LoadLevel(lvl, 100);
	}
	else if (player->GetPos().y <= 0 + TP_TILE)
	{
		int lvl = level->GetTpMap(1);
		if (lvl != 0)	LoadLevel(lvl, 102);
	}
}
void Scene::Render()
{
	BeginMode2D(camera);



	level->Render();

	//Draw Castle
	if (lvlList->GetLvl() == 1)
		DrawTexture(gameStart, 0, -35, WHITE);

	if (debug == DebugMode::OFF || debug == DebugMode::SPRITES_AND_HITBOXES)
		for (size_t i = 0; i < enemies.size(); i++)
		{
			if (enemies[i]->IsAlive() && (enemies[i]->getType() == EnemyType::KNIGHT || enemies[i]->getType() == EnemyType::BAT || (enemies[i]->getType() == EnemyType::MEDUSA_HEAD && enemies[i]->IsMedusaSpawn())))
				enemies[i]->Draw();
		}
	if (debug == DebugMode::SPRITES_AND_HITBOXES || debug == DebugMode::ONLY_HITBOXES)
		for (size_t i = 0; i < enemies.size(); i++)
		{
			if (enemies[i]->IsAlive() && (enemies[i]->getType() == EnemyType::KNIGHT || enemies[i]->getType() == EnemyType::BAT || (enemies[i]->getType() == EnemyType::MEDUSA_HEAD && enemies[i]->IsMedusaSpawn())))
				enemies[i]->DrawDebug(GREEN);
		}

	//Objects
	if (debug == DebugMode::OFF || debug == DebugMode::SPRITES_AND_HITBOXES)
		for (size_t i = 0; i < objects.size(); i++)
		{
			objects[i]->Draw();
		}
	if (debug == DebugMode::SPRITES_AND_HITBOXES || debug == DebugMode::ONLY_HITBOXES)
		for (size_t i = 0; i < objects.size(); i++)
		{
			objects[i]->DrawDebug(GREEN);
		}

	//Fires
	if (debug == DebugMode::OFF || debug == DebugMode::SPRITES_AND_HITBOXES)
		for (size_t i = 0; i < fires.size(); i++)
		{
			fires[i]->Draw();
		}
	if (debug == DebugMode::SPRITES_AND_HITBOXES || debug == DebugMode::ONLY_HITBOXES)
		for (size_t i = 0; i < fires.size(); i++)
		{
			fires[i]->DrawDebug(GREEN);
		}

	if (debug == DebugMode::SPRITES_AND_HITBOXES || debug == DebugMode::ONLY_HITBOXES)
	{
		DrawLine(TP_TILE, 0, TP_TILE, WINDOW_HEIGHT, RED);
		DrawLine(WINDOW_WIDTH - TP_TILE, 0, WINDOW_WIDTH - TP_TILE, WINDOW_HEIGHT, RED);
		DrawLine(0, TP_TILE, WINDOW_WIDTH, TP_TILE, RED);
		DrawLine(0, WINDOW_HEIGHT - TP_TILE - MARGIN_GUI_Y, WINDOW_WIDTH, WINDOW_HEIGHT - TP_TILE - MARGIN_GUI_Y, RED);
		DrawRectangle(seq->GetHitBox().pos.x, seq->GetHitBox().pos.y, seq->GetHitBox().width, seq->GetHitBox().height, YELLOW);
	}

	//Player
	if (debug == DebugMode::OFF || debug == DebugMode::SPRITES_AND_HITBOXES)
		player->Draw();
	if (debug == DebugMode::SPRITES_AND_HITBOXES || debug == DebugMode::ONLY_HITBOXES)
		player->DrawDebug(GREEN);

	if (debug == DebugMode::SPRITES_AND_HITBOXES || debug == DebugMode::ONLY_HITBOXES)
	{
		DrawText(TextFormat("Go to a level (1-9)"), 16 * 9, 16 * 1, 1, LIGHTGRAY);
		DrawText(TextFormat("Spawn a Item (I)"), 16 * 9, 16 * 2, 1, LIGHTGRAY);
		DrawText(TextFormat("Spawn a Enemy (E)"), 16 * 9, 16 * 3, 1, LIGHTGRAY);
	}

	if (lvlList->GetLvl() == 8)
		DrawTexture(door, 14, seq->GetY(), WHITE);

	//False Tile
	if (lvlList->GetLvl() == 4)
		DrawTexture(falseTile, 224, 112, WHITE);
	else if (lvlList->GetLvl() == 8)
		DrawTexture(falseTile, 0, -5, WHITE);

	RenderGUI();

	EndMode2D();

}
void Scene::Release()
{
	level->Release();
	player->Release();
	for (size_t i = 0; i < enemies.size(); i++)
		enemies[i]->Release();
	for (size_t i = 0; i < fires.size(); i++)
		fires[i]->Release();
	for (size_t i = 0; i < objects.size(); i++)
		objects[i]->Release();

}
void Scene::CheckCollisions()
{
	AABB player_box, obj_box, whip_hitbox;

	player_box = player->GetHitbox().first;
	whip_hitbox = player->GetHitbox().second;

	//Collision Item
	auto itObj = objects.begin();
	while (itObj != objects.end())
	{
		obj_box = (*itObj)->GetHitbox();
		if (player_box.TestAABB(obj_box) && (*itObj)->GetHeartState() == ItemAnim::IDLE)
		{
			player->IncrScore((*itObj)->Points());
			//Delete the object
			delete* itObj;
			//Erase the object from the vector and get the iterator to the next valid element
			itObj = objects.erase(itObj);
		}
		else
		{
			//Move to the next object
			++itObj;
		}
	}

	//Collision Fire
	auto itFi = fires.begin();
	while (itFi != fires.end())
	{
		obj_box = (*itFi)->GetHitbox();
		if (whip_hitbox.TestAABB(obj_box) && player->GetAttackState() == AttackState::ATTACKING)
		{
			//Change the array for not creating more fires in this position
			lvlList->SetEnt((*itFi)->GetPosArray());

			//Create a heart in the position of the fire
			objects.push_back(new Object({ (*itFi)->GetPos().x, (*itFi)->GetPos().y }, (*itFi)->GetItemType(), level));
			//Delete the object
			delete* itFi;
			//Erase the object from the vector and get the iterator to the next valid element
			itFi = fires.erase(itFi);

		}
		else
		{
			//Move to the next object
			++itFi;
		}
	}

	//Collision Enemy
	for (size_t i = 0; i < enemies.size(); i++)
	{
		if (enemies[i]->IsAlive())
		{
			obj_box = enemies[i]->GetHitbox();
			//Collision Player with Enemy
			if (player_box.TestAABB(obj_box) && player->GetInvincibility() == 0)
			{
				EnemyType et = enemies[i]->getType();
				player->Damaged(et);
				playerBar->changeBar(player->GetLife());
				player->StartInvincibility();
			}
			//Collision Whip with Enemy
			else if (whip_hitbox.TestAABB(obj_box) && enemies[i]->GetInvincibility() == 0)
			{
				enemies[i]->Damaged(player->GetDmg());
				enemies[i]->StartInvincibility();
				if (enemies[i]->getLife() <= 0)
				{
					if (enemies[i]->getType() == EnemyType::KNIGHT || enemies[i]->getType() == EnemyType::BAT)
						enemies[i]->Die();
					else
						enemies[i]->MedusaSpawn(false);
				}
			}

			if (player_box.TestAABB(enemies[i]->GetAttackRadius()) && enemies[i]->GetState() == EnemyState::IDLE)
				enemies[i]->SetState(EnemyState::WALKING);
		}
	}

	//Game Start Sequence
	if (seq->GetGameSequence() == GameSequence::GAME_START && seq->GetStateSequence() == StateSequence::SEQUENCE && player_box.TestAABB(seq->GetHitBox()))
	{
		player->MoveAuto(false);
		player->LookAhead(true);
		seq->StartWaiting();
	}

	//Castle Entry Sequence
	if (lvlList->GetLvl() == 4 && seq->GetGameSequence() == GameSequence::CASTLE_ENTRY && player_box.TestAABB(seq->GetHitBox()))
	{
		seq->SetStateSequence(StateSequence::SEQUENCE);
		player->BlockMovement(true);
		player->Stop();

		if (player->GetPos().y == 143)
		{
			player->MoveAuto(true);
			seq->StartWaiting();
		}
	}

	//Boss Door
	if (lvlList->GetLvl() == 8 && seq->GetGameSequence() == GameSequence::BOSS_DOOR_OPEN && player_box.TestAABB(seq->GetHitBox()))
	{
		seq->SetStateSequence(StateSequence::SEQUENCE);
		player->BlockMovement(true);
		player->Stop();
		player->ChangeLook(Look::LEFT);

		if (player->GetPos().y == 63)
		{
			seq->StartWaiting();
		}
	}
}
void Scene::RenderObjects() const
{
	for (Object* obj : objects)
	{
		obj->Draw();
	}
}
void Scene::RenderObjectsDebug(const Color& col) const
{
	for (Object* obj : objects)
	{
		obj->DrawDebug(col);
	}
}
void Scene::RenderGUI() const
{
	//Temporal approach
	DrawTexture(ui, 0, -35, WHITE);
	playerBar->Draw();
	bossBar->Draw();
	DrawText(TextFormat("%06d", score), 58, -32, 10, WHITE);
	DrawText(TextFormat("%02d",  stage), 157, -32, 10, WHITE);
	DrawText(TextFormat("%02d",  hearts), 193, -32, 10, WHITE);
	DrawText(TextFormat("%02d",  life), 229, -32, 10, WHITE);
}
bool Scene::getLevelOver() const {
	return levelOver;
}