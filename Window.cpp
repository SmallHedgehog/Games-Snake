#include "stdafx.h"
#include "Window.h"
#include <Windows.h>
#include <stdint.h>


Window::Window(void):
	win(nullptr), renderer(nullptr), Font(nullptr), texture(nullptr),
	bg1(nullptr), bg2(nullptr), bg3(nullptr), game(nullptr)
{
	// ��ʼ��SDL
	if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
	{
		cout << "SDL_Init Error: " << SDL_GetError() << endl;
		exit(1);
	}
	// ��ʼ��ͼ���
	IMG_Init(IMG_INIT_PNG | IMG_INIT_JPG);
	// ��ʼ�������
	TTF_Init();
	Font = TTF_OpenFont("res/SourceSansPro-Regular.ttf", 20);

	// ��������
	win = SDL_CreateWindow(WINDOW_CAPTION, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_SHOWN);
	// ������Ⱦ��(ʹ��Ӳ��������Ⱦ���뵱ǰ��ʾ��ͬ��)
	renderer = SDL_CreateRenderer(win, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

	// ��ʼ�����������
	srand(unsigned int (time(0)));

	// ������Դ�ļ�
	LoadResouceFile();
	// ��ʼ����Ϸ����
	Init();
}

void Window::Init()
{
	game = new Game(renderer, texture, Font);
	game->Init();
}

void Window::ResetGame()
{
	// do something
}

// ������Ϣѭ��
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
			case SDL_KEYDOWN:	// ���̰����¼�
				{
					switch (event.key.keysym.sym)
					{
					case SDLK_UP:		// ��ת��ǰ��Ϸ��
						game->HandleInput(NONE, true);
						break;
					case SDLK_LEFT:
						game->HandleInput(LEFT, false);
						break;
					case SDLK_RIGHT:
						game->HandleInput(RIGHT, false);
						break;
					case SDLK_DOWN:
						game->HandleInput(DOWN, false);
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

// refresh����Ļ��
void Window::Refresh()
{
	SDL_RenderPresent(renderer);
}

// ����ͼ��λ����Ϣ
void Window::Update()
{
	SDL_RenderClear(renderer);

	// ���Ʊ���ͼƬ
	int width = 0, height = 0;
	SDL_QueryTexture(bg2, NULL, NULL, &width, &height);
	SDL_Rect rect = {
		BG2_POSITION_x, BG2_POSITION_y, width, height
	};
	SDL_RenderCopy(renderer, bg2, NULL, &rect);

	SDL_QueryTexture(bg1, NULL, NULL, &width, &height);
	SDL_Rect rect2 = {
		BG1_POSITION_x, BG1_POSITION_y, width, height
	};
	SDL_RenderCopy(renderer, bg1, NULL, &rect2);

	SDL_QueryTexture(bg3, NULL, NULL, &width, &height);
	SDL_Rect rect3 = {
		BG3_POSITION_x, BG3_POSITION_y, width, height
	};
	SDL_RenderCopy(renderer, bg3, NULL, &rect3);

	game->GameBlock_selfMove();
}

void Window::LoadResouceFile()
{
	texture = Load_image("res/square.png");
	bg1 = Load_image("res/bg1.png");
	bg2 = Load_image("res/bg2.png");
	bg3 = Load_image("res/bg3.png");
}

// ����ͼ������
SDL_Texture* Window::Load_image(std::string FilePath)
{
	SDL_Surface* picture = nullptr;

	picture = IMG_Load(FilePath.c_str());
	// ���ñ���͸��
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
	SDL_DestroyTexture(texture);
	SDL_DestroyTexture(bg1);
	SDL_DestroyTexture(bg2);
	SDL_DestroyTexture(bg3);
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(win);
	SDL_Quit();
	
	delete game;
}
