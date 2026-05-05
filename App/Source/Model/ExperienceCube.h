#pragma once
#include "raylib.h"
#include <CommonInclude.h>

class ExperienceCube
{
public:
	ExperienceCube();
	~ExperienceCube();

	void Init(Vector2 position, Vector2 velocity, Vector2* target);
	void Update(float deltaTime);
	void Draw();

	bool GetActive();
	Vector2 GetPosition();
	float GetSize();


	void SetActive(bool active);
private:
	Vector2 _position = {0, 0};
	Vector2 _velocity = {0, 0};
	Vector2* _target = nullptr;

	int _amount = 10;
	bool _active = false;
	float _size = 5.0f;
	float _lifetime = 600.0f;

	float _attractRange = 150.0f;
	float _attractSpeed = 60.0f;
	float _attractSpeedMax = 80.0f;

	Color _color = MAIN_GOOD_COLOR;
};