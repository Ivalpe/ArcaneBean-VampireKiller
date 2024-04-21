#include "Scene.h"
#include <stdio.h>
#include "Globals.h"

Scene::Scene()
{
	player = nullptr;
	level = nullptr;
	levelOver = false;

	camera.target = { 0, 0 };				//Center of the screen
	camera.offset = { 0, MARGIN_GUI_Y };	//Offset from the target (center of the screen)
	camera.rotation = 0.0f;					//No rotation
	camera.zoom = 1.0f;						//Default zoom

	debug = DebugMode::OFF;
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
	//Create player
	player = new Player({ 0,0 }, State::IDLE, Look::RIGHT);
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
	if (LoadLevel(1, 103) != AppStatus::OK)
	{
		LOG("Failed to load Level 1");
		return AppStatus::ERROR;
	}
	//Assign the tile map reference to the player to check collisions while navigating
	player->SetTileMap(level);

	player->InitScore();

	return AppStatus::OK;
}
AppStatus Scene::LoadLevel(int stage, int direction)
{
	int size;
	int x, y, i;
	Tile tile;
	Point pos;
	int* map = nullptr;
	Object* obj;

	if (stage == 1)
	{
		size = LEVEL_WIDTH * LEVEL_HEIGHT;
		int map[] = {
				 1, 2, 3, 4, 1, 2, 3, 4, 1, 2, 3, 4, 1, 2, 3, 4
				,9, 10,11,12,9 ,10,11,12,9 ,10,11,12,9 ,10,11,12
				,17,18,19,20,17,18,19,20,17,18,19,20,17,18,19,20
				,23,24,25,26,23,24,25,26,23,24,25,26,23,24,25,26
				,27,28,29,30,27,28,29,30,27,28,29,30,27,28,29,30
				,31,32,33,34,5 ,6 ,21,22,31,6 ,31,7 ,8 ,6 ,31,7
				,35,36,40,41,13,14,35,14,35,14,35,34,16,14,35,14
				,46,47,42,43,47,47,48,47,48,47,48,47,47,47,46,47
				,49,49,44,45,50,49,49,49,49,49,49,49,50,49,49,49
				,60,60,60,60,60,60,60,60,60,60,60,60,60,60,60,60
				,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0
		};

		int entities[] = {
				0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0,
				0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0,
				0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0,
				0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0,
				0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0,
				0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0,
				0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0,
				0 ,0 ,0 ,0 ,140 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,140 ,0 ,0 ,0,
				0 ,103,0,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,101 ,0,
				0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0,
				0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0
		};
		i = 0;
		for (y = 0; y < LEVEL_HEIGHT; ++y)
		{
			for (x = 0; x < LEVEL_WIDTH; ++x)
			{
				tile = (Tile)entities[i];
				if ((direction == 100 && tile == Tile::PLAYERUP) ||
					(direction == 101 && tile == Tile::PLAYERRIGHT) ||
					(direction == 102 && tile == Tile::PLAYERDOWN) ||
					(direction == 103 && tile == Tile::PLAYERLEFT))
				{
					pos.x = x * TILE_SIZE;
					pos.y = y * TILE_SIZE + TILE_SIZE - 1;
					player->SetPos(pos);
				}
				else if (tile == Tile::ITEM_BIG_HEART)
				{
					pos.x = x * TILE_SIZE;
					pos.y = y * TILE_SIZE + TILE_SIZE - 1;
					obj = new Object(pos, ObjectType::BIG_HEART);
					objects.push_back(obj);
					entities[i] = 0;
				}
				else if (tile == Tile::ITEM_SMALL_HEART)
				{
					pos.x = x * TILE_SIZE;
					pos.y = y * TILE_SIZE + TILE_SIZE - 1;
					obj = new Object(pos, ObjectType::SMALL_HEART);
					objects.push_back(obj);
					entities[i] = 0;
				}
				++i;
			}
		}

		//Tile map
		level->Load(map, LEVEL_WIDTH, LEVEL_HEIGHT, 0, 2, 0, 0);
	}
	else if (stage == 2) {
		size = LEVEL_WIDTH * LEVEL_HEIGHT;
		int map[] = {
				 1, 2, 3, 4, 1, 2, 3, 4, 1, 2, 3, 4, 1, 2, 3, 4
				,9, 10,11,12,9 ,10,11,12,9 ,10,11,12,9 ,10,11,12
				,17,18,19,20,17,18,19,20,17,18,19,20,17,18,19,20
				,23,24,25,26,23,24,25,26,23,24,25,26,23,24,25,26
				,27,28,29,30,27,28,29,30,27,28,29,30,27,28,29,30
				,31,32,33,34,5 ,6 ,21,22,31,6 ,31,7 ,8 ,6 ,31,7
				,35,36,40,41,13,14,35,14,35,14,35,34,16,14,35,14
				,46,47,42,43,47,47,48,47,48,47,48,47,47,47,46,47
				,49,49,44,45,50,49,49,49,49,49,49,49,50,49,49,49
				,60,60,60,60,60,60,60,60,60,60,60,60,60,60,60,60
				,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0
		};

		int entities[] = {
				0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0,
				0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0,
				0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0,
				0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0,
				0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0,
				0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0,
				0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0,
				0 ,0 ,0 ,0 ,140 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,140 ,0 ,0 ,0,
				0 ,103,0,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,101 ,0,
				0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0,
				0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0
		};
		//Entities
		i = 0;
		for (y = 0; y < LEVEL_HEIGHT; ++y)
		{
			for (x = 0; x < LEVEL_WIDTH; ++x)
			{
				tile = (Tile)entities[i];
				if ((direction == 100 && tile == Tile::PLAYERUP) ||
					(direction == 101 && tile == Tile::PLAYERRIGHT) ||
					(direction == 102 && tile == Tile::PLAYERDOWN) ||
					(direction == 103 && tile == Tile::PLAYERLEFT))
				{
					pos.x = x * TILE_SIZE;
					pos.y = y * TILE_SIZE + TILE_SIZE - 1;
					player->SetPos(pos);
				}
				else if (tile == Tile::ITEM_BIG_HEART)
				{
					pos.x = x * TILE_SIZE;
					pos.y = y * TILE_SIZE + TILE_SIZE - 1;
					obj = new Object(pos, ObjectType::BIG_HEART);
					objects.push_back(obj);
					entities[i] = 0;
				}
				else if (tile == Tile::ITEM_SMALL_HEART)
				{
					pos.x = x * TILE_SIZE;
					pos.y = y * TILE_SIZE + TILE_SIZE - 1;
					obj = new Object(pos, ObjectType::SMALL_HEART);
					objects.push_back(obj);
					entities[i] = 0;
				}
				++i;
			}
		}
		//Tile map
		level->Load(map, LEVEL_WIDTH, LEVEL_HEIGHT, 0, 3, 0, 1);

	}
	else if (stage == 3) {
		size = LEVEL_WIDTH * LEVEL_HEIGHT;
		int map[] = {
				1 ,2 ,3 ,4 ,1 ,2 ,3 ,4 ,1 ,2 ,70,71,72,71,72,71,
				9 ,10,11,12,9 ,10,11,12,9 ,10,73,74,75,75,75,77,
				17,18,19,20,17,18,19,20,17,18,78,79,80,81,76,82,
				23,24,25,26,23,24,25,26,23,24,73,83,85,86,87,77,
				27,28,29,30,27,28,29,30,27,28,78,88,89,86,87,90,
				31,32,33,34,5 ,6 ,21,22,31,6 ,73,83,85,86,87,91,
				35,36,40,41,13,14,35,14,35,14,78,88,89,86,87,90,
				46,47,42,43,47,47,48,47,48,47,92,93,94,86,96,97,
				49,49,44,45,50,49,49,49,49,49,92,95,94,86,96,98,
				60,60,60,60,60,60,60,60,60,60,60,60,60,60,60,60,
				0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
		};

		int entities[] = {
				0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0,
				0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0,
				0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0,
				0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0,
				0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0,
				0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0,
				0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0,
				0 ,0 ,0 ,0 ,140 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0,
				0 ,103,0,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0,
				0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0,
				0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0
		};
		//Entities
		i = 0;
		for (y = 0; y < LEVEL_HEIGHT; ++y)
		{
			for (x = 0; x < LEVEL_WIDTH; ++x)
			{
				tile = (Tile)entities[i];
				if ((direction == 100 && tile == Tile::PLAYERUP) ||
					(direction == 101 && tile == Tile::PLAYERRIGHT) ||
					(direction == 102 && tile == Tile::PLAYERDOWN) ||
					(direction == 103 && tile == Tile::PLAYERLEFT))
				{
					pos.x = x * TILE_SIZE;
					pos.y = y * TILE_SIZE + TILE_SIZE - 1;
					player->SetPos(pos);
				}
				else if (tile == Tile::ITEM_BIG_HEART)
				{
					pos.x = x * TILE_SIZE;
					pos.y = y * TILE_SIZE + TILE_SIZE - 1;
					obj = new Object(pos, ObjectType::BIG_HEART);
					objects.push_back(obj);
					entities[i] = 0;
				}
				else if (tile == Tile::ITEM_SMALL_HEART)
				{
					pos.x = x * TILE_SIZE;
					pos.y = y * TILE_SIZE + TILE_SIZE - 1;
					obj = new Object(pos, ObjectType::SMALL_HEART);
					objects.push_back(obj);
					entities[i] = 0;
				}
				++i;
			}

		}
		//Tile map
		level->Load(map, LEVEL_WIDTH, LEVEL_HEIGHT, 0, 0, 0, 2);

	}
	else
	{
		//Error level doesn't exist or incorrect level number
		LOG("Failed to load level, stage %d doesn't exist", stage);
		return AppStatus::ERROR;
	}
	return AppStatus::OK;
}
void Scene::Update()
{
	Point p1, p2;
	AABB box;

	//Change level if player gets off the screen
	LoadNextLevel();

	//Switch between the different debug modes: off, on (sprites & hitboxes), on (hitboxes) 
	if (IsKeyPressed(KEY_F1))
	{
		debug = (DebugMode)(((int)debug + 1) % (int)DebugMode::SIZE);
	}

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
	CheckCollisions();
}
void Scene::LoadNextLevel() {
	if (player->GetPos().x >= WINDOW_WIDTH - TILE_SIZE)
	{
		int lvl = level->GetTpMap(2);
		if (lvl != 0)	LoadLevel(lvl, 103);
	}
	else if (player->GetPos().x <= 0 + TILE_SIZE)
	{
		int lvl = level->GetTpMap(4);
		if (lvl != 0)	LoadLevel(lvl, 101);
	}
	else if (player->GetPos().y >= WINDOW_HEIGHT + TILE_SIZE)
	{
		int lvl = level->GetTpMap(1);
		if (lvl != 0)	LoadLevel(lvl, 102);
	}
	else if (player->GetPos().y <= 0 + TILE_SIZE)
	{
		int lvl = level->GetTpMap(3);
		if (lvl != 0)	LoadLevel(lvl, 100);
	}
}
void Scene::Render()
{
	BeginMode2D(camera);

	level->Render();

	if (debug == DebugMode::OFF || debug == DebugMode::SPRITES_AND_HITBOXES)
		player->Draw();
	if (debug == DebugMode::SPRITES_AND_HITBOXES || debug == DebugMode::ONLY_HITBOXES)
		player->DrawDebug(GREEN);

	for (size_t i = 0; i < objects.size(); i++)
	{
		objects[i]->Draw();
	}

	EndMode2D();

	RenderGUI();
}
void Scene::Release()
{
	level->Release();
	player->Release();
}
void Scene::CheckCollisions()
{
	AABB player_box, obj_box;

	player_box = player->GetHitbox();
	auto it = objects.begin();
	while (it != objects.end())
	{
		obj_box = (*it)->GetHitbox();
		if (player_box.TestAABB(obj_box))
		{
			player->IncrScore((*it)->Points());

			//Delete the object
			delete* it;
			//Erase the object from the vector and get the iterator to the next valid element
			it = objects.erase(it);
		}
		else
		{
			//Move to the next object
			++it;
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
	DrawText(TextFormat("SCORE : %d", player->GetScore()), 10, 10, 8, WHITE);
}
bool Scene::getLevelOver() {
	return levelOver;
}