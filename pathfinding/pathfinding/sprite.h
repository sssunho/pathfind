#ifndef __SPRITE__
#define __SPRITE__
#include "framework.h"
#include <fstream>

using std::wfstream;
using namespace Gdiplus;

class Sprite
{
private:
	Image* img;

protected:
	int cx;
	int cy;
	int bx;
	int by;

public:
	Sprite(WCHAR* file, int cx, int cy, int bx, int by);
	void draw(HDC hdc, int x, int y);
	int getWidth() { return img->GetWidth(); }
	int getHeigth() { return img->GetHeight(); }
	void setSprite(int cx, int cy, int bx, int by) { Sprite::cx = cx; Sprite::cy = cy, Sprite::bx = bx; Sprite::by = by; }
	void setImage(WCHAR* file);
	~Sprite() { if (img != NULL) delete img; }
};

class Animation : public Sprite
{
private:
	bool open;
	wfstream script;

public:
	Animation(WCHAR* path);
	~Animation() { if (script.is_open()) script.close(); }
};

#endif