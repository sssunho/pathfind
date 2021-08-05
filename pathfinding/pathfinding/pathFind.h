#ifndef __PATHFIND__
#define __PATHFIND__

#include "framework.h"
#include <stack>
#include <queue>
#include <vector>

using std::stack;
using std::vector;
using std::priority_queue;

class Node;

Node* findPath(POINT start, POINT end);

void selectNode(POINT pos, POINT end);

void updateNode(POINT pos, POINT end, POINT prev);

Node * findPath_(POINT start, POINT end, int size);

void selectNode_(POINT pos, POINT end, int size);

void updateNode_(POINT pos, POINT end, POINT prev, int size);

bool blockCheck(POINT pos, int size);

int getDistance(POINT p1, POINT p2);

void sortAgain();

void drawPath(HDC& hdc, Node* node);

#endif