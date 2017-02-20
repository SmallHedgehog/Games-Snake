#pragma once

// ��Ϸ������Game
// �洢��Ϸ�е�������Ϸ�顢��ײ�����߼�

#include <time.h>
#include <math.h>
#include <vector>
#include <SDL_ttf.h>
#include "Defines.h"
#include "Enums.h"
#include "Snake.h"

using namespace std;

class Game
{
public:
	Game(SDL_Texture* texture[], SDL_Renderer* renderer);
	~Game(void);

public:
	void Draw();
	// ������������¼�
	void HandleInput(Direction dir);
	// �����ߵ��ƶ�
	void Move();
	void MoveSelf();

// ������ײ����߼�
public:
	// �ж���ͷ�Ƿ�����������ײ
	bool IsCollisions(int _x, int _y);
	// �ж���ͷ�Ƿ���ʳ�����߷�����ײ
	bool IsCollisioned();
	// �����ʳ������λ��ʱ�����ʳ�������Ƿ��������ÿ��������ͬ
	// �����ͬ���������ʳ������λ��
	void IsSame();
	
private:
	Snake* snake;
	// ʳ������
	Square* gf;
	// ��Ϸ��������Ϸ���������
	SDL_Texture** textures;
	// SDL��Ⱦ��
	SDL_Renderer* renderer;

	// ��¼���·�����ķ���
	Direction direction;
};

