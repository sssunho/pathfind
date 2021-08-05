#include "pathFind.h"
#include "gameObject.h"
#include "map.h"

stack<POINT> path;
vector<vector<bool>> visit;
vector<vector<bool>> open;
extern vector<vector<Node*>> map;

struct compare
{
	bool operator()(Node* p1, Node* p2)
	{
		return p1->getF() == p2->getF() ? p1->getG() > p2->getG() : p1->getF() > p2->getF();
	}
};


priority_queue<Node*, vector<Node*>, compare> openNodes;

Node* findPath(POINT start, POINT end)
{
	visit = vector<vector<bool>>(map.size(), vector<bool>(map[0].size(), false));
	open = vector<vector<bool>>(map.size(), vector<bool>(map[0].size(), true));
	openNodes = priority_queue<Node*, vector<Node*>, compare>();
	map[start.y][start.x]->setG(0);
	map[start.y][start.x]->setH(getDistance(start, end));
	map[start.y][start.x]->setPrev(NULL);

	Node* nearest = map[start.y][start.x];
	selectNode(start, end);

	while (!openNodes.empty())
	{
		Node* temp = openNodes.top();
		openNodes.pop();
		selectNode(temp->getPos(), end);
		if (nearest->getH() > temp->getH())
			nearest = temp;
		if (visit[end.y][end.x])
			return map[end.y][end.x];
	}

	return nearest;
}

void selectNode(POINT pos, POINT end)
{
	open[pos.y][pos.x] = false;

	updateNode(POINT({ pos.x - 1, pos.y }), end, pos);
	updateNode(POINT({ pos.x + 1, pos.y }), end, pos);
	updateNode(POINT({ pos.x, pos.y - 1 }), end, pos);
	updateNode(POINT({ pos.x, pos.y + 1 }), end, pos);
	updateNode(POINT({ pos.x - 1, pos.y - 1 }), end, pos);
	updateNode(POINT({ pos.x - 1, pos.y + 1 }), end, pos);
	updateNode(POINT({ pos.x + 1, pos.y - 1 }), end, pos);
	updateNode(POINT({ pos.x + 1, pos.y + 1 }), end, pos);
}

void updateNode(POINT pos, POINT end, POINT prev)
{
	if (pos.x < 0 || pos.y < 0 || pos.x >= NX || pos.y >= NY)
		return;
	if (!open[pos.y][pos.x] || map[pos.y][pos.x]->isBlock())
		return;

	Node temp(pos, getDistance(pos, prev) + map[prev.y][prev.x]->getG(), getDistance(pos, end), false, map[prev.y][prev.x]);

	if (visit[pos.y][pos.x])
	{
		if (temp > *map[pos.y][pos.x])
		{
			*map[pos.y][pos.x] = temp;
			sortAgain();
		}
	}
	else
	{
		visit[pos.y][pos.x] = true;
		*map[pos.y][pos.x] = temp;
		openNodes.push(map[pos.y][pos.x]);
	}

}

Node* findPath_(POINT start, POINT end, int size)
{
	visit = vector<vector<bool>>(map.size(), vector<bool>(map[0].size(), false));
	open = vector<vector<bool>>(map.size(), vector<bool>(map[0].size(), true));
	openNodes = priority_queue<Node*, vector<Node*>, compare>();
	map[start.y][start.x]->setG(0);
	map[start.y][start.x]->setH(getDistance(start, end));
	map[start.y][start.x]->setPrev(NULL);

	Node* nearest = map[start.y][start.x];
	selectNode_(start, end, size);

	while (!openNodes.empty())
	{
		Node* temp = openNodes.top();
		openNodes.pop();
		selectNode_(temp->getPos(), end, size);
		if (nearest->getH() > temp->getH())
			nearest = temp;
		if (visit[end.y][end.x])
			return map[end.y][end.x];
	}

	return nearest;
}

void selectNode_(POINT pos, POINT end, int size)
{
	open[pos.y][pos.x] = false;

	updateNode_(POINT({ pos.x - 1, pos.y }), end, pos, size);
	updateNode_(POINT({ pos.x + 1, pos.y }), end, pos, size);
	updateNode_(POINT({ pos.x, pos.y - 1 }), end, pos, size);
	updateNode_(POINT({ pos.x, pos.y + 1 }), end, pos, size);
	updateNode_(POINT({ pos.x - 1, pos.y - 1 }), end, pos, size);
	updateNode_(POINT({ pos.x - 1, pos.y + 1 }), end, pos, size);
	updateNode_(POINT({ pos.x + 1, pos.y - 1 }), end, pos, size);
	updateNode_(POINT({ pos.x + 1, pos.y + 1 }), end, pos, size);
}

void updateNode_(POINT pos, POINT end, POINT prev, int size)
{
	if (pos.x < 0 || pos.y < 0 || pos.x >= NX || pos.y >= NY)
		return;
	if (!open[pos.y][pos.x] || map[pos.y][pos.x]->isBlock())
		return;
	if (blockCheck(pos, size))
		return;

	Node temp(pos, getDistance(pos, prev) + map[prev.y][prev.x]->getG(), getDistance(pos, end), false, map[prev.y][prev.x]);

	if (visit[pos.y][pos.x])
	{
		if (temp > *map[pos.y][pos.x])
		{
			*map[pos.y][pos.x] = temp;
			sortAgain();
		}
	}
	else
	{
		visit[pos.y][pos.x] = true;
		*map[pos.y][pos.x] = temp;
		openNodes.push(map[pos.y][pos.x]);
	}

}

bool blockCheck(POINT pos, int size)
{
	if (pos.x + size > map[0].size() || pos.y + size > map.size())
		return true;
	for(int i = 0; i < size ; i++)
		for (int j = 0; j < size; j++)
		{
			if (map[pos.y + i][pos.x + j]->isBlock())
				return true;
		}
	return false;
}


int getDistance(POINT p1, POINT p2)
{
	int bx = abs(p1.x - p2.x);
	int by = abs(p1.y - p2.y);
	return bx > by ? by * 14 + (bx - by) * 10 : bx * 14 + (by - bx) * 10;
}

void sortAgain()
{
	priority_queue<Node*, vector<Node*>, compare> temp;
	while (!openNodes.empty())
	{
		temp.push(openNodes.top());
		openNodes.pop();
	}
	openNodes = temp;
	
}

