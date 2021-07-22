#include "UI.h"
#include "gameObject.h"
#include "pathFind.h"
#include "map.h"
#include "intVector.h"
#include <list>

extern HWND ghWnd;

using std::list;

bool toggleSelect = false;
POINT start = { -1, -1 };
POINT end = { -1, -1 };

extern stack<POINT> path;
extern vector<vector<Node*>> map;
extern list<GameObject*> objList;
extern Actor* marill;

vector<HBRUSH> brushes;
Node* dest = NULL;

void initBrush()
{
	brushes.push_back(CreateSolidBrush(RGB(255, 255, 255)));
	brushes.push_back(CreateSolidBrush(RGB(80, 80, 80)));
	brushes.push_back(CreateSolidBrush(RGB(0, 168, 243)));
	brushes.push_back(CreateSolidBrush(RGB(14, 209, 69)));
	brushes.push_back(CreateSolidBrush(RGB(255, 0, 0)));
}

void releaseBrush()
{
	for (int i = 0; i < brushes.size(); i++)
		DeleteObject(brushes[i]);
}

void clickNode(POINT pos)
{
	if (map[pos.y][pos.x]->isBlock())
		return;
	if (toggleSelect)
	{
		if (start.x == pos.x && start.y == pos.y)
			return;
		end = pos;
		dest = findPath(start, end);
		path = getPath(dest->getPos());
		marill->pos = toGlobalSpace( start);
		if(!path.empty())
			marill->setState(ActorState::ONMOVE);
	}
	else
	{
		start = pos;
		end = { -1,-1 };
		dest = NULL;
	}

	toggleSelect = !toggleSelect;
}

void blockNode(POINT pos)
{
	map[pos.y][pos.x]->toggleBlock();
}

void render()
{
	HDC hdc = GetDC(ghWnd);
	HDC buffer = CreateCompatibleDC(hdc);	
	HBITMAP bitmap = CreateCompatibleBitmap(hdc, WINDOWWIDTH, WINDOWHEIGHT);
	HBRUSH oldBrush;

	SelectObject(buffer, bitmap);

	for (int i = 0; i < map.size(); i++)
		for (int j = 0; j < map[0].size(); j++)
			if (map[i][j] != NULL)
				map[i][j]->draw(buffer);

	drawPath(buffer, dest);

	if (start.x >= 0)
	{
		POINT p = toGlobalSpace(start);
		RECT rt = { p.x - UNITSIZE / 2, p.y - UNITSIZE / 2, p.x + UNITSIZE / 2, p.y + UNITSIZE / 2 };
		oldBrush = (HBRUSH)SelectObject(buffer, brushes[BLUE]);
		Rectangle(buffer, rt.left, rt.top, rt.right, rt.bottom);
		SelectObject(buffer, oldBrush);
	}
	if (end.x >= 0)
	{
		POINT p = toGlobalSpace(end);
		RECT rt = { p.x - UNITSIZE / 2, p.y - UNITSIZE / 2, p.x + UNITSIZE / 2, p.y + UNITSIZE / 2 };
		oldBrush = (HBRUSH)SelectObject(buffer, brushes[GREEN]);
		Rectangle(buffer, rt.left, rt.top, rt.right, rt.bottom);
		SelectObject(buffer, oldBrush);
	}

	for (list<GameObject*>::iterator it = objList.begin(); it != objList.end(); it++)
		(*it)->draw(buffer);

	if (!path.empty())
	{
		trackingPath(marill, path);
	}

	marill->update();

	BitBlt(hdc, 0, 0, WINDOWWIDTH, WINDOWHEIGHT, buffer, 0, 0, SRCCOPY);

	DeleteObject(bitmap);
	DeleteDC(buffer);
	ReleaseDC(ghWnd, hdc);
}

void drawGrid(HDC& hdc)
{
	for (int i = 1; i < WINDOWWIDTH / UNITSIZE; i++)
	{
		MoveToEx(hdc, i*UNITSIZE, 0, 0);
		LineTo(hdc, i*UNITSIZE, WINDOWHEIGHT);
	}
	for (int i = 1; i < WINDOWHEIGHT / UNITSIZE; i++)
	{
		MoveToEx(hdc, 0, i*UNITSIZE, 0);
		LineTo(hdc, WINDOWWIDTH, i*UNITSIZE);
	}
}

void drawPath(HDC& hdc, Node* node)
{
	if (node == NULL)
		return;
	drawPath(hdc, node->getPrev());
	HBRUSH oldBrush;
	POINT p = toGlobalSpace(node->getPos());
	RECT rt = { p.x - UNITSIZE / 2, p.y - UNITSIZE / 2, p.x + UNITSIZE / 2, p.y + UNITSIZE / 2 };
	oldBrush = (HBRUSH)SelectObject(hdc, brushes[RED]);
	Rectangle(hdc, rt.left, rt.top, rt.right, rt.bottom);
	SelectObject(hdc, oldBrush);
}

void SetClientSize(HWND hWnd, int nDestClientWidth, int nDestClientHeight)
{
	::SetWindowPos(hWnd, NULL, 0, 0, nDestClientWidth, nDestClientHeight, SWP_NOMOVE);
	RECT stWindowRect;
	RECT stClientRect;
	GetWindowRect(hWnd, &stWindowRect);
	GetClientRect(hWnd, &stClientRect);

	int nClientWidth = stClientRect.right - stClientRect.left;
	int nClientHeight = stClientRect.bottom - stClientRect.top;
	int nWindowWidth = stWindowRect.right - stWindowRect.left;
	int nWindowHeight = stWindowRect.bottom - stWindowRect.top;

	nWindowWidth += nWindowWidth - nClientWidth;
	nWindowHeight += nWindowHeight - nClientHeight;

	//해상도 구하기
	int nResolutionX = GetSystemMetrics(SM_CXSCREEN);
	int nResolutionY = GetSystemMetrics(SM_CYSCREEN);

	//알맞게 변환된 윈도우를 화면 정중앙에 배치한다.
	::SetWindowPos(hWnd, NULL,
		nResolutionX / 2 - nWindowWidth / 2,
		nResolutionY / 2 - nWindowHeight / 2,
		nWindowWidth, nWindowHeight, NULL);
}

POINT toLocalSpace(POINT p)
{
	return POINT({ p.x / UNITSIZE , p.y / UNITSIZE });
}

POINT toGlobalSpace(POINT p)
{
	return POINT({ p.x * UNITSIZE + UNITSIZE / 2, p.y * UNITSIZE + UNITSIZE / 2 });
}

DIRECTION getDirectionKeyState()
{
	int l = 8 * ((GetAsyncKeyState(VK_LEFT) & 0x8001) > 0);
	int r = 2 * ((GetAsyncKeyState(VK_RIGHT) & 0x8001) > 0);
	int u = 4 * ((GetAsyncKeyState(VK_UP) & 0x8001) > 0);
	int d = 1 * ((GetAsyncKeyState(VK_DOWN) & 0x8001) > 0);

	return DIRECTION(l | r | u | d);
}

void trackingPath(Actor* obj, stack<POINT>& path)
{
	if (obj->pos == path.top())
	{
		POINT localDest;
		path.pop();
		if (path.empty())
		{
			obj->vel = { 0,0 };
			obj->setState(ActorState::IDLE);
			return;
		}
		localDest = path.top();
		POINT d = localDest - obj->pos;
		obj->vel.x = d.x > 0 ? 10 : d.x < 0 ? -10 : 0;
		obj->vel.y = d.y > 0 ? 10 : d.y < 0 ? -10 : 0;

		DIRECTION dir;
		if (obj->vel.x > 0)
		{
			dir = obj->vel.y == 0 ? DIRECTION::R : obj->vel.y > 0 ? DIRECTION::RD : DIRECTION::RU;
		}
		else if (obj->vel.x < 0)
		{
			dir = obj->vel.y == 0 ? DIRECTION::L : obj->vel.y > 0 ? DIRECTION::LD : DIRECTION::LU;
		}
		else
		{
			dir = obj->vel.y == 0 ? DIRECTION::NONE : obj->vel.y > 0 ? DIRECTION::D : DIRECTION::U;
		}

		obj->setDirection(dir);

	}
}

stack<POINT> getPath(POINT p)
{
	stack<POINT> temp;
	Node* ptr = map[p.y][p.x];
	while (ptr != NULL)
	{
		temp.push(toGlobalSpace(ptr->getPos()));
		ptr = ptr->getPrev();
	}

	return temp;
}