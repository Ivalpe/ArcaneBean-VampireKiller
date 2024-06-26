#pragma once
#include <raylib.h>
#include "Globals.h"
#include "Entity.h"

class Bar
{
public:
	Bar(int m, Color c, Point& pos, int width, int height);
	Bar();
	~Bar();

	int getCurrent();
	void changeBar(int life);
	void Draw();
private:
	int max, current, width, height;
	Color col;
	Point p;
};