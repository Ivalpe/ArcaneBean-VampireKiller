
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
	TREE1 = 1, TREE2, TREE3, TREE4, TREE5, TREE6, TREE7, TREE8, TREE9, TREE10, TREE11, TREE12, TREE13, TREE14, TREE15, TREE16,
	TREE17, TREE18, TREE19, TREE20, TREE21, TREE22, TREE23, TREE24, TREE25, TREE26, TREE27, TREE28, TREE29, TREE30, TREE31, TREE32,
	TREE33, TREE34, TREE35, TREE36,

	//id >= 40: fence
	BLOCK_STATUE1 = 40, BLOCK_STATUE2, BLOCK_STATUE3, BLOCK_STATUE4, BLOCK_STATUE5, BLOCK_STATUE6, BLOCK_FENCE1,
	BLOCK_FENCE2, BLOCK_FENCE3, BLOCK_FENCE4, BLOCK_FENCE5,

	//id >= 60: ground
	BLOCK_GROUND = 60, BLOCK_CASTLE_DIRT, BLOCK_CASTLE_DIRT2,

	//id >= 70: CASTLE_OUT
	CASTLE_OUT1 = 70, CASTLE_OUT2, CASTLE_OUT3, CASTLE_OUT4, CASTLE_OUT5, CASTLE_OUT6, CASTLE_OUT7, CASTLE_OUT8, CASTLE_OUT9, CASTLE_OUT10, CASTLE_OUT11, CASTLE_OUT12, CASTLE_OUT13, CASTLE_OUT14, CASTLE_OUT15,
	CASTLE_OUT16, CASTLE_OUT17, CASTLE_OUT18, CASTLE_OUT19, CASTLE_OUT20, CASTLE_OUT21, CASTLE_OUT22, CASTLE_OUT23, CASTLE_OUT24, CASTLE_OUT25, CASTLE_OUT26, CASTLE_OUT27, CASTLE_OUT28, CASTLE_OUT29,

	LADDER_L = 150, LADDER_R, LADDER_TOP_L, LADDER_TOP_R,

	// id >= 100: entities' initial locations
	PLAYERUP = 100, PLAYERRIGHT, PLAYERDOWN, PLAYERLEFT, PLAYERDOOR,

	CASTLE1 = 111, CASTLE2, CASTLE3, CASTLE4, CASTLE_DOOR1, CASTLE_DOOR2, CASTLE_DOOR3, CASTLE_DOOR4, CASTLE_WINDOW1, CASTLE_WINDOW2, CASTLE_WINDOW3, CASTLE_WINDOW4, CASTLE5, CASTLE6, CASTLE7,
	CASTLE8, CASTLE9, CASTLE10, CASTLE11, CASTLE12, CASTLE13, CASTLE14, CASTLE15, CASTLE16, CASTLE17,
	CASTLE18 = 137, CASTLE19, CASTLELADER1, CASTLELADER2,

	ITEM_FIRE_HEART = 140, ITEM_FIRE_HEART_BIG, ITEM_FIRE_WHIPE,


	ENEMY_KNIGHT = 200, ENEMY_MEDUSA_HEAD_LEFT, ENEMY_MEDUSA_HEAD_RIGHT,

	GLASS1 = 170, GLASS2, GLASS3, GLASS4, GLASS5, GLASS6, GLASS7,
	RED_THING = 177, RED_THING2, 
	ARCH1 = 179, ARCH2, ARCH3, ARCH4,

	STATIC_FIRST = BLOCK_GROUND,
	STATIC_LAST = BLOCK_GROUND,
	SOLID_FIRST = BLOCK_GROUND,
	SOLID_LAST = BLOCK_CASTLE_DIRT2,
	ENTITY_FIRST = PLAYERRIGHT,
	ENTITY_LAST = PLAYERRIGHT,
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
	bool TestCollisionGroundRight(const AABB& box) const;
	bool TestCollisionGroundLeft(const AABB& box) const;

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

