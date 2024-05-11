#include "TileMap.h"
#include "Globals.h"
#include "ResourceManager.h"
#include <cstring>

TileMap::TileMap()
{
	map = nullptr;
	width = 0;
	height = 0;
	img_tiles = nullptr;
	InitTileDictionary();
}
TileMap::~TileMap()
{
	if (map != nullptr)
	{
		delete[] map;
		map = nullptr;
	}
}
void TileMap::InitTileDictionary()
{
	const int n = TILE_SIZE;


	dict_rect[(int)Tile::TREE1] = { 0,  0, n, n };
	dict_rect[(int)Tile::TREE2] = { n,  0, n, n };
	dict_rect[(int)Tile::TREE3] = { n * 2,  0, n, n };
	dict_rect[(int)Tile::TREE4] = { n * 3,  0, n, n };
	dict_rect[(int)Tile::TREE5] = { n * 4,  0, n, n };
	dict_rect[(int)Tile::TREE6] = { n * 5,  0, n, n };
	dict_rect[(int)Tile::TREE7] = { n * 6,  0, n, n };
	dict_rect[(int)Tile::TREE8] = { n * 7,  0, n, n };
	dict_rect[(int)Tile::TREE9] = { 0,  n, n, n };
	dict_rect[(int)Tile::TREE10] = { n,  n, n, n };
	dict_rect[(int)Tile::TREE11] = { n * 2,  n, n, n };
	dict_rect[(int)Tile::TREE12] = { n * 3,  n, n, n };
	dict_rect[(int)Tile::TREE13] = { n * 4,  n, n, n };
	dict_rect[(int)Tile::TREE14] = { n * 5,  n, n, n };
	dict_rect[(int)Tile::TREE15] = { n * 6,  n, n, n };
	dict_rect[(int)Tile::TREE16] = { n * 7,  n, n, n };
	dict_rect[(int)Tile::TREE17] = { 0,  n * 2, n, n };
	dict_rect[(int)Tile::TREE18] = { n,  n * 2, n, n };
	dict_rect[(int)Tile::TREE19] = { n * 2,  n * 2, n, n };
	dict_rect[(int)Tile::TREE20] = { n * 3,  n * 2, n, n };
	dict_rect[(int)Tile::TREE21] = { n * 4,  n * 2, n, n };
	dict_rect[(int)Tile::TREE22] = { n * 5,  n * 2, n, n };
	dict_rect[(int)Tile::TREE23] = { 0,  n * 3, n, n };
	dict_rect[(int)Tile::TREE24] = { n,  n * 3, n, n };
	dict_rect[(int)Tile::TREE25] = { n * 2,  n * 3, n, n };
	dict_rect[(int)Tile::TREE26] = { n * 3,  n * 3, n, n };
	dict_rect[(int)Tile::TREE27] = { 0,  n * 4, n, n };
	dict_rect[(int)Tile::TREE28] = { n,  n * 4, n, n };
	dict_rect[(int)Tile::TREE29] = { n * 2,  n * 4, n, n };
	dict_rect[(int)Tile::TREE30] = { n * 3,  n * 4, n, n };
	dict_rect[(int)Tile::TREE31] = { 0,  n * 5, n, n };
	dict_rect[(int)Tile::TREE32] = { n,  n * 5, n, n };
	dict_rect[(int)Tile::TREE33] = { n * 2,  n * 5, n, n };
	dict_rect[(int)Tile::TREE34] = { n * 3,  n * 5, n, n };
	dict_rect[(int)Tile::TREE35] = { 0,  n * 6, n, n };
	dict_rect[(int)Tile::TREE36] = { n,  n * 6, n, n };

	dict_rect[(int)Tile::BLOCK_STATUE1] = { n * 2,  n * 6, n, n };
	dict_rect[(int)Tile::BLOCK_STATUE2] = { n * 3,  n * 6, n, n };
	dict_rect[(int)Tile::BLOCK_STATUE3] = { n * 2,  n * 7, n, n };
	dict_rect[(int)Tile::BLOCK_STATUE4] = { n * 3,  n * 7, n, n };
	dict_rect[(int)Tile::BLOCK_STATUE5] = { n * 2,  n * 8, n, n };
	dict_rect[(int)Tile::BLOCK_STATUE6] = { n * 3,  n * 8, n, n };

	dict_rect[(int)Tile::BLOCK_FENCE1] = { 0,  n * 7, n, n };
	dict_rect[(int)Tile::BLOCK_FENCE2] = { n,  n * 7, n, n };
	dict_rect[(int)Tile::BLOCK_FENCE3] = { n * 4,  n * 7, n, n };
	dict_rect[(int)Tile::BLOCK_FENCE4] = { 0,  n * 8, n, n };
	dict_rect[(int)Tile::BLOCK_FENCE5] = { n,  n * 8, n, n };

	dict_rect[(int)Tile::CASTLE_OUT1] = { n * 4,  n * 3, n, n };
	dict_rect[(int)Tile::CASTLE_OUT2] = { n * 5,  n * 3, n, n };
	dict_rect[(int)Tile::CASTLE_OUT3] = { n * 6,  n * 3, n, n };
	dict_rect[(int)Tile::CASTLE_OUT4] = { n * 4,  n * 4, n, n };
	dict_rect[(int)Tile::CASTLE_OUT5] = { n * 5,  n * 4, n, n };
	dict_rect[(int)Tile::CASTLE_OUT6] = { n * 6,  n * 4, n, n };
	dict_rect[(int)Tile::CASTLE_OUT7] = { n * 7,  n * 4, n, n };
	dict_rect[(int)Tile::CASTLE_OUT8] = { n * 8,  n * 4, n, n };
	dict_rect[(int)Tile::CASTLE_OUT9] = { n * 4,  n * 5, n, n };
	dict_rect[(int)Tile::CASTLE_OUT10] = { n * 5,  n * 5, n, n };
	dict_rect[(int)Tile::CASTLE_OUT11] = { n * 6,  n * 5, n, n };
	dict_rect[(int)Tile::CASTLE_OUT12] = { n * 7,  n * 5, n, n };
	dict_rect[(int)Tile::CASTLE_OUT13] = { n * 8,  n * 5, n, n };
	dict_rect[(int)Tile::CASTLE_OUT14] = { n * 4,  n * 6, n, n };
	dict_rect[(int)Tile::CASTLE_OUT15] = { n * 5,  n * 6, n, n };
	dict_rect[(int)Tile::CASTLE_OUT16] = { n * 6,  n * 6, n, n };
	dict_rect[(int)Tile::CASTLE_OUT17] = { n * 7,  n * 6, n, n };
	dict_rect[(int)Tile::CASTLE_OUT18] = { n * 8,  n * 6, n, n };
	dict_rect[(int)Tile::CASTLE_OUT19] = { n * 5,  n * 7, n, n };
	dict_rect[(int)Tile::CASTLE_OUT20] = { n * 6,  n * 7, n, n };
	dict_rect[(int)Tile::CASTLE_OUT21] = { n * 7,  n * 7, n, n };
	dict_rect[(int)Tile::CASTLE_OUT22] = { n * 8,  n * 7, n, n };
	dict_rect[(int)Tile::CASTLE_OUT23] = { n * 4,  n * 8, n, n };
	dict_rect[(int)Tile::CASTLE_OUT24] = { n * 5,  n * 8, n, n };
	dict_rect[(int)Tile::CASTLE_OUT25] = { n * 6,  n * 8, n, n };
	dict_rect[(int)Tile::CASTLE_OUT26] = { n * 7,  n * 8, n, n };
	dict_rect[(int)Tile::CASTLE_OUT27] = { n * 8,  n * 8, n, n };
	dict_rect[(int)Tile::CASTLE_OUT28] = { n * 4,  n * 9, n, n };
	dict_rect[(int)Tile::CASTLE_OUT29] = { n * 5,  n * 9, n, n };

	dict_rect[(int)Tile::BLOCK_CASTLE_DIRT] = { n * 9,  0, n, n };
	dict_rect[(int)Tile::BLOCK_CASTLE_DIRT2] = { n * 10,  n * 5, n, n };

	dict_rect[(int)Tile::CASTLE1] = { n * 10,  0, n, n };
	dict_rect[(int)Tile::CASTLE2] = { n * 11,  0, n, n };
	dict_rect[(int)Tile::CASTLE3] = { n * 12,  0, n, n };
	dict_rect[(int)Tile::CASTLE4] = { n * 13,  0, n, n };
	dict_rect[(int)Tile::CASTLE_DOOR1] = { n * 9 ,  n, n, n };
	dict_rect[(int)Tile::CASTLE_DOOR2] = { n * 10,  n, n, n };
	dict_rect[(int)Tile::CASTLE_DOOR3] = { n * 9 ,  n * 2, n, n };
	dict_rect[(int)Tile::CASTLE_DOOR4] = { n * 10,  n * 2, n, n };
	dict_rect[(int)Tile::CASTLE_WINDOW1] = { n * 11,  n, n, n };
	dict_rect[(int)Tile::CASTLE_WINDOW2] = { n * 11,  n * 2, n, n };
	dict_rect[(int)Tile::CASTLE_WINDOW3] = { n * 12,  n, n, n };
	dict_rect[(int)Tile::CASTLE_WINDOW4] = { n * 12,  n * 2, n, n };
	dict_rect[(int)Tile::CASTLE5] = { n * 13,  n, n, n };
	dict_rect[(int)Tile::CASTLE6] = { n * 13,  n * 2, n, n };
	dict_rect[(int)Tile::CASTLE7] = { n * 9 ,  n * 3, n, n };
	dict_rect[(int)Tile::CASTLE8] = { n * 10,  n * 3, n, n };
	dict_rect[(int)Tile::CASTLE9] = { n * 11,  n * 3, n, n };
	dict_rect[(int)Tile::CASTLE10] = { n * 12,  n * 3, n, n };
	dict_rect[(int)Tile::CASTLE11] = { n * 13,  n * 3, n, n };
	dict_rect[(int)Tile::CASTLE12] = { n * 9 ,  n * 4, n, n };
	dict_rect[(int)Tile::CASTLE13] = { n * 10,  n * 4, n, n };
	dict_rect[(int)Tile::CASTLE14] = { n * 11,  n * 4, n, n };
	dict_rect[(int)Tile::CASTLE15] = { n * 12,  n * 4, n, n };
	dict_rect[(int)Tile::CASTLE16] = { n * 13,  n * 4, n, n };
	dict_rect[(int)Tile::CASTLE17] = { n * 9 ,  n * 5, n, n };
	dict_rect[(int)Tile::CASTLE18] = { n * 11,  n * 5, n, n };
	dict_rect[(int)Tile::CASTLE19] = { n * 12,  n * 5, n, n };

	dict_rect[(int)Tile::BLOCK_GROUND] = { 0,  n * 9, n, n };
	dict_rect[(int)Tile::AIR] = { n,  n * 9, n, n };



}
AppStatus TileMap::Initialise()
{
	ResourceManager& data = ResourceManager::Instance();

	if (data.LoadTexture(Resource::IMG_TILES, "Assets/Tilesets/tileset.png") != AppStatus::OK)
	{
		return AppStatus::ERROR;
	}
	img_tiles = data.GetTexture(Resource::IMG_TILES);

	return AppStatus::OK;
}
AppStatus TileMap::Load(int data[], int w, int h, int u, int r, int d, int l)
{
	size = w * h;
	width = w;
	height = h;
	up = u;
	right = r;
	down = d;
	left = l;

	if (map != nullptr)	delete[] map;

	map = new Tile[size];
	if (map == nullptr)
	{
		LOG("Failed to allocate memory for tile map");
		return AppStatus::ERROR;
	}
	memcpy(map, data, size * sizeof(int));

	return AppStatus::OK;
}
void TileMap::Update()
{

}
Tile TileMap::GetTileIndex(int x, int y) const
{
	int idx = x + y * width;
	if (idx < 0 || idx >= size)
	{
		LOG("Error: Index out of bounds. Tile map dimensions: %dx%d. Given index: (%d, %d)", width, height, x, y)
			return Tile::AIR;
	}
	return map[x + y * width];
}
bool TileMap::IsTileSolid(Tile tile) const
{
	return (Tile::SOLID_FIRST <= tile && tile <= Tile::SOLID_LAST);
}
bool TileMap::IsTileLadderTop(Tile tile) const
{
	return tile == Tile::LADDER_TOP_L || tile == Tile::LADDER_TOP_R;
}
bool TileMap::IsTileLadder(Tile tile) const
{
	return tile == Tile::LADDER_L || tile == Tile::LADDER_R;
}
bool TileMap::TestCollisionWallLeft(const AABB& box) const
{
	return CollisionX(box.pos, box.height);
}
bool TileMap::TestCollisionWallRight(const AABB& box) const
{
	return CollisionX(box.pos + Point(box.width - 1, 0), box.height);
}
bool TileMap::TestCollisionGround(const AABB& box, int* py) const
{
	Point p(box.pos.x, *py);	//control point
	int tile_y;

	if (CollisionY(p, box.width))
	{
		tile_y = p.y / TILE_SIZE;

		*py = tile_y * TILE_SIZE - 1;
		return true;
	}
	return false;
}
bool TileMap::TestFalling(const AABB& box) const
{
	return !CollisionY(box.pos + Point(0, box.height), box.width);
}
bool TileMap::CollisionX(const Point& p, int distance) const
{
	int x, y, y0, y1;

	//Calculate the tile coordinates and the range of tiles to check for collision
	x = p.x / TILE_SIZE;
	y0 = p.y / TILE_SIZE;
	y1 = (p.y + distance - 1) / TILE_SIZE;

	//Iterate over the tiles within the vertical range
	for (y = y0; y <= y1; ++y)
	{
		//One solid tile is sufficient
		if (IsTileSolid(GetTileIndex(x, y)))
			return true;
	}
	return false;
}
bool TileMap::CollisionY(const Point& p, int distance) const
{
	int x, y, x0, x1;
	Tile tile;

	//Calculate the tile coordinates and the range of tiles to check for collision
	y = p.y / TILE_SIZE;
	x0 = p.x / TILE_SIZE;
	x1 = (p.x + distance - 1) / TILE_SIZE;

	//Iterate over the tiles within the horizontal range
	for (x = x0; x <= x1; ++x)
	{
		tile = GetTileIndex(x, y);

		//One solid or laddertop tile is sufficient
		if (IsTileSolid(tile) || IsTileLadderTop(tile))
			return true;
	}
	return false;
}
bool TileMap::TestOnLadder(const AABB& box, int* px) const
{
	int left, right, bottom;
	int tx1, tx2, ty;
	Tile tile1, tile2;

	//Control points
	left = box.pos.x;
	right = box.pos.x + box.width - 1;
	bottom = box.pos.y + box.height - 1;

	//Calculate the tile coordinates
	tx1 = left / TILE_SIZE;
	tx2 = right / TILE_SIZE;
	ty = bottom / TILE_SIZE;

	//To be able to climb up or down, both control points must be on ladder
	tile1 = GetTileIndex(tx1, ty);
	tile2 = GetTileIndex(tx2, ty);
	if (IsTileLadder(tile1) && IsTileLadder(tile2))
	{
		*px = GetLadderCenterPos(left, bottom) - box.width / 2;
		return true;
	}
	return false;
}
bool TileMap::TestOnLadderTop(const AABB& box, int* px) const
{
	int left, right, bottom;
	int tx1, tx2, ty;
	Tile tile1, tile2;

	//Control points
	left = box.pos.x;
	right = box.pos.x + box.width - 1;
	bottom = box.pos.y + box.height - 1;

	//Calculate the tile coordinates
	tx1 = left / TILE_SIZE;
	tx2 = right / TILE_SIZE;
	ty = bottom / TILE_SIZE;

	//To be able to climb up or down, both control points must be on ladder
	tile1 = GetTileIndex(tx1, ty);
	tile2 = GetTileIndex(tx2, ty);
	if (IsTileLadderTop(tile1) && IsTileLadderTop(tile2))
	{
		*px = GetLadderCenterPos(left, bottom) - box.width / 2;
		return true;
	}
	return false;
}
int TileMap::GetTpMap(int direction) const {
	switch (direction)
	{
	case 1:
		return up;
		break;
	case 2:
		return right;
		break;
	case 3:
		return down;
		break;
	case 4:
		return left;
		break;
	}
}
int TileMap::GetLadderCenterPos(int pixel_x, int pixel_y) const
{
	int tx, ty;

	tx = pixel_x / TILE_SIZE;
	ty = pixel_y / TILE_SIZE;
	Tile tile = GetTileIndex(tx, ty);

	if (tile == Tile::LADDER_L || tile == Tile::LADDER_TOP_L)		return tx * TILE_SIZE + TILE_SIZE;
	else if (tile == Tile::LADDER_R || tile == Tile::LADDER_TOP_R)	return tx * TILE_SIZE;
	else
	{
		LOG("Internal error, tile should be a LADDER, coord: (%d,%d), tile type: %d", pixel_x, pixel_y, (int)tile);
		return 0;
	}
}
void TileMap::Render()
{
	Tile tile;
	Rectangle rc;
	Vector2 pos;

	for (int i = 0; i < height; ++i)
	{
		for (int j = 0; j < width; ++j)
		{
			tile = map[i * width + j];
			if (tile != Tile::AIR)
			{
				pos.x = (float)j * TILE_SIZE;
				pos.y = (float)i * TILE_SIZE;

				rc = dict_rect[(int)tile];
				DrawTextureRec(*img_tiles, rc, pos, WHITE);
			}
		}
	}
}
void TileMap::Release()
{
	ResourceManager& data = ResourceManager::Instance();
	data.ReleaseTexture(Resource::IMG_TILES);

	dict_rect.clear();
}
