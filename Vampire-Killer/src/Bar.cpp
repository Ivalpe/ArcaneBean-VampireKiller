#include <raylib.h>
#include "Bar.h"
#include "ResourceManager.h"
#include "Entity.h"
#include "Sprite.h"

Bar::Bar(int m, Color c, Point& pos, int w, int h)
{
	max = m;
	current = max;
	col = c;
	width = w;
	height = h;
	p = pos;
}
Bar::Bar() {};
Bar::~Bar() {}
int Bar::getCurrent()
{
	return current;
}
void Bar::changeBar(int life)
{
	width = life * 4;
}
void Bar::Draw()
{
	DrawRectangle(p.x, p.y, width, height, col);
}
