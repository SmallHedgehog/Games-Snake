#pragma once

// 游戏控制类Game
// 存储游戏中的所有游戏块、碰撞检测等逻辑

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
	// 处理键盘输入事件
	void HandleInput(Direction dir);
	// 处理蛇的移动
	void Move();
	void MoveSelf();

// 处理碰撞检测逻辑
public:
	// 判断蛇头是否与蛇身发生碰撞
	bool IsCollisions(int _x, int _y);
	// 判断蛇头是否与食物或道具发生碰撞
	bool IsCollisioned();
	// 随机化食物或道具位置时，检测食物或道具是否与蛇身的每个坐标相同
	// 如果相同接着随机化食物或道具位置
	void IsSame();
	
private:
	Snake* snake;
	// 食物或道具
	Square* gf;
	// 游戏中所有游戏对象的纹理
	SDL_Texture** textures;
	// SDL渲染器
	SDL_Renderer* renderer;

	// 记录按下方向键的反向
	Direction direction;
};

