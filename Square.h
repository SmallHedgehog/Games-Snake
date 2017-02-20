#pragma once

// Square类表示蛇中的每一个小部分
// Square类还可用于物品道具和食物道具上

#include <SDL.h>
#include "Defines.h"

class Square
{
public:
	Square(int x, int y, SDL_Texture* texture);
	~Square(void);

// 设置和获取Square属性的方法
public:
	void setCenterX(int x) { center_x = x; }
	void setCenterY(int y) { center_y = y; }
	int getCenterX() const { return this->center_x; }
	int getCenterY() const { return this->center_y; }

public:
	void Draw(SDL_Renderer* renderer);

private:
	// 存储Square的中心坐标
	int center_x;
	int center_y;
	// 存储Square的纹理数据
	SDL_Texture* texture;
};

