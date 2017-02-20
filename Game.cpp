#include "stdafx.h"
#include "Game.h"


Game::Game(SDL_Texture* textures[], SDL_Renderer* renderer):
	renderer(renderer), snake(nullptr), gf(nullptr)
{
	this->textures = textures;
	snake = new Snake((rand() % PER_ROW) * (RADIUS * 2) + 12, 
		(rand() % PER_COL) * (RADIUS * 2) + 12, textures[HEAD]);
	// ��Ʒ
	gf = new Square((rand() % PER_ROW) * (RADIUS * 2) + 12,
		(rand() % PER_COL) * (RADIUS * 2) + 12, textures[NORMAL_BALL]);
	// ��Ʒ�Ƿ����ߵ�������ͬ�������ͬ�ͽ���Ʒ����ı�
	IsSame();
	// ��¼����
	direction = NONE;
}

void Game::Draw()
{
	for (int i=0; i<snake->squares.size(); ++i)
	{
		snake->squares[i]->Draw(renderer);
	}
	gf->Draw(renderer);
}

// ������������¼�
void Game::HandleInput(Direction dir)
{
	direction = dir;
	MoveSelf();
}

// �����ߵ��ƶ�
void Game::Move()
{
	for (int i=snake->squares.size()-1; i>0; --i)
	{
		snake->squares[i]->setCenterX(snake->squares[i-1]->getCenterX());
		snake->squares[i]->setCenterY(snake->squares[i-1]->getCenterY());
	}
}

void Game::MoveSelf()
{
	static int x = 0;
	static int y = 0;
	static int DECRESE = TIME_INTERVAL;

	switch (direction)
	{
	case LEFT:
		x = -24;
		y = 0;
		break;
	case RIGHT:
		x = 24;
		y = 0;
		break;
	case DOWN:
		x = 0;
		y = 24;
		break;
	case UP:
		x = 0;
		y = -24;
		break;
	case NONE:
		break;
	default:
		break;
	}

	DECRESE--;
	if (DECRESE == 0)
	{
		// �ж��Ƿ�Խ�磨��Ļ��
		int _x = snake->squares[0]->getCenterX() + x;
		int _y = snake->squares[0]->getCenterY() + y;
		if (_x < RADIUS || _x > (WINDOW_WIDTH - RADIUS))
		{
			if (_x < RADIUS)
				_x = WINDOW_WIDTH - RADIUS;
			else
				_x = RADIUS;
		}
		if (_y < RADIUS || _y > (WINDOW_HEIGHT - RADIUS))
		{
			if (_y < RADIUS)
				_y = WINDOW_HEIGHT - RADIUS;
			else
				_y = RADIUS;
		}

		// ��ͷ�Ƿ�����������ײ
		if (IsCollisions(_x, _y))
			printf("Faliure.");

		// ��ͷ�Ƿ���ʳ�﷢����ײ
		if (IsCollisioned())
		{
			snake->squares.push_back(new Square(snake->squares[int(snake->squares.size() - 1)]->getCenterX(),
				snake->squares[int(snake->squares.size() - 1)]->getCenterY(), textures[TAIL]));
			delete gf;
			// ��Ʒ
			gf = new Square((rand() % PER_ROW) * (RADIUS * 2) + 12,
				(rand() % PER_COL) * (RADIUS * 2) + 12, textures[rand() % 3]);
			IsSame();
		}

		Move();

		snake->squares[0]->setCenterX(_x);
		snake->squares[0]->setCenterY(_y);
		DECRESE = TIME_INTERVAL;
	}
}

// �ж���ͷ�Ƿ���ʳ�﷢����ײ
bool Game::IsCollisioned()
{
	// ��ʱ��������������
	int head_x = snake->squares[0]->getCenterX();
	int head_y = snake->squares[0]->getCenterY();

	int gf_x = gf->getCenterX();
	int gf_y = gf->getCenterY();

	if (abs(head_x - gf_x) < RADIUS * 2 &&
		abs(head_y - gf_y) < RADIUS * 2)
	{
		return true;
	}
	
	return false;
}

// �ж���ͷ�Ƿ�����������ײ
bool Game::IsCollisions(int _x, int _y)
{
	for (int i=1; i<snake->squares.size(); ++i)
	{
		int x = snake->squares[i]->getCenterX();
		int y = snake->squares[i]->getCenterY();
		if (abs(_x - x) < RADIUS * 2 &&
			abs(_y - y) < RADIUS * 2)
		{
			return true;
		}
	}
	return false;
}

// �����ʳ������λ��ʱ�����ʳ�������Ƿ��������ÿ��������ͬ
// �����ͬ���������ʳ������λ��
void Game::IsSame()
{
	while (1)
	{
		bool sign = false;
		for (int i=0; i<snake->squares.size(); ++i)
		{
			if (gf->getCenterX() == snake->squares[i]->getCenterX() &&
				gf->getCenterY() == snake->squares[i]->getCenterY())
			{
				gf->setCenterX((rand() % PER_ROW) * (RADIUS * 2) + 12);
				gf->setCenterY((rand() % PER_COL) * (RADIUS * 2) + 12);
				sign = true;
				break;
			}
		}
		if (!sign)
			break;
	}
}

Game::~Game(void)
{
	if (snake)
		delete snake;
	if (gf)
		delete gf;
}
