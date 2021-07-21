#include "UI.h"

extern HWND ghWnd;

bool toggleSelect = false;
POINT start;
POINT end;

extern stack<Node*> path;

void clickNode(POINT pos)
{
	if (toggleSelect)
	{
		end = pos;
		path = findPath();

	}
	else
	{
		start = pos;
	}
}

void render()
{
	HDC hdc = GetDC(ghWnd);
	HDC buffer = CreateCompatibleDC(hdc);

	//drawGrid(buffer);
	drawGrid(hdc);

	BitBlt(hdc, 0, 0, WINDOWWIDTH, WINDOWHEIGHT, buffer, 0, 0, SRCCOPY);

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
