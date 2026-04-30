#include "Enemy.h"

Enemy::Enemy()
{

}

Enemy::~Enemy()
{

}

void Enemy::Init(Vector2 position, Vector2 velocity)
{
	_position = position;
	_velocity = velocity;
	_velocity = Vector2Scale(_velocity, GetRandomValue(1, 5));
	_active = true;
	_rotation = GetRandomValue(0, 360);
	_rotation_speed = GetRandomValue(-50, 50);
}

void Enemy::Update(float deltaTime)
{
	if (!_active)
		return;

	_position = Vector2Add(_position, Vector2Scale(_velocity, deltaTime * 5));
	_rotation = deltaTime * _rotation_speed + _rotation;
}

void Enemy::Draw() {
	if (!_active) 
		return;
	DrawPolyLines(_position, (int)_enemyType, (int)_enemyType * 7, _rotation, WHITE);
}

bool Enemy::GetActive()
{
	return _active;
}

void Enemy::SetActive(bool active)
{
	_active = active;
}

float Enemy::GetSize()
{
	return (float)_enemyType * 7;
}

Vector2 Enemy::GetPosition()
{
	return _position;
}