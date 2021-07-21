#ifndef __PATHFIND__
#define __PATHFIND__

#include "framework.h"
#include "gameObject.h"
#include <stack>
#include <queue>

using std::stack;
using std::priority_queue;

stack<Node*> findPath();

void drawPath();

#endif