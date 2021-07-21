#include "sprite.h"

Sprite::Sprite(WCHAR* file, int cx, int cy, int bx, int by) : cx(cx), cy(cy), bx(bx), by(by)
{
	img = Image::FromFile(file);
	if (img->GetLastStatus() != Ok)
		img = NULL;
}

void Sprite::draw(HDC hdc, int x, int y)
{
	if (img != NULL)
	{
		Graphics g(hdc);
		g.DrawImage(img, x, y, cx, cy, bx, by, UnitPixel);
	}
}

void Sprite::setImage(WCHAR* file)
{
	if (img != NULL)
		delete img;
	img = Image::FromFile(file);
	if (img->GetLastStatus() != Ok)
		img = NULL;
	
}