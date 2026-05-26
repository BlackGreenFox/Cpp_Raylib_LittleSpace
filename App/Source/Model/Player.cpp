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
	_rotate = 0;
	_currentHeath = _loadout.playerMaxHealth;

	_screenHeight = GetScreenHeight();
	_screenWidth = GetScreenWidth();
}

void Player::TakeDamage(float amount)
{
	_currentHeath -= amount;
	if (_currentHeath < 0)
	{
		_currentHeath = 0;
		_isAlive = false;
	}
}

void Player::Heal(float amount)
{
	_currentHeath += amount;
	if (_currentHeath > _loadout.playerMaxHealth)
	{
		_currentHeath = _loadout.playerMaxHealth;
	}
}

//
//void Player::Shoot()
//{
//	if (!_projectBuffer)
//		return;
//
//	ShotType type = ShotType::Bullet;
//
//	int count = 1;
//
//	switch (type)
//	{
//	case ShotType::Bullet:
//		for (int i = 0; i < count; i++)
//		{
//			Projectile p;
//			p.position = _position;
//			p.velocity.x = cosf(_rotate * DEG2RAD);
//			p.velocity.y = sinf(_rotate * DEG2RAD);
//			p.velocity = Vector2Rotate(p.velocity, (float)GetRandomValue(-25, 25) * DEG2RAD);
//			p.stats.speed = _loadout.bulletSpeed;
//			p.stats.damage = _loadout.bulletDamage;
//			p.stats.distance = _loadout.bulletDistance;
//			p.stats.size = _loadout.bulletSize;
//			p.stats.color = _loadout.bulletColor;
//			StraightTrajectory* trajectory = new StraightTrajectory;
//			//trajectory->center = &this->position;
//			p.trajectory = trajectory;
//			p.type = type;
//			p.Spawn();
//			_projectBuffer->push_back(p);
//		}
//		break;
//	case ShotType::Laser:
//		if (_projectBuffer->empty())
//		{
//			Projectile p;
//			p.position = _position;
//			p.ownerPos = &this->_position;     
//			p.ownerRotation = &this->_rotate;
//
//
//			p.velocity.x = cosf(_rotate * DEG2RAD);
//			p.velocity.y = sinf(_rotate * DEG2RAD);
//			StraightTrajectory* trajectory = new StraightTrajectory;
//			//trajectory->center = &this->position;
//			p.trajectory = trajectory;
//
//			p.stats.speed = _loadout.bulletSpeed;
//			p.stats.damage = _loadout.bulletDamage;
//			p.stats.distance = _loadout.bulletDistance;
//			p.stats.size = _loadout.bulletSize;
//			p.stats.color = _loadout.bulletColor;
//			p.type = type;
//			p.Spawn();
//			_projectBuffer->push_back(p);
//		}
//		else
//		{
//			//for (auto& p : _projectBuffer)
//			//{
//			//	if (p.type == ShotType::Laser) {
//			//		p.velocity.x = cosf(rotate * DEG2RAD);
//			//		p.velocity.y = sinf(rotate * DEG2RAD);
//			//	}
//			//}
//		}
//		break;
//	default:
//		break;
//	}
//	
//}

void Player::FireBullet(float angle)
{
	int count = _loadout.shootCount > 0 ? _loadout.shootCount : 1;
	float spread = _loadout.shootSpread;

	for (int i = 0; i < count; i++)
	{
		float angelDeg;

		if (count > 1)
		{
			float t = i / count - 1;
			angelDeg = angle + (t - 0.5f) * 2.0f * GetRandomValue(-spread * 10, spread * 10) / 10;
		}
		else
		{
			angelDeg = angle + GetRandomValue(-spread * 10, spread * 10) / 10;
		}



		Projectile p;
		p.position = _position;
		p.startpos = _position;
		p.direction = { cosf(angelDeg * DEG2RAD), sinf(angelDeg * DEG2RAD) };
		p.velocity = p.direction;
		//p.velocity = Vector2Rotate(p.velocity, (float)GetRandomValue(-spread, spread) * DEG2RAD);
		p.stats.speed = _loadout.bulletSpeed;
		p.stats.size = _loadout.bulletSize;
		p.stats.damage = _loadout.bulletDamage;
		p.stats.distance = _loadout.bulletDistance;
		p.stats.color = _loadout.bulletColor;
		//p.explode = _loadout.bulletExplode;
		p.type = ShotType::Bullet;

		if (_loadout.trajectory == TrajectoryKind::Straight)
		{
			p.trajectory = new StraightTrajectory;

		}

		p.Spawn();
		_projectBuffer->push_back(p);
	}

}

void Player::FireLazer(float angle)
{
	Projectile p;
	p.position = _position;
	p.startpos = _position;
	p.ownerPos = &_position;
	p.ownerRotation = &_rotate;	
	p.velocity = { cosf(angle * DEG2RAD), sinf(angle * DEG2RAD) };
	p.direction = p.velocity;
	p.stats.speed = _loadout.bulletSpeed;
	p.stats.size = _loadout.bulletSize;
	p.stats.damage = _loadout.bulletDamage;
	p.stats.distance = _loadout.bulletDistance;
	p.stats.color = _loadout.bulletColor;
	p.type = ShotType::Laser;

	if (_loadout.trajectory == TrajectoryKind::Straight)
	{
		p.trajectory = new StraightTrajectory;

	}

	p.Spawn();
	_projectBuffer->push_back(p);
}

void Player::DestroyOwner()
{
	if (!_projectBuffer)
		return;

	for (auto& p :  *_projectBuffer)
	{
		p.Destroy();
	}
}

void Player::HandlerShooting(float deltaTime)
{
	if (IsMouseButtonDown(MOUSE_LEFT_BUTTON))
	{
		if (!_projectBuffer)
			return;

		switch (_loadout.shotType)
		{
			case ShotType::Bullet:
				_shootCooldown -= deltaTime;

				if (_shootCooldown <= 0)
				{
					FireBullet(_rotate);
					if (_loadout.shootBackwards)
						FireBullet(_rotate + 180);

					_shootCooldown = _loadout.fireRate;
				}
				break;
			case ShotType::Laser:
				_chaergeProgress += deltaTime;
				if (!_isLaserAcrive && _chaergeProgress >= _loadout.fireRate)
				{
					FireLazer(_rotate);
					if (_loadout.shootBackwards)
						FireLazer(_rotate + 180);
					_isLaserAcrive = true;
				}
				else
				{
					 if (_isLaserAcrive)
					 {
						 DestroyOwner();
						_isLaserAcrive = false;
					 }
					 _chaergeProgress = 0;
				}
				break;
		default:
			break;
		}

	}
}

void Player::HandlerMovement(float deltaTime)
{
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
		_velocity = Vector2Normalize(_velocity);
		_velocity = Vector2Scale(_velocity, _loadout.playerSpeed * deltaTime);
		_position = Vector2Add(_position, _velocity);
	}



	_rotate = atan2f(GetMouseY() - _position.y, GetMouseX() - _position.x);
	_rotate = _rotate * RAD2DEG;


	float r = _loadout.playerSize;
	if (_position.x < r) _position.x = r;
	if (_position.x > _screenWidth - r) 
		_position.x = _screenWidth - r;

	if (_position.y < r) _position.y = r;
	if (_position.y > _screenHeight - r) 
		_position.y = _screenHeight - r;
}

void Player::Update(float deltaTime) 
{
	HandlerMovement(deltaTime);
	HandlerShooting(deltaTime);
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

float Player::GetMaxHealth()
{
	return _loadout.playerMaxHealth;
}

float Player::GetMaxHealth() const
{
	return _loadout.playerMaxHealth;
}

float Player::GetCurrentHealth()
{
	return _currentHeath;
}

float Player::GetCurrentHealth() const
{
	return _currentHeath;
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
