#pragma once
#include "raylib.h"
#include <vector>



class Enemy;
class ExperienceCube;
class Player;
struct Projectile;

using std::vector;

namespace CollisionManager
{
	void Update(Player& player, vector<Enemy>& enemy, vector<Projectile>& bullets, float deltaTime);
}


