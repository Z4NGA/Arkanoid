#include "MapEngine.h"
MapEngine::MapEngine() {

}
MapEngine::~MapEngine() {

}
void MapEngine::LoadMap() {
	map = new vector<vector<char>>();
	ifstream fromFile("Assets/map.txt");
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