#pragma once
#include "Projectile.h"
#include "PlayerStats.h"

struct Item
{
	virtual void Apply(ShotStats& stats, ShotType& type)
	{

	}

	virtual void Apply(ShotStats& stats)
	{

	}

	virtual void Apply(PlayerStats& stats)
	{

	}
};

struct ItemLaser : Item 
{
	void Apply(ShotStats& stats, ShotType& type) 
	{
		type = ShotType::Laser;
		stats.color = RED;
	}
};


struct ItemSpeedPack : Item
{
	void Apply(PlayerStats& stats)
	{
		stats.speed += 20;
	}
};