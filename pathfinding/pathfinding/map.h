#ifndef __MAP__
#define __MAP__

#include "framework.h"
#include "UI.h"

class Node
{
private:
	POINT pos;
	int g;
	int h;
	bool block;
	Node* prev;
	BRUSHCOLOR color;

public:
	Node(POINT pos = { 0, 0 }, int g = 0, int h = 0, bool block = false, Node* prev = NULL) : pos(pos), g(g), h(h), block(block), prev(prev), color(WHITE) {}
	void draw(HDC& hdc);
	int getG() { return g; }
	int getH() { return h; }
	int getF() { return g + h; }
	POINT getPos() { return pos; }
	Node* getPrev() { return prev; }
	void setG(int _g) { g = _g; }
	void setH(int _h) { h = _h; }
	void setPrev(Node* node) { prev = node; }
	bool isBlock() { return block; }
	void toggleBlock() { block = !block; }

	bool operator<(Node p)
	{
		return g + h == p.g + p.h ? g > p.g: g + h > p.g + p.h;
	}

	bool operator>(Node p)
	{
		return g + h == p.g + p.h ? g < p.g : g + h < p.g + p.h;
	}
};

void initMap();

void releaseMap();

#endif