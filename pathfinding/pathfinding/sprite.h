#ifndef __SPRITE__
#define __SPRITE__
#include "framework.h"
#include "controlTime.h"
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
	int nx;
	int ny;
	TIMER time;
	int delay;
	int frame;
	int startFrame;
	bool playing;
	bool repeat;
	void updateFrame();

public:
	Sprite(const WCHAR* file = NULL, int cx = 0, int cy = 0, int nx = 1, int ny = 1);
	virtual void draw(HDC& hdc, int x, int y);
	int getWidth() { return img->GetWidth(); }
	int getHeigth() { return img->GetHeight(); }

	void setSprite(int cx, int cy, int bx, int by) { Sprite::cx = cx; Sprite::cy = cy, Sprite::bx = bx; Sprite::by = by; }
	void setImage(const WCHAR* file);

	void setXOffset(int n) { cx = bx * n; }
	void setYOffset(int n) { cy = by * n; }

	void setFrame(int n) { frame = n; }
	void setStartFrame(int n) { startFrame = n; }

	void setDelay(int n) { delay = n; }

	void play() { playing = true; }
	void pause() { playing = false; }

	void setRepeat(bool flag) { repeat = flag; }

	~Sprite() { if (img != NULL) delete img; }
};

#endif