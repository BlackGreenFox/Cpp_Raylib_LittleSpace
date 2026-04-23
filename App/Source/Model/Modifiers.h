#pragma once
#include "Projectile.h"
#include "PlayerStats.h"

struct Modifier
{
	virtual ~Modifier() = default;
	
	virtual void Apply(Projectile& p) {}
	virtual void Apply(PlayerStats& p) {}
};


struct MinigunModifier : Modifier
{
	float spreadDeg = 10;
	float fireRateBonus = 0.05f;


	void Apply(Projectile& p) override
	{
		p.stats.speed += 200;
		p.stats.damage += 0.5f;

		float angle = float(GetRandomValue(-spreadDeg, spreadDeg));
		p.direction = Vector2Rotate(p.direction, angle * DEG2RAD);
	}

	void Apply(PlayerStats& p) override
	{
		p.fireRate -= fireRateBonus;
	}
};