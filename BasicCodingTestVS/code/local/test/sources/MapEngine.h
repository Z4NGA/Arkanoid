#ifndef MapEngine_HEADER
#define MapEngine_HEADER

#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>


#pragma once
using namespace std;
class MapEngine
{
protected:
	vector<vector<char>>* map;
public:
	MapEngine();
	~MapEngine();
	void LoadMap(int level);
	void SaveMap();
	vector<vector<char>>* GetMap();
	void PrintMap();
};


#endif // !MapEngine_HEADER