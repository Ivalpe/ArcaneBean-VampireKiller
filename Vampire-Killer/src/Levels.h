#pragma once
#include <raylib.h>
#include "Globals.h"
#include <vector>

struct posTp {
	int top, right, down, left;
};

class Levels
{
public:
	Levels();

	AppStatus Initialise();
	std::vector<int> getMap();
	std::vector<int> getEnt();
	posTp getTp();
	void setLvl(int level);

private:
	int level;
};