#include <iostream>

#include "GameManager.h"
#include "PlayerScene.h"
#include "Game1Scene.h"
#include "GameOverScene.h"
#define WIDTH 1000
#define HEIGHT 800

int main(int argc, char* argv[])
{
	
	GameManager gameManager("Flappy Mask", 500, 250, WIDTH, HEIGHT);
	Window& window = gameManager.GetWindow();

	gameManager.GetSceneManager()->AddScene("Intro", new PlayerScene(&gameManager));
	gameManager.GetSceneManager()->AddScene("Game", new PlayerScene(&gameManager));
	gameManager.GetSceneManager()->AddScene("Game_Over", new GameOverScene());

	gameManager.GetSceneManager()->SetCurrentScene("Game");

	gameManager.Initialize();
	gameManager.Loop();

	return 0;
}