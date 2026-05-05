#include "CollisionManager.h"
#include "raymath.h"
#include <iostream>

#include "Model/Player.h"
#include "Model/Enemy.h"
#include "Model/Projectile.h"
#include "Model/ExperienceCube.h"


namespace CollisionManager
{
	static bool CircleCollision(Vector2 a, float radiusA, Vector2 b, float radiusB)
	{
		return Vector2Distance(a, b) <= radiusA + radiusB;
	}

	static Vector2 GetDirectionm(Vector2 from, Vector2 to)
	{
		return Vector2Normalize(Vector2Subtract(to, from));
	}

	static void HandleProjectileEnemyCollision(vector<Projectile>& bullets, vector<Enemy>& enemy)
	{
		for (auto& bullet : bullets)
		{
			if (!bullet.alive)
				continue;

			for (auto& enemy : enemy)
			{
				if (!enemy.GetActive())
					continue;

				if (CheckCollisionCircles(bullet.position, bullet.stats.size, enemy.GetPosition(), enemy.GetSize()))
				{
					bullet.Destroy();
					enemy.SetActive(false);
				}
			}
		}
	}

	static void HandlePlayerEnemyCollision(Player& player, vector<Enemy>& enemy)
	{
		for (auto& e : enemy)
		{
			if (!e.GetActive())
				continue;

			if (CheckCollisionCircles(player.GetPosition(), 20, e.GetPosition(), e.GetSize()))
			{
				std::cout << "Player hit!" << std::endl;
				Vector2 direction = GetDirectionm(e.GetPosition(), player.GetPosition());

				float push = 50;

				player.SetPosition(Vector2Add(player.GetPosition(), Vector2Scale(direction, push)));
			}
		}
	}

	static void HandlePlayerExpirienceCollision(Player& player, vector<ExperienceCube>& exp)
	{
		for (auto& e : exp)
		{
			if (!e.GetActive())
				continue;

			if (CheckCollisionCircles(player.GetPosition(), player.GetStats().expPickupRange, e.GetPosition(), e.GetSize()))
			{
				std::cout << "Player picked up exp!" << std::endl;
				e.SetActive(false);
			}
		}
	}


	void Update(Player& player, vector<Enemy>& enemy, vector<Projectile>& bullets, vector<ExperienceCube>& exp, float deltaTime)
	{
		HandleProjectileEnemyCollision(bullets, enemy);
		HandlePlayerEnemyCollision(player, enemy);
		HandlePlayerExpirienceCollision(player, exp);
	}

}