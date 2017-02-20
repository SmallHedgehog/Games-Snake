#pragma once

// Snake表示蛇类，初始时只有一个蛇头
// 用vector来保存蛇身

#include <vector>
#include "Square.h"

using namespace std;

class Snake
{
public:
	Snake(int x, int y, SDL_Texture* texture);
	~Snake(void);

public:
	// 向蛇尾添加square
	void push(Square* square);
	//vector<Square*>
	void Draw(SDL_Renderer* renderer);

public:
	// 存储蛇身数据
	vector<Square*> squares;

	SDL_Texture* texture;
};

