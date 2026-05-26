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

	float GetMaxHealth();
	float GetMaxHealth() const;

	float GetCurrentHealth();
	float GetCurrentHealth() const;

	float GetSize();
	float GetSize() const;
	
	float GetExpAttractRange();
	float GetExpAttractRange() const;

	float GetExpPickupRange();
	float GetExpPickupRange() const;

private:
	void HandlerShooting(float deltaTime);
	void HandlerMovement(float deltaTime);

	void FireLazer(float angle);
	void FireBullet(float angle);

	void DestroyOwner();

	Loadout _loadout;

	float _currentHeath = 100;
	Vector2 _position;
	Vector2 _velocity;
	float _rotate;
	bool _isAlive = true;

	float _shootCooldown = 0.0f;
	float _chargeCooldown = 0.0f;
	float _chaergeProgress = 0.0f;
	bool _isLaserAcrive = false;


	std::vector<Projectile>* _projectBuffer = nullptr;

	int _screenWidth = 800;
	int _screenHeight = 600;
};