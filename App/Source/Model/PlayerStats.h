#pragma once

struct PlayerStats
{
	float currentHealth;
	float maxHealth;

	float fireRate = 0.6f;
	float speed = 50.0f;

	float expAttractRange = 150.0f;
	float expPickupRange = 60.0f;
};