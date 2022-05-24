#ifndef MapEngine_HEADER
#define MapEngine_HEADER

#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>


#pragma once
using namespace std;
/*
* @class: an engine responsible for reading maps from files and converting them to a map configuration vector
*/
class MapEngine
{
protected:
	vector<vector<char>>* map;
public:
	MapEngine();
	~MapEngine();
	/*
	* @brief loads the map of level from a file
	*/
	void LoadMap(int level);
	/*
	* @brief saves the map to a file
	*/
	void SaveMap();
	/*
	* @return: returns the map configurations vector of the currently loaded map
	*/
	vector<vector<char>>* GetMap();
	/*
	* @brief prints a map to the screen
	*/
	void PrintMap();
};


#endif // !MapEngine_HEADER