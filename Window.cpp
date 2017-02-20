#include "stdafx.h"
#include "Window.h"
#include <Windows.h>
#include <stdint.h>


Window::Window(void):
	win(nullptr), renderer(nullptr), Font(nullptr),
	bg(nullptr)
{
	// 初始化所有纹理数据
	for (int i=0; i<TEXTURE_COUNTS; ++i)
	{
		textures[i] = nullptr;
	}
	
	// 初始化SDL
	if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
	{
		cout << "SDL_Init Error: " << SDL_GetError() << endl;
		exit(1);
	}
	// 初始化图像库
	IMG_Init(IMG_INIT_PNG | IMG_INIT_JPG);
	// 初始化字体库
	TTF_Init();
	Font = TTF_OpenFont("res/SourceSansPro-Regular.ttf", 20);

	// 创建窗口
	win = SDL_CreateWindow(WINDOW_CAPTION, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_SHOWN);
	// 创建渲染器(使用硬件加速渲染和与当前显示器同步)
	renderer = SDL_CreateRenderer(win, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

	// 初始化随机数种子
	srand(unsigned int (time(0)));

	// 加载资源文件
	LoadResouceFile();
	// 初始化游戏对象
	Init();
}

void Window::Init()
{
	game = new Game(textures, renderer);
}

void Window::ResetGame()
{
	// do something
}

// 进入消息循环
void Window::Start()
{
	SDL_Event event;
	bool gameRunning = true;
	while (gameRunning)
	{
		if (SDL_PollEvent(&event))
		{
			switch (event.type)
			{
			case SDL_QUIT:
				gameRunning = false;
				break;
			case SDL_KEYDOWN:	// 键盘按键事件
				{
					switch (event.key.keysym.sym)
					{
					case SDLK_UP:
						game->HandleInput(UP);
						break;
					case SDLK_LEFT:
						game->HandleInput(LEFT);
						break;
					case SDLK_RIGHT:
						game->HandleInput(RIGHT);
						break;
					case SDLK_DOWN:
						game->HandleInput(DOWN);
						break;
					case SDLK_SPACE:
						{
							// do something
						}
						break;
					default:
						break;
					}
				}
				break;
			default:
				break;
			}
		}

		Update();
		Refresh();
	}
}

// refresh到屏幕上
void Window::Refresh()
{
	SDL_RenderPresent(renderer);
}

// 更新图像位置信息
void Window::Update()
{
	game->MoveSelf();
	SDL_RenderClear(renderer);

	// 绘制背景图片
	int width = 0, height = 0;
	SDL_QueryTexture(bg, NULL, NULL, &width, &height);
	SDL_Rect rect = {
		0, 0, width, height
	};
	SDL_RenderCopy(renderer, bg, NULL, &rect);

	game->Draw();
}

void Window::LoadResouceFile()
{
	// 加载背景纹理
	bg = Load_image("res/background.png");
	textures[NORMAL_BALL] = Load_image("res/normal.png");
	textures[HARM_BALL] = Load_image("res/harm_ball.png");
	textures[GOOD_BALL] = Load_image("res/good_ball.png");
	textures[HEAD] = Load_image("res/head.png");
	textures[TAIL] = Load_image("res/tail.png");
}

// 加载图像纹理
SDL_Texture* Window::Load_image(std::string FilePath)
{
	SDL_Surface* picture = nullptr;

	picture = IMG_Load(FilePath.c_str());
	// 设置背景透明
	Uint32 colorkey = SDL_MapRGB(picture->format, 0, 0, 0);
	SDL_SetColorKey(picture, SDL_TRUE, colorkey);

	SDL_Texture* result = SDL_CreateTextureFromSurface(renderer, picture);
	SDL_FreeSurface(picture);

	return result;
}

SDL_Texture* Window::Draw_text(std::string message)
{
	SDL_Color color = { 0, 0, 0 };
	SDL_Surface* surface = TTF_RenderText_Blended(Font, message.c_str(), color);
	SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);

	SDL_FreeSurface(surface);

	return texture;
}

Window::~Window(void)
{
	TTF_CloseFont(Font);
	TTF_Quit();
	// 释放纹理资源
	SDL_DestroyTexture(bg);
	for (int i=0; i<TEXTURE_COUNTS; ++i)
	{
		SDL_DestroyTexture(textures[i]);
	}
	// 释放渲染器资源
	SDL_DestroyRenderer(renderer);
	// 销毁窗口
	SDL_DestroyWindow(win);
	SDL_Quit();
}
