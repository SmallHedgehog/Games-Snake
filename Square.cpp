#include "stdafx.h"
#include "Square.h"


Square::Square(int x, int y, SDL_Texture* texture):
	texture(texture)
{
	center_x = x;
	center_y = y;
}

// ªÊ÷∆Square
void Square::Draw(SDL_Renderer* renderer)
{
	SDL_Rect rect = {
		center_x - RADIUS, center_y - RADIUS, RADIUS*2, RADIUS*2
	};
	SDL_RenderCopy(renderer, texture, NULL, &rect);
}

Square::~Square(void)
{
	// nothing to do
}
