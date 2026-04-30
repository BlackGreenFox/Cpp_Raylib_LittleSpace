#pragma once
#include "raylib.h"
#include "raymath.h"
#include "Projectile.h"
#include "Item.h"
#include <CommonInclude.h>

class Player {
public:
	Player();
	~Player();

	void Update(float deltaTime);
	void Draw();

	Vector2 GetPosition();
	void SetPosition(Vector2 value);

	PlayerStats GetStats() const;

private:
	void Shoot();

	PlayerStats stats;
	ShotStats shootStats;

	// For gun
	float shootCooldown = 0;

	//

	Vector2 position;
	Vector2 velocity;
	float rotate;
};