#include "gameObject.h"
#include "UI.h"
#include <vector>

using std::vector;
vector<vector<Node*>> map;

void initMap()
{
	map = vector<vector<Node*>>(WINDOWHEIGHT / UNITSIZE, vector<Node*>(WINDOWWIDTH / UNITSIZE, NULL));

	for (int i = 0; i < map.size(); i++)
		for (int j = 0; j < map[0].size(); j++)
			map[i][j] = new Node(POINT({ j, i }));
}

void releaseMap()
{
	for (int i = 0; i < map.size(); i++)
		for (int j = 0; j < map[0].size(); j++)
			delete map[i][j];
}

void Node::draw(HDC& hdc)
{
	TextOut(hdc, pos.x*UNITSIZE, pos.y*UNITSIZE, L"sel", wcslen(L"sel"));
}