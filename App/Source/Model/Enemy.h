#pragma once
#include "raylib.h"
#include "raymath.h"

typedef enum ENEMY_TYPE
{
	TRIANGLE = 3,
	SQUARE = 4,
	SIX_SIDES = 6
}ENEMY_TYPE;


class Enemy
{
public:
	Enemy();
	~Enemy();

	void Init(Vector2 position, Vector2 velocity);
	void Update(float deltaTime);
	void Draw();

	// Get ^ Set
	bool GetActive();
	float GetSize();
	Vector2 GetPosition();
	void SetActive(bool active);

private:
	bool _active = false;
	ENEMY_TYPE _enemyType = SIX_SIDES;

	Vector2 _position;
	Vector2 _velocity;

	float _rotation_speed;
	float _rotation;
};