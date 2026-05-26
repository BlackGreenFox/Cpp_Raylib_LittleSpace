#pragma once
#include "raylib.h"
#include "Projectile.h"
#include "CommonInclude.h"

enum class TrajectoryKind
{
	Straight,
	Wave
};

struct Loadout
{
	Color playerColor = MAIN_BAD_COLOR;
	float playerSpeed = 200;
	float playerSize = 80;
	float playerMaxHealth = 100;

	float fireRate = 0.20f;

	float expAttractRange = 150.0f;
	float expPickupRange = 60;


	ShotType shotType = ShotType::Bullet;
	float bulletSpeed = 4000;
	float bulletSize = 555;
	float bulletDamage = 10;
	float bulletDistance = 1400;
	Color bulletColor = WHITE;


	int shootCount = 3;
	float shootSpread = 15;


	bool shootBackwards = false;
	bool explodes = false;
	bool homing = false;
	bool splits = false;


	float explosionRadius = 500;
	float explosionDamage = 210;
	float homingTurnRate = 20;
	int splitCount = 3;

	TrajectoryKind trajectory = TrajectoryKind::Straight;
};