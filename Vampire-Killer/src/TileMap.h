
#pragma once
#include <raylib.h>
#include "Sprite.h"
#include "Point.h"
#include "AABB.h"
#include "Globals.h"
#include <unordered_map>

enum class Tile {

	//  0: empty tile
	// -1: area covered by entity
	AIR = 0,

	// 0 < id < 50: trees
	BLOCK_TREE1 = 1, BLOCK_TREE2, BLOCK_TREE3, BLOCK_TREE4, BLOCK_TREE5, BLOCK_TREE6, BLOCK_TREE7, BLOCK_TREE8,
	BLOCK_TREE9, BLOCK_TREE10, BLOCK_TREE11, BLOCK_TREE12, BLOCK_TREE13, BLOCK_TREE14, BLOCK_TREE15, BLOCK_TREE16,
	BLOCK_TREE17, BLOCK_TREE18, BLOCK_TREE19, BLOCK_TREE20, BLOCK_TREE21, BLOCK_TREE22, BLOCK_TREE23, BLOCK_TREE24,
	BLOCK_TREE25, BLOCK_TREE26, BLOCK_TREE27, BLOCK_TREE28, BLOCK_TREE29, BLOCK_TREE30, BLOCK_TREE31, BLOCK_TREE32,
	BLOCK_TREE33, BLOCK_TREE34, BLOCK_TREE35, BLOCK_TREE36,

	//id >= 40: fence
	BLOCK_STATUE1 = 40, BLOCK_STATUE2, BLOCK_STATUE3, BLOCK_STATUE4, BLOCK_STATUE5, BLOCK_STATUE6, BLOCK_FENCE1,
	BLOCK_FENCE2, BLOCK_FENCE3, BLOCK_FENCE4, BLOCK_FENCE5,

	//id >= 60: ground
	BLOCK_GROUND = 60,

	//id >= 70: castle
	CASTLE1 = 70, CASTLE2, CASTLE3, CASTLE4, CASTLE5, CASTLE6, CASTLE7, CASTLE8, CASTLE9, CASTLE10, CASTLE11, CASTLE12, CASTLE13, CASTLE14, CASTLE15,
	CASTLE16, CASTLE17, CASTLE18, CASTLE19, CASTLE20, CASTLE21, CASTLE22, CASTLE23, CASTLE24, CASTLE25, CASTLE26, CASTLE27, CASTLE28, CASTLE29,

	LADDER_L = 120, LADDER_R, LADDER_TOP_L, LADDER_TOP_R,

	// id >= 100: entities' initial locations
	PLAYERUP = 100, PLAYERRIGHT, PLAYERDOWN, PLAYERLEFT,

	STATIC_FIRST = BLOCK_GROUND,
	STATIC_LAST = BLOCK_GROUND,
	SOLID_FIRST = BLOCK_GROUND,
	SOLID_LAST = BLOCK_GROUND,
	ENTITY_FIRST = PLAYERRIGHT,
	ENTITY_LAST = PLAYERRIGHT,

	ITEM_BIG_HEART = 140, ITEM_SMALL_HEART, ITEM_FIRE
};

class TileMap
{
public:
	TileMap();
	~TileMap();

	AppStatus Initialise();
	AppStatus Load(int data[], int w, int h, int up, int right, int down, int left);
	void Update();
	void Render();
	void Release();

	//Test for collisions with walls
	bool TestCollisionWallLeft(const AABB& box) const;
	bool TestCollisionWallRight(const AABB& box) const;

	//Test collision with the ground and update 'py' with the maximum y-position to prevent
	//penetration of the grounded tile, that is, the pixel y-position above the grounded tile.
	//Grounded tile = solid tile (blocks) or ladder tops.
	bool TestCollisionGround(const AABB& box, int* py) const;

	//Test if there is a ground tile one pixel below the given box
	bool TestFalling(const AABB& box) const;

	//Test if box is on ladder and update 'px' with the x-center position of the ladder
	bool TestOnLadder(const AABB& box, int* px) const;

	//Test if box is on ladder top and update 'px' with the x-center position of the ladder
	bool TestOnLadderTop(const AABB& box, int* px) const;

	int GetTpMap(int direction) const;

private:
	void InitTileDictionary();

	Tile GetTileIndex(int x, int y) const;
	bool IsTileSolid(Tile tile) const;
	bool IsTileLadderTop(Tile tile) const;
	bool IsTileLadder(Tile tile) const;
	bool CollisionX(const Point& p, int distance) const;
	bool CollisionY(const Point& p, int distance) const;
	int GetLadderCenterPos(int pixel_x, int pixel_y) const;

	//Tile map
	Tile* map;

	//Size of the tile map
	int size, width, height, up, right, down, left;
	
	//Dictionary of tile frames
	std::unordered_map<int, Rectangle> dict_rect;

	//Tile sheet
	const Texture2D* img_tiles;
};

