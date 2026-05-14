#include "ExperienceCube.h"
#include "raymath.h"

ExperienceCube::ExperienceCube()
{
}

ExperienceCube::~ExperienceCube()
{
}

void ExperienceCube::Init(Vector2 position, Vector2 velocity, Vector2* target, int amount)
{
	_position = position;
	_velocity = velocity;
	_active = true;
	_target = target;
	_amount = amount;
}

void ExperienceCube::Update(float deltaTime)
{
	if (!_active || _target == nullptr)
		return;


	Vector2 toTarget = Vector2Subtract(*_target, _position);
	float dist = Vector2Length(toTarget);


	_velocity = Vector2Scale(_velocity, _attractSpeed * deltaTime);
	if (dist < _attractRange && dist > 0.0001f)
	{

		Vector2 dir = Vector2Scale(toTarget, 1.0 / dist);
		float strength = 1.0f - (dist / _attractRange);
		Vector2 attraction = Vector2Scale(dir, strength * _attractSpeedMax);
		_velocity = Vector2Lerp(_velocity, attraction, deltaTime);
		_position = Vector2Add(_position, Vector2Scale(_velocity, deltaTime));
	}

}

void ExperienceCube::Draw()
{
	if (!_active)
		return;

	DrawPolyLinesEx(_position, 4, _size, GetRandomValue(0,360),5, _color);
}



bool ExperienceCube::GetActive()
{
	return _active;
}

bool ExperienceCube::GetActive() const
{
	return _active;
}

Vector2 ExperienceCube::GetPosition()
{
	return _position;
}

float ExperienceCube::GetSize()
{
	return _size;
}

int ExperienceCube::GetExpValue()
{
	if (_amount <= 0)
		return 0;

	return _amount;
}


void ExperienceCube::SetActive(bool active)
{
	_active = active;
}

void ExperienceCube::SetAmount(int amount)
{
	_amount = amount;
}