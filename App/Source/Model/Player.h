#pragma once
#include "raylib.h"
#include "raymath.h"

#include <vector>

#include <CommonInclude.h>
#include "Projectile.h"
#include <Loadout.h>




class Player {
public:
	Player();
	~Player();

	void Init(Vector2 position);
	void Update(float deltaTime);
	void Draw();


	void TakeDamage(float amount);
	void Heal(float amount);

	





	void SetProjectileBuffer(std::vector<Projectile>* ptrBuffer);

	void SetPosition(Vector2 value);



	Loadout& GetLoadout();
	Loadout& GetLoadout() const;

	Vector2 GetPosition();
	Vector2 GetPosition() const;
	Vector2* GetPositionPtr();

	float GetCurrentHeath();
	float GetCurrentHeath() const;

	float GetSize();
	float GetSize() const;
	
	float GetExpAttractRange();
	float GetExpAttractRange() const;

	float GetExpPickupRange();
	float GetExpPickupRange() const;

private:
	void Shoot();

	Loadout _loadout;

	float _currentHeath = 100;
	Vector2 _position;
	Vector2 _velocity;
	float _rotate;


	float _shootCooldown = 0.0f;
	float _chargeCooldown = 0.0f;
	bool _isLaserAcrive = false;


	std::vector<Projectile>* _projectBuffer = nullptr;
};