#include <iostream>

#include "raylib.h"

#include "Model/Enemy.h"
#include <Model/Player.h>
#include <GUI/Bar.h>
#include <GUI/Panel.h>
#include <GUI/Button.h>
#include <GUI/ButtonToggle.h>
#include <CommonInclude.h>



const float ENEMY_RANDOM_ANGLE = 30 * DEG2RAD;


int main(void)
{
	const int screenWidth = 1920;
	const int screenHeight = 1080;

    InitWindow(screenWidth, screenHeight, "My game");

	Enemy enemy;
    Player player;

    Vector2 size_level = Vector2{ 1700, 20 };
    Vector2 pos_level = { (float)(GetScreenWidth() / 2 - size_level.x / 2), (float)(GetScreenHeight() - 100) };

    Vector2 panel_size = Vector2{ 300, 400 };
    Vector2 panel_pos = Vector2{ 500, 200 };

    Vector2 button_size = Vector2{ 30, 30 };
    Vector2 button_pos = Vector2{ panel_pos.x, panel_pos.y + panel_size.y + 20 };

	Panel panel = Panel(panel_pos, panel_size, "Item", "This is the item");
    ButtonToggle button = ButtonToggle(button_pos, button_size, "x");
	Bar expBar = Bar(pos_level, size_level, MAIN_GOOD_COLOR, 40, 100);

    SetTargetFPS(60);

	enemy.Init({ screenWidth / 2.0f, screenHeight / 2.0f }, { 1, 1});

    Vector2 position = { screenWidth / 2.0f, screenHeight / 2.0f };
    Vector2 line[2] = { {1, 1}, {1, 1} };

    while (!WindowShouldClose())
    {
		float deltaTime = GetFrameTime();
        // Update
        // --------------------------------------------------
      /*  if (IsMouseButtonDown(MOUSE_LEFT_BUTTON))
        {
			Vector2 center = { screenWidth / 2.0f, screenHeight / 2.0f };
		    position = GetMousePosition();
          
            Vector2 velocity = Vector2Subtract(center, position);
			velocity = Vector2Normalize(velocity);
            velocity = Vector2Rotate(velocity, GetRandomValue(-ENEMY_RANDOM_ANGLE, ENEMY_RANDOM_ANGLE));





            line[0] = Vector2Add(position, Vector2Rotate(Vector2Scale(velocity, 100), ENEMY_RANDOM_ANGLE));
            line[1] = Vector2Add(position, Vector2Rotate(Vector2Scale(velocity, 100), -ENEMY_RANDOM_ANGLE));

            enemy.Init(position, velocity);
        }*/

        if (IsKeyPressed(KEY_RIGHT))
        {
			expBar.SetValue(expBar.GetValue() + 10);
        }
        if (IsKeyPressed(KEY_LEFT))
        {
            expBar.SetValue(expBar.GetValue() - 10);
        }

        player.Update(deltaTime);
		enemy.Update(deltaTime);
        expBar.Update(deltaTime);
        panel.Update(deltaTime);
        button.Update(deltaTime);

        UpdateProjectiles(deltaTime);
        DrawProjectiles();

        // Draw
        // --------------------------------------------------
        ClearBackground(MAIN_BACKGROUND_COLOR);
        BeginDrawing();
        enemy.Draw();
        player.Draw();
		expBar.Draw();
		panel.Draw();
        button.Draw();
        EndDrawing();
        // --------------------------------------------------
    }

    CloseWindow();

    return 0;
}
