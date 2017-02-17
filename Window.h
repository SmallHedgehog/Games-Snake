#pragma once

/*
����Window����Ҫ���𴰿ڵĴ�������ʾ����£�������Դ
*/

#include <SDL_image.h>
#include <iostream>
#include "Game.h"

using namespace std;

class Window
{
public:
	Window(void);
	~Window(void);

public:
	void Start();				// ������Ϣѭ��
	void Refresh();				// refresh����Ļ��
	void Update();				// ����ͼ����Ϣ
	void LoadResouceFile();		// ������Դ�ļ�
	SDL_Texture* Load_image(std::string FilePath);	// ����ͼ��
	void Init();				// ��ʼ����Ϸ����
	void ResetGame();			// ������Ϸ
	SDL_Texture* Draw_text(std::string message);	// ��������

private:
	SDL_Window* win;			// ����
	SDL_Renderer* renderer;		// ��Ⱦ��
	SDL_Texture* bg1;			// ��������
	SDL_Texture* bg2;
	SDL_Texture* bg3;
	SDL_Texture* texture;		// ��������
	TTF_Font* Font;				// ����

	Game* game;					// ��Ϸ�����
};

