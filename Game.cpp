#include "stdafx.h"
#include "Game.h"


Game::Game(SDL_Texture* textures[], SDL_Renderer* renderer):
	renderer(renderer), snake(nullptr), gf(nullptr)
{
	this->textures = textures;
	snake = new Snake((rand() % PER_ROW) * (RADIUS * 2) + 12, 
		(rand() % PER_COL) * (RADIUS * 2) + 12, textures[HEAD]);
	// 物品
	gf = new Square((rand() % PER_ROW) * (RADIUS * 2) + 12,
		(rand() % PER_COL) * (RADIUS * 2) + 12, textures[NORMAL_BALL]);
	// 物品是否与蛇的坐标相同，如果相同就将物品坐标改变
	IsSame();
	// 记录方向
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

// 处理键盘输入事件
void Game::HandleInput(Direction dir)
{
	direction = dir;
	MoveSelf();
}

// 处理蛇的移动
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
		// 判断是否越界（屏幕）
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

		// 蛇头是否与蛇身发生碰撞
		if (IsCollisions(_x, _y))
			printf("Faliure.");

		// 蛇头是否与食物发生碰撞
		if (IsCollisioned())
		{
			snake->squares.push_back(new Square(snake->squares[int(snake->squares.size() - 1)]->getCenterX(),
				snake->squares[int(snake->squares.size() - 1)]->getCenterY(), textures[TAIL]));
			delete gf;
			// 物品
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

// 判断蛇头是否与食物发生碰撞
bool Game::IsCollisioned()
{
	// 临时变量，代码清晰
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

// 判断蛇头是否与蛇身发生碰撞
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

// 随机化食物或道具位置时，检测食物或道具是否与蛇身的每个坐标相同
// 如果相同接着随机化食物或道具位置
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
