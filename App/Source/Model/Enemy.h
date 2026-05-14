#pragma once
#include "raylib.h"
#include "raymath.h"

typedef enum ENEMY_TYPE
{
	TRIANGLE = 3,
	SQUARE = 4,
	SIX_SIDES = 6,
	EIGHT_SIDES = 8,
	NINE_SIDES = 9
}ENEMY_TYPE;


class Enemy
{
public:
	Enemy();
	~Enemy();

	void Init(Vector2 position, Vector2 velocity, ENEMY_TYPE type);
	void Update(float deltaTime);
	void Draw();

	// Get ^ Set
	bool GetActive();
	bool GetActive() const;
	bool GetOutSide();
	bool GetOutSide() const;
	ENEMY_TYPE GetEnemyType();
	ENEMY_TYPE GetEnemyType() const;

	float GetSize();
	Vector2 GetPosition();


	void SetActive(bool active);
	void SetOutSide(bool outside);


private:
	bool _active = false;
	bool _outside = false;
	ENEMY_TYPE _enemyType = SIX_SIDES;

	Vector2 _position;
	Vector2 _velocity;

	float _rotation_speed;
	float _rotation;
};