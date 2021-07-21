#include "gameObject.h"

using std::vector;
vector<vector<Node*>> map;
extern vector<HBRUSH> brushes;

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
	POINT p = toGlobalSpace(pos);
	RECT rt = { p.x - UNITSIZE / 2, p.y - UNITSIZE / 2, p.x + UNITSIZE / 2 , p.y + UNITSIZE / 2};
	WCHAR str[32];
	HBRUSH oldBrush;
	if (block)
	{
		oldBrush = (HBRUSH)SelectObject(hdc, brushes[GRAY]);
		Rectangle(hdc, rt.left, rt.top, rt.right, rt.bottom);
		SelectObject(hdc, oldBrush);
		return;
	}
	oldBrush = (HBRUSH)SelectObject(hdc, brushes[color]);
	Rectangle(hdc, rt.left, rt.top, rt.right, rt.bottom);
	SelectObject(hdc, oldBrush);
	swprintf_s(str, 32, L"%d\n%d %d\n", g + h, g, h);
	OffsetRect(&rt, 0, 5);
	DrawTextW(hdc, str, wcslen(str), &rt, DT_VCENTER | DT_CENTER);
}