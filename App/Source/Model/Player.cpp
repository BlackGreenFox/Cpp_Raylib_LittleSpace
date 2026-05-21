#include "Player.h"


Player::Player() 
{

}

Player::~Player() 
{

}

void Player::Init(Vector2 position) 
{
	_position = position;
}

void Player::Shoot()
{
	if (!_projectBuffer)
		return;

	ShotType type = ShotType::Bullet;

	int count = 1;

	switch (type)
	{
	case ShotType::Bullet:
		for (int i = 0; i < count; i++)
		{
			Projectile p;
			p.position = _position;
			p.velocity.x = cosf(_rotate * DEG2RAD);
			p.velocity.y = sinf(_rotate * DEG2RAD);
			p.velocity = Vector2Rotate(p.velocity, (float)GetRandomValue(-25, 25) * DEG2RAD);
			p.stats.speed = _loadout.bulletSpeed;
			p.stats.damage = _loadout.bulletDamage;
			p.stats.distance = _loadout.bulletDistance;
			p.stats.size = _loadout.bulletSize;
			p.stats.color = _loadout.bulletColor;
			StraightTrajectory* trajectory = new StraightTrajectory;
			//trajectory->center = &this->position;
			p.trajectory = trajectory;
			p.type = type;
			p.Spawn();
			_projectBuffer->push_back(p);
		}
		break;
	case ShotType::Laser:
		if (_projectBuffer->empty())
		{
			Projectile p;
			p.position = _position;
			p.ownerPos = &this->_position;     
			p.ownerRotation = &this->_rotate;


			p.velocity.x = cosf(_rotate * DEG2RAD);
			p.velocity.y = sinf(_rotate * DEG2RAD);
			StraightTrajectory* trajectory = new StraightTrajectory;
			//trajectory->center = &this->position;
			p.trajectory = trajectory;

			p.stats.speed = _loadout.bulletSpeed;
			p.stats.damage = _loadout.bulletDamage;
			p.stats.distance = _loadout.bulletDistance;
			p.stats.size = _loadout.bulletSize;
			p.stats.color = _loadout.bulletColor;
			p.type = type;
			p.Spawn();
			_projectBuffer->push_back(p);
		}
		else
		{
			//for (auto& p : _projectBuffer)
			//{
			//	if (p.type == ShotType::Laser) {
			//		p.velocity.x = cosf(rotate * DEG2RAD);
			//		p.velocity.y = sinf(rotate * DEG2RAD);
			//	}
			//}
		}
		break;
	default:
		break;
	}
	
}

void Player::Update(float deltaTime) 
{

	_shootCooldown -= deltaTime;

	if (IsMouseButtonDown(MOUSE_LEFT_BUTTON) )
	{
		Shoot();

	}


	if (IsKeyDown(KEY_W))
	{
		_velocity.y = -1;
	}
	else if (IsKeyDown(KEY_S))
	{
		_velocity.y = 1;
	}
	else
	{
		_velocity.y = 0;
	}

	if (IsKeyDown(KEY_A))
	{
		_velocity.x = -1;
	}
	else if (IsKeyDown(KEY_D))
	{
		_velocity.x = 1;
	}
	else
	{
		_velocity.x = 0;
	}


	if (_velocity.x != 0 || _velocity.y != 0)
	{
		_velocity = Vector2Scale(_velocity, _loadout.playerSpeed * deltaTime);
		_position = Vector2Add(_position, _velocity);
	}


	_rotate = atan2f(GetMouseY() - _position.y, GetMouseX() - _position.x);
	_rotate = _rotate * RAD2DEG;


}

void Player::Draw() 
{
	float angleStep = 360.0f / 3.0f;
	float smallRadius = 20.0f;
	float offset = 60.0f;

	Vector2 leftPos = {
		_position.x + cosf(DEG2RAD * (_rotate + angleStep)) * offset,
		_position.y + sinf(DEG2RAD * (_rotate + angleStep)) * offset
	};


	Vector2 rightPos = {
		_position.x + cosf(DEG2RAD * (_rotate - angleStep)) * offset,
		_position.y + sinf(DEG2RAD * (_rotate - angleStep)) * offset
	};

	DrawPolyLinesEx(_position, 3, _loadout.playerSize, _rotate, 15.0f, _loadout.playerColor);
	DrawPolyLinesEx(leftPos, 3, smallRadius, _rotate, 15.0f, WHITE);
	DrawPolyLinesEx(rightPos, 3, smallRadius, _rotate, 15.0f, WHITE);

	//DrawCircleLines(position.x,position.y, stats.expAttractRange, WHITE);
}


void Player::SetProjectileBuffer(std::vector<Projectile>* ptrBuffer)
{
	_projectBuffer = ptrBuffer;
}




Loadout& Player::GetLoadout()
{
	return _loadout;
}




Vector2 Player::GetPosition()
{
	return _position;
}

Vector2* Player::GetPositionPtr()
{
	return &_position;
}

float Player::GetExpPickupRange()
{
	return _loadout.expPickupRange;
}

float Player::GetExpPickupRange() const
{
	return _loadout.expPickupRange;
}

void Player::SetPosition(Vector2 value)
{
	_position = value;
}
