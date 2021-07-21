#ifndef __GAMEOBJ__
#define __GAMEOBJ__

#include "framework.h"

class GameObject
{
public:
	POINT pos;
	GameObject(int x = 0, int y = 0) : pos(POINT({ x,y })) {}
};

class Node
{
private:
	POINT pos;
	int g;
	int h;
	bool block;
	Node* prev;

public:
	Node(POINT pos, int g = 0, int h = 0, bool block = false, Node* prev = NULL) : pos(pos), g(g), h(h), block(block), prev(prev) {}
	void draw(HDC& hdc);
	int getG() { return g; }
	int getH() { return h; }
	int getF() { return g + h; }
	bool isBlock() { return block; }
};

void initMap();

void releaseMap();

#endif