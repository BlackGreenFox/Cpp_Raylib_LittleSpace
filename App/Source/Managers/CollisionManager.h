#pragma once
#include "raylib.h"
#include <vector>


class Player;
class Enemy;
class ExperienceCube;
struct Projectile;

using std::vector;

namespace CollisionManager
{
	void Update(Player& player, vector<Enemy>& enemy, vector<Projectile>& bullets, vector<ExperienceCube>& exp, float deltaTime);
}


