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

	lvlList = new Levels();
	lvlList->Initialise();

	ResourceManager& rm = ResourceManager::Instance();
	musicStage0 = rm.GetMusic(MusicResource::MUSIC_STAGE0);

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
	Object* obj;
	Fire* ent;

	//Delete all objects
	for (size_t i = 0; i < objects.size(); i++)
	{
		objects.pop_back();
	}

	//Delete all fires
	for (size_t i = 0; i < fires.size(); i++)
	{
		fires.pop_back();
	}

	lvlList->setLvl(stage);

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
			}
			else if (tile == Tile::ITEM_SMALL_HEART)
			{
				pos.x = x * TILE_SIZE;
				pos.y = y * TILE_SIZE + TILE_SIZE - 1;
				obj = new Object(pos, ObjectType::SMALL_HEART);
				objects.push_back(obj);
			}
			else if (tile == Tile::ITEM_FIRE)
			{
				pos.x = x * TILE_SIZE;
				pos.y = y * TILE_SIZE + TILE_SIZE - 1;
				ent = new Fire(pos, 16, 16, i);
				ent->Initialise();
				fires.push_back(ent);
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

	for (size_t i = 0; i < fires.size(); i++)
	{
		fires[i]->Update();
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

	for (size_t i = 0; i < objects.size(); i++)
	{
		objects[i]->Draw();
	}

	for (size_t i = 0; i < fires.size(); i++)
	{
		fires[i]->Draw();
	}

	if (debug == DebugMode::OFF || debug == DebugMode::SPRITES_AND_HITBOXES)
		player->Draw();
	if (debug == DebugMode::SPRITES_AND_HITBOXES || debug == DebugMode::ONLY_HITBOXES)
		player->DrawDebug(GREEN);

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
	auto itObj = objects.begin();
	while (itObj != objects.end())
	{
		obj_box = (*itObj)->GetHitbox();
		if (player_box.TestAABB(obj_box))
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
	auto itFi = fires.begin();
	while (itFi != fires.end())
	{
		obj_box = (*itFi)->GetHitbox();
		if (player_box.TestAABB(obj_box) && player->GetState() == State::ATTACKING)
		{

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