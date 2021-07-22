#include "sprite.h"

Sprite::Sprite(const WCHAR* file, int cx, int cy, int nx, int ny) 
	: cx(cx), cy(cy), nx(nx), ny(ny), time(), delay(50), frame(0), playing(false), repeat(false)
{
	if (nx <= 0)
		nx = 1;
	if (ny <= 0)
		ny = 1;

	if (file == NULL)
	{
		img = NULL;
		bx = 0; by = 0;
	}
	else
	{
		img = Image::FromFile(file);
		if (img->GetLastStatus() != Ok)
		{
			img = NULL;
			bx = 0; by = 0;
		}
		else
		{
			bx = img->GetWidth() / nx;
			by = img->GetHeight() / ny;
		}
	}
}

void Sprite::setImage(const WCHAR* file)
{
	if (img != NULL)
		delete img;
	img = Image::FromFile(file);
	if (img->GetLastStatus() != Ok)
		img = NULL;
	
}

void Sprite::draw(HDC& hdc, int x, int y)
{
	if (img == NULL)
		return;

	Graphics g(hdc);
	g.DrawImage(img, x - bx/2, y - by/2, cx + frame * bx, cy, bx, by, UnitPixel);
	if (playing)
		updateFrame();
}

void Sprite::updateFrame()
{
	if (time.getElapsedTime() > delay)
	{
		time.set();
		frame++;
		if (frame >= nx)
		{
			frame = 0;
			if (!repeat)
				playing = false;
		}
	}
}