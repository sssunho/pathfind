#ifndef __UI__
#define __UI__

#include "framework.h"
#include <stack>
#include <vector>
#define UNITSIZE 40
#define NX WINDOWWIDTH / UNITSIZE
#define NY WINDOWHEIGHT / UNITSIZE

using std::stack;
using std::vector;

enum BRUSHCOLOR {WHITE, GRAY, BLUE, GREEN, RED};
enum class DIRECTION;
class Node;
class Actor;

void initBrush();

void releaseBrush();

void clickNode(POINT pos);

void blockNode(POINT pos);

void render();

void drawGrid(HDC& hdc);

void SetClientSize(const HWND hWnd, int nDestClientWidth = 800, int nDestClientHeight = 800);

POINT toLocalSpace(POINT p);

POINT toGlobalSpace(POINT p);

DIRECTION getDirectionKeyState();

void trackingPath(Actor * obj, stack<POINT>& path);

stack<POINT> getPath(POINT p);

#endif