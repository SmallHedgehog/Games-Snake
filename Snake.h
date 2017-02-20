#pragma once

// Snake��ʾ���࣬��ʼʱֻ��һ����ͷ
// ��vector����������

#include <vector>
#include "Square.h"

using namespace std;

class Snake
{
public:
	Snake(int x, int y, SDL_Texture* texture);
	~Snake(void);

public:
	// ����β���square
	void push(Square* square);
	//vector<Square*>
	void Draw(SDL_Renderer* renderer);

public:
	// �洢��������
	vector<Square*> squares;

	SDL_Texture* texture;
};

