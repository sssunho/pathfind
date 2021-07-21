#ifndef __UI__
#define __UI__

#include "framework.h"
#include "gameObject.h"
#include "pathFind.h"
#include <stack>
#define UNITSIZE 40

using std::stack;

void clickNode(POINT pos);

void render();

void drawGrid(HDC& hdc);

void SetClientSize(const HWND hWnd, int nDestClientWidth = 800, int nDestClientHeight = 800);

POINT toLocalSpace(POINT p);

#endif