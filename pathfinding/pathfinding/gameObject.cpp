#include "gameObject.h"
#include <list>

using std::list;
Actor* marill;

list<GameObject*> objList;

void initObject()
{
	marill = new Actor(100, 100, DIRECTION::D, L"images\\marill.png");
	objList.push_back(marill);
}

void releaseObject()
{
	for (list<GameObject*>::iterator it = objList.begin(); it != objList.end(); it++)
		delete (*it);

	objList.clear();
}

void Actor::setState(ActorState st)
{
	switch (state)
	{
	case ActorState::IDLE:
		if (st == ActorState::ONMOVE)
		{
			sprite.play();
		}
	break;

	case ActorState::ONMOVE:
		if (st == ActorState::IDLE)
		{
			sprite.pause();
			sprite.setFrame(1);
		}
	break;
	}

	state = st;
}

void Actor::draw(HDC& hdc)
{
	sprite.draw(hdc, pos.x, pos.y);
}

void Actor::update()
{
	pos.x += vel.x;
	pos.y += vel.y;
}

void Actor::setDirection(DIRECTION dir)
{
	switch (dir)
	{
	case DIRECTION::D:
		sprite.setYOffset(0);
		break;
	case DIRECTION::L:
		sprite.setYOffset(1);
		break;
	case DIRECTION::R:
		sprite.setYOffset(2);
		break;
	case DIRECTION::U:
		sprite.setYOffset(3);
		break;
	case DIRECTION::LU:
		sprite.setYOffset(4);
		break;
	case DIRECTION::RU:
		sprite.setYOffset(5);
		break;
	case DIRECTION::LD:
		sprite.setYOffset(6);
		break;
	case DIRECTION::RD:
		sprite.setYOffset(7);
		break;
	}

	Actor::dir = dir;
}