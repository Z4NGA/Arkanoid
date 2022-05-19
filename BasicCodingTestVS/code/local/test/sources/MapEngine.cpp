#include "MapEngine.h"
MapEngine::MapEngine() {

}
MapEngine::~MapEngine() {

}
void MapEngine::LoadMap(int level) {
	char* mapPath;
	switch (level) {
	case 1:
		mapPath = "Assets/level1.txt";
		break;
	case 2:
		mapPath = "Assets/level2.txt";
		break;
	case 3:
		mapPath = "Assets/level3.txt";
		break;
	case 4:
		mapPath = "Assets/level4.txt";
		break;
	case 5:
		mapPath = "Assets/level5.txt";
		break;
	case 6:
		mapPath = "Assets/level6.txt";
		break;
	case 7:
		mapPath = "Assets/level7.txt";
		break;
	default:
		mapPath = "Assets/map.txt";
		break;
	}
	map = new vector<vector<char>>();
	ifstream fromFile(mapPath);
	string ss;
	int lineIndex = 0;
	if (fromFile.is_open()) {
		while (fromFile.good()) {
			auto temp = new vector<char>();
			map->push_back(*temp);
			getline(fromFile, ss);
			cout << ss << endl;
			for (auto ch : ss)
			{
				map->at(lineIndex).push_back(ch);
			}
			lineIndex++;
		}
		fromFile.close();
	}

}
void MapEngine::SaveMap() {

}
vector<vector<char>>* MapEngine::GetMap() {
	return map;
}

void MapEngine::PrintMap() {
	for (size_t i = 0; i < map->size(); i++)
	{
		for (auto ch : map->at(i))
		{
			cout << ch;
		}
		cout << endl;
	}
}