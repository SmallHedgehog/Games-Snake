#pragma once

// Square���ʾ���е�ÿһ��С����
// Square�໹��������Ʒ���ߺ�ʳ�������

#include <SDL.h>
#include "Defines.h"

class Square
{
public:
	Square(int x, int y, SDL_Texture* texture);
	~Square(void);

// ���úͻ�ȡSquare���Եķ���
public:
	void setCenterX(int x) { center_x = x; }
	void setCenterY(int y) { center_y = y; }
	int getCenterX() const { return this->center_x; }
	int getCenterY() const { return this->center_y; }

public:
	void Draw(SDL_Renderer* renderer);

private:
	// �洢Square����������
	int center_x;
	int center_y;
	// �洢Square����������
	SDL_Texture* texture;
};

