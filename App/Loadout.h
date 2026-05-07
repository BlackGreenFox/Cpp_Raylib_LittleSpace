#pragma once
#include "raylib.h"
#include "Projectile.h"

struct Loadout
{
	float playerSpeed = 200;
	float playerSize = 20;
	float playerMaxHealth = 100;

	float fireRate = 0.5f;

	float expAttractRange = 150.0f;
	float expPickupRange = 60;


	ShotType shotType = ShotType::Bullet;
	float bulletSpeed = 400;
	float bulletSize = 5;
	float bulletDamage = 10;
	float bulletDistance = 100;
	Color bulletColor = WHITE;


	int shootCount = 1;
	float shootSpread = 5;


	bool shootBackwards = false;
	bool explodes = false;
	bool homing = false;
	bool splits = false;


	float explosionRadius = 50;
	float explosionDamage = 20;
	float homingTurnRate = 20;
	int splitCount = 3;

};