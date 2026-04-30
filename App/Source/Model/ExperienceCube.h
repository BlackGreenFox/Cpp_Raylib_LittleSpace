#pragma once
#include "raylib.h"
#include "raymath.h"
#include "Player.h"

class ExperienceCube
{
public:
	ExperienceCube();
	~ExperienceCube();

	void Init(Vector2 position, Vector2 velocity, Player* target);
	void Update(float deltaTime);
	void Draw();

	bool GetActive() const;
	Vector2 GetPosition() const;
	void SetActive(bool active);
	float GetSize() const;

private:
	Vector2 _position;
	Vector2 _velocity;

	Player* _target;


	int _amount = 10;

	bool _active = false;
	float _lifetime = 600.0f;
	float _attractSpeed = 60.0f;
	float _attractSpeedMax = 80.0f;


	float _size = 5.0f;
	Color _color = MAIN_GOOD_COLOR;
};