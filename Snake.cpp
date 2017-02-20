#include "stdafx.h"
#include "Snake.h"


Snake::Snake(int x, int y, SDL_Texture* texture):
	texture(texture)
{
	// ÃÌº”…ﬂÕ∑
	Square* square = new Square(x, y, texture);
	squares.push_back(square);
}

void Snake::push(Square* square)
{
	squares.push_back(square);
}

void Snake::Draw(SDL_Renderer* renderer)
{
	for (int i=0; i<squares.size(); ++i)
	{
		if (squares[i])
			squares[i]->Draw(renderer);
	}
}

Snake::~Snake(void)
{
	for (int i=0; i<squares.size(); ++i)
	{
		if (squares[i])
			delete squares[i];
	}
	squares.clear();
}
