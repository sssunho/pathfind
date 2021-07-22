#ifndef __GAMEOBJ__
#define __GAMEOBJ__

#include "sprite.h"
#include "framework.h"
#include "UI.h"
#include <vector>

enum class DIRECTION { NONE = 0, D = 1, R = 2, RD = 3, U = 4, RU = 6, L = 8, LD = 9, LU = 12 };
enum class ActorState { IDLE, ONMOVE };

class GameObject
{
public:
	POINT pos;
	POINT vel;
	GameObject(int x = 0, int y = 0, int vx = 0, int vy = 0) : pos(POINT({ x,y })), vel(POINT({ vx,vy })) {}

	virtual void draw(HDC& hdc) = 0;
	virtual void update() = 0;
};

class Actor : public GameObject
{
private:
	DIRECTION dir;
	ActorState state;
	Sprite sprite;

public:
	Actor(int x = 0, int y = 0, DIRECTION dir = DIRECTION::D, const WCHAR* filename = NULL) : GameObject(x, y), dir(DIRECTION::D), state(ActorState::IDLE), sprite(filename, 0, 0, 3, 8) { sprite.setRepeat(true); sprite.setFrame(1); }

	void setDirection(DIRECTION dir);
	DIRECTION getDirection() { return dir; }

	void setState(ActorState st);
	ActorState getState() { return state; }

	virtual void draw(HDC& hdc);
	virtual void update();

};

#endif

void initObject();

void releaseObject();
