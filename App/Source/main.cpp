#include "raylib.h"
#include "MAnagers/GameManager.h"
#include "CommonInclude.h"

int main()
{
	int screenWidth = 1920;
	int screenHeight = 1080;


	InitWindow(screenWidth, screenHeight, "Raylib - Top Down Shooter");

	GameManager gameManager;
	gameManager.Init(screenWidth, screenHeight);


	while (!WindowShouldClose())
	{
		float deltaTime = GetFrameTime();
	
		gameManager.Update(deltaTime);
	
		BeginDrawing();
	
		ClearBackground(MAIN_BACKGROUND_COLOR);
		gameManager.Draw();

		EndDrawing();
	}

	CloseWindow();
	return 0;
}