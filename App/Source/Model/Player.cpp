#include "Player.h"


Player::Player() 
{
	position = { (float)GetScreenWidth() / 2, (float)GetScreenHeight() / 2 };
	stats.speed = 100;
	rotate = 45;
}

Player::~Player() 
{

}

void Player::Shoot()
{
	ShotType type = ShotType::Bullet;

	int count = 1;

	switch (type)
	{
	case ShotType::Bullet:
		for (int i = 0; i < count; i++)
		{
			Projectile p;
			p.position = position;
			p.velocity.x = cosf(rotate * DEG2RAD);
			p.velocity.y = sinf(rotate * DEG2RAD);
			p.velocity = Vector2Rotate(p.velocity, (float)GetRandomValue(-25, 25) * DEG2RAD);
			p.stats = shootStats;
			StraightTrajectory* trajectory = new StraightTrajectory;
			//trajectory->center = &this->position;
			p.trajectory = trajectory;
			p.type = type;
			p.Spawn();
			projectiles.push_back(p);
		}
		break;
	case ShotType::Laser:
		if (projectiles.empty())
		{
			Projectile p;
			p.position = position;
			p.ownerPos = &this->position;     
			p.ownerRotation = &this->rotate;


			p.velocity.x = cosf(rotate * DEG2RAD);
			p.velocity.y = sinf(rotate * DEG2RAD);
			StraightTrajectory* trajectory = new StraightTrajectory;
			//trajectory->center = &this->position;
			p.trajectory = trajectory;
			p.stats = shootStats;
			p.type = type;
			p.Spawn();
			projectiles.push_back(p);
		}
		else
		{
			for (auto& p : projectiles)
			{
				if (p.type == ShotType::Laser) {
					p.velocity.x = cosf(rotate * DEG2RAD);
					p.velocity.y = sinf(rotate * DEG2RAD);
				}
			}
		}
		break;
	default:
		break;
	}
	
}

void Player::Update(float deltaTime) 
{

	shootCooldown -= deltaTime;

	if (IsMouseButtonDown(MOUSE_LEFT_BUTTON) && shootCooldown <= 0)
	{
		Shoot();
		shootCooldown = stats.fireRate;
	}













	if (IsKeyDown(KEY_W))
	{
		velocity.y = -1;
	}
	else if (IsKeyDown(KEY_S))
	{
		velocity.y = 1;
	}
	else
	{
		velocity.y = 0;
	}

	if (IsKeyDown(KEY_A))
	{
		velocity.x = -1;
	}
	else if (IsKeyDown(KEY_D))
	{
		velocity.x = 1;
	}
	else
	{
		velocity.x = 0;
	}


	if (velocity.x != 0 || velocity.y != 0)
	{
		velocity = Vector2Scale(velocity, stats.speed * deltaTime);
		position = Vector2Add(position, velocity);
	}


	rotate = atan2f(GetMouseY() - position.y, GetMouseX() - position.x);
	rotate = rotate * RAD2DEG;


}

void Player::Draw() 
{
	DrawPolyLinesEx(position, 4, 10, rotate, 2, WHITE);
	DrawPolyLinesEx(position, 3, 40, rotate, 5, PLAYER);
	DrawCircleLines(position.x,position.y, stats.expAttractRange, WHITE);
}

Vector2 Player::GetPosition()
{
	return position;
}

void Player::SetPosition(Vector2 value)
{
	position = value;
}

PlayerStats Player::GetStats() const
{
	return stats;
}