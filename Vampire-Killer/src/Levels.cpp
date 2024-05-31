#include "Levels.h"
#include <raylib.h>
#include <vector>

Levels::Levels() {}

AppStatus Levels::Initialise() {

	level = 1;
	stage = 0;
	std::vector<int> mapEnt;

	mapEnt =  //stage 0.0
	{
		0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0,
		0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0,
		0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0,
		0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0,
		0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0,
		0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0,
		0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0,
		0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0,
		0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0,
		0 ,103 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,101,0,
		0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0
	};
	entities.push_back(mapEnt);

	mapEnt =  //stage 0.1
	{
		0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0,
		0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0,
		0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0,
		0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0,
		0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0,
		0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0,
		0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0,
		0 ,0 ,0 ,0,144,145 ,146 ,143 ,142 ,141 ,0 ,0,140,0 ,0 ,0,
		0,103,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0,101,0,
		0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0,
		0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0
	};
	entities.push_back(mapEnt);

	mapEnt = {//stage 0.2

		 0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0,
		0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0,
		0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0,
		0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0,
		0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0,
		0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0,
		0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0,
		0 ,0 ,0 ,0,141,0 ,0 ,0 ,0 ,0 ,0 ,0,141,0 ,0 ,0,
		0,103,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0,101,0,
		0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0,
		0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0
	};
	entities.push_back(mapEnt);

	mapEnt = {//stage 0.3

		0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0,
		0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0,
		0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0,
		0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0,
		0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0,
		0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0,
		0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0,
		0 ,0 ,0 ,0 ,142 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0,
		0 ,103,0,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0,
		0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0,
		0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0
	};
	entities.push_back(mapEnt);

	mapEnt = {//stage 2.4

		0 ,0 ,0 ,0 ,0 ,0 ,100 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0,
		0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0,
		0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,143 ,0 ,0 ,0 ,0 ,0,
		0 ,0 ,0 ,0 ,0 ,0 ,200 ,0,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0,
		0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0,
		0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0,
		0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0,
		0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,146 ,0 ,0 ,0 ,0 ,0 ,143 ,0,
		0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0,
		0 ,103,0,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,200 ,0 ,0,
		0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0
	};
	entities.push_back(mapEnt);

	mapEnt = {//stage 2.5

		0 ,0 ,0 ,0 ,0 ,203 ,100 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0,
		0 ,0 ,0 ,0 ,143 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,143 ,0 ,0 ,0,
		0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0,
		0 ,0 ,0 ,0 ,0 ,0 ,0 ,200 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0,
		0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0,
		0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0,
		0 ,0 ,0 ,0 ,143 ,0 ,0 ,0 ,0 ,143 ,0 ,0 ,0 ,0 ,0 ,0,
		0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0,
		0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0,
		0 ,103,0,0 ,0 ,0 ,0 ,200 ,0 ,0 ,0 ,0 ,0 ,0 ,101 ,0,
		0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0
	};
	entities.push_back(mapEnt);

	mapEnt = {//stage 2.6

		0 ,0 ,0 ,0 ,100 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0,
		0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0,
		0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0,
		0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0,
		0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0,
		0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0,
		0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0,
		0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0,
		0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0,
		0 ,103,0,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,101 ,0,
		0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0
	};
	entities.push_back(mapEnt);

	mapEnt = {//stage 2.7

		0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0,
		0 ,0 ,0 ,0 ,143 ,0 ,0 ,0 ,0 ,0 ,143 ,0 ,0 ,0 ,0 ,0,
		0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0,
		0 ,103 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,101 , 0,
		0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0,
		0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0,
		0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0,
		0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0,
		0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0,
		0 ,0,0,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0,
		0 ,0 ,0 ,0 ,0 ,104 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0
	};
	entities.push_back(mapEnt);

	mapEnt = {//stage 2.8

		0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0,
		0 ,143 ,0 ,0 ,0 ,0 ,0 ,143 ,0 ,0 ,0 ,143 ,0 ,0 ,0 ,0,
		0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,201,
		0 ,103,0,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,101,0,
		0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0,
		0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0,
		0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0,
		0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0,
		202,0,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,201,
		0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0,
		0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,104,0,0 ,0 ,0 ,0 ,0 ,0
	};
	entities.push_back(mapEnt);

	mapEnt = {//stage 2.9

		0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0,
		0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0,
		0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0,
		0 ,103 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0,
		0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0,
		0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0,
		0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0,
		0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0,
		0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0,
		0 ,0,0,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0,
		0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,104 ,0 ,0
	};
	entities.push_back(mapEnt);

	mapEnt = {//boss fight

		0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0,
		0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0,
		0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0,
		0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0,
		0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0,
		0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0,
		0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0,
		0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,101 ,0,
		0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0,
		0 ,0,0,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0,
		0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0
	};
	entities.push_back(mapEnt);

	return AppStatus::OK;
}

std::vector<int> Levels::getMap() {
	std::vector<int> map;
	switch (level)
	{
	case 1://stage 0.0
		map = {
		0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0,
		0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0,
		0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0,
		0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0,
		0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0,
		0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0,
		0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0,
		0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0,
		0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0,
		0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0,
		63,63,63,63,63,63,63,63,63,63,63,63,63,63,63,63,
		};
		return map;
		break;
	case 2://stage 1.1
		map = {
		1, 2, 3, 4, 1, 2, 3, 4, 1, 2, 3, 4, 1, 2, 3, 4,
		9, 10,11,12,9 ,10,11,12,9 ,10,11,12,9 ,10,11,12,
		17,18,19,20,17,18,19,20,17,18,19,20,17,18,19,20,
		23,24,25,26,23,24,25,26,23,24,25,26,23,24,25,26,
		27,28,29,30,27,28,29,30,27,28,29,30,27,28,29,30,
		31,32,33,34,5 ,6 ,21,22,31,6 ,31,7 ,8 ,6 ,31,7,
		35,36,40,41,13,14,35,14,35,14,35,34,16,14,35,14,
		46,47,42,43,47,47,48,47,48,47,48,47,47,47,46,47,
		49,49,44,45,50,49,49,49,49,49,49,49,50,49,49,49,
		60,60,60,60,60,60,60,60,60,60,60,60,60,60,60,60,
		0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0
		};
		return map;
		break;
	case 3://stage 1.2
		map = {
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
		return map;
		break;
	case 4://stage 1.3
		map = {
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
		return map;
		break;
	case 5://stage 2.1
		map = {
		 61 ,61 ,61 ,61 ,111,111,112,113,123,134,111,111,112,113,61 ,61
		,61 ,61 ,61 ,61 ,119,121,112,113,126,125,119,121,112,113,61 ,61
		,61 ,61 ,61 ,61 ,120,122,112,113,128,135,120,122,112,113,61 ,61
		,61 ,61 ,61 ,61 ,111,111,112,113,131,132,111,111,112,113,61 ,61
		,61 ,61 ,61 ,61 ,61 ,61 ,61 ,61 ,61 ,61 ,111,111,61 ,61 ,61 ,61
		,61 ,61 ,61 ,61 ,111,111,112,113,111,111,111,111,112,113,123,134
		,61 ,61 ,61 ,61 ,111,111,112,113,111,111,111,111,112,113,126,125
		,123,134,111,111,119,121,112,113,111,111,111,111,112,113,111,111
		,126,125,111,111,120,122,112,113,111,111,61 ,61 ,112,113,111,111
		,128,135,111,111,131,132,112,113,111,111,131,132,112,113,128,135
		,61 ,61 ,61 ,61 ,61 ,61 ,61 ,61 ,61 ,61 ,61 ,61 ,61 ,61 ,61 ,61
		};
		return map;
		break;
	case 6://stage 2.2
		map = {
		 61,61,112,113,126,127,111,111,139,111,61,61,111,111,112,113,
		61,61,112,113,111,111,111,139,119,121,61,61,111,111,112,113,
		61,61,112,113,111,111,139,111,120,122,61,61,111,111,112,113,
		61,61,112,113,138,139,131,132,111,111,61,61,131,132,112,113,
		61,61,61,61,61,61,61,61,139,61,61,61,128,129,61,61,
		133,130,112,113,111,111,111,139,111,111,61,61,124,135,112,113,
		114,125,112,113,111,111,139,111,111,111,61,61,61,61,112,113,
		119,121,112,113,111,139,131,132,119,121,61,61,123,130,112,113,
		120,122,112,113,139,111,128,129,120,122,61,61,114,125,112,113,
		131,132,112,140,111,111,124,135,131,132,61,61,131,132,112,113,
		61,61,61,61,61,61,61,61,61,61,61,61,61,61,61,61
		};
		return map;
		break;
	case 7://stage 2.3
		map = {
		 128,129,111,111,139,111,61,61,111,111,114,125,139,111,61,61,
		133,134,111,139,111,111,61,61,119,121,138,139,111,111,61,61,
		114,125,139,111,111,111,61,61,120,122,139,111,111,111,61,61,
		138,139,131,132,111,111,61,61,138,139,111,111,111,111,61,61,
		61,61,61,61,61,61,61,61,61,61,111,111,111,111,61,61,
		133,134,111,111,112,113,123,130,111,111,111,111,61,61,61,61,
		114,125,111,111,112,113,114,125,111,111,139,61,61,61,61,61,
		111,111,111,111,112,113,111,111,138,139,131,132,111,111,119,121,
		111,111,61,61,112,113,111,111,139,111,128,129,111,111,120,122,
		111,111,131,132,112,113,138,139,111,111,124,135,111,111,131,132,
		61,61,61,61,61,61,61,61,61,61,61,61,61,61,61,61
		};
		return map;
		break;
	case 8://stage 2.4
		map = {
		61,61,111,111,111,111,112,113,111,111,114,125,112,113,111,111,
		115,116,119,121,111,111,112,113,119,121,111,111,112,113,119,121,
		115,116,120,122,111,111,112,113,120,122,111,111,112,113,120,122,
		117,118,131,132,111,111,112,113,111,111,111,111,112,113,131,132,
		61,61,128,129,111,111,61,61,61,61,111,111,61,61,61,61,
		61,111,124,135,111,111,111,111,61,61,111,111,112,113,61,61,
		61,111,61,61,111,111,111,111,61,61,111,111,112,113,61,61,
		61,111,133,134,111,111,111,111,61,61,133,134,112,113,61,61,
		61,111,114,125,111,111,61,61,61,61,126,127,112,113,61,61,
		61,111,131,132,111,111,133,134,61,61,111,111,112,113,61,61,
		61,61,61,61,111,111,114,125,61,61,111,111,112,113,61,61
		};
		return map;
		break;
	case 9://stage 2.5
		map = {
		114,125,111,111,112,113,126,127,111,111,111,111,112,113,111,111,
		111,111,119,121,112,113,131,132,119,121,111,111,112,113,119,121,
		111,111,120,122,112,113,128,129,120,122,111,111,112,113,120,122,
		111,111,131,132,112,113,133,134,131,132,111,111,112,113,111,111,
		61,61,128,129,112,113,114,125,61,61,111,111,61,61,61,61,
		61,111,124,135,112,113,111,111,111,111,131,132,111,111,61,61,
		61,111,61,61,112,113,111,111,111,111,61,61,111,111,61,61,
		61,111,123,130,112,113,131,132,119,121,133,134,111,111,61,61,
		61,111,114,125,61,61,61,61,120,122,126,127,111,111,61,61,
		61,111,111,111,112,113,123,130,111,111,111,111,131,132,61,61,
		61,111,111,111,112,113,114,125,139,61,61,61,128,129,61,61
		};
		return map;
		break;
	case 10://stage 2.6
		map = {
		128,129,112,113,111,111,114,125,111,111,112,113,114,125,61,61,
		133,134,112,113,119,121,111,111,119,121,112,113,119,121,61,61,
		126,127,112,113,120,122,111,111,120,122,112,113,120,122,61,61,
		111,111,112,113,111,111,111,111,111,111,112,113,131,132,61,61,
		61,61,112,113,61,61,61,61,111,111,112,113,128,129,61,61,
		61,111,112,113,123,130,111,111,111,111,112,113,123,130,61,61,
		61,111,112,113,114,125,111,111,139,61,112,113,114,125,61,61,
		61,111,112,113,119,121,138,139,131,132,112,113,119,121,61,61,
		61,61,61,61,120,122,139,111,128,129,61,61,120,122,61,61,
		61,111,112,113,138,139,111,111,133,134,112,113,111,111,61,61,
		61,111,112,113,139,111,61,61,126,127,112,113,139,61,61,61,
		};
		return map;
		break;
	case 11://boss fight
		map = {
		111,111,182,179,180,181,182,179,180,181,182,179,180,181,182,179,
		111,111,112,113,0,0,112,113,170,171,112,113,0,0,112,113,
		111,111,112,113,170,171,112,113,174,175,112,113,170,171,112,113,
		111,111,112,113,172,173,112,113,176,176,112,113,172,173,112,113,
		111,111,112,113,172,173,112,113,176,176,112,113,172,173,112,113,
		111,111,112,113,172,173,112,113,0,0,112,113,172,173,112,113,
		111,111,112,113,172,173,112,113,0,0,112,113,172,173,112,113,
		61,61,112,113,172,173,112,113,177,178,112,113,172,173,112,113,
		61,61,61,61,172,173,112,113,61,61,112,113,172,173,61,61,
		61,61,61,61,61,61,61,61,61,61,61,61,61,61,61,61,
		61,61,61,61,61,61,61,61,61,61,61,61,61,61,61,61
		};
		return map;
		break;
	}
}

std::vector<int> Levels::getEnt() {
	return entities[level - 1];
}

void Levels::SetEnt(int pos) {
	entities[level - 1][pos] = 0;
}

int Levels::GetStage()
{
	if (level <= 4)
		return 0;
	else
		return 4;
}

posTp Levels::getTp() {
	posTp tp;
	switch (level)
	{
	case 1: //stage 0.0
		tp.top = 0;
		tp.right = 0;
		tp.down = 0;
		tp.left = 0;
		return tp;
		break;
	case 2://stage 1.1
		tp.top = 0;
		tp.right = 3;
		tp.down = 0;
		tp.left = 0;
		return tp;
		break;
	case 3://stage 1.2
		tp.top = 0;
		tp.right = 4;
		tp.down = 0;
		tp.left = 2;
		return tp;
		break;
	case 4://stage 1.3
		tp.top = 0;
		tp.right = 0;
		tp.down = 0;
		tp.left = 3;
		return tp;
		break;
	case 5://stage 2.4
		tp.top = 8;
		tp.right = 6;
		tp.down = 0;
		tp.left = 7;
		return tp;
		break;
	case 6://stage 2.5
		tp.top = 9;
		tp.right = 7;
		tp.down = 0;
		tp.left = 5;
		return tp;
		break;
	case 7://stage 2.6
		tp.top = 10;
		tp.right = 5;
		tp.down = 0;
		tp.left = 6;
		return tp;
		break;
	case 8://stage 2.7
		tp.top = 0;
		tp.right = 9;
		tp.down = 5;
		tp.left = 0;//boss
		return tp;
		break;
	case 9://stage 2.8
		tp.top = 0;
		tp.right = 10;
		tp.down = 6;
		tp.left = 8;
		return tp;
		break;
	case 10://stage 2.9
		tp.top = 0;
		tp.right = 0;
		tp.down = 7;
		tp.left = 9;
		return tp;
		break;
	case 11://boss fight
		tp.top = 0;
		tp.right = 8;
		tp.down = 0;
		tp.left = 0;
		return tp;
		break;
	}
}

void Levels::SetLvl(int lvl) {
	level = lvl;
}

int Levels::GetLvl()
{
	return level;
}