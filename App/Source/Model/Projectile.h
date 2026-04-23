#pragma once
#include "raylib.h"
#include "raymath.h"
#include <vector>

enum class ShotType {
	Bullet,
	Laser
};

struct ShotStats
{
	float damage = 1;
	float speed = 400;
	float size = 6;
	float distance = 2000;
	Color color = WHITE;
};

struct Projectile;
struct Trajectory
{
	virtual ~Trajectory() = default;
	virtual Vector2 GetPosition(const Projectile& p, float t) = 0;
};

struct Projectile
{

	Vector2 startpos;
    Vector2* ownerPos = nullptr;
    float* ownerRotation = nullptr; 
    Vector2 position;
	Vector2 velocity;
	Vector2 direction;

	ShotStats stats;
	ShotType type;
	Trajectory* trajectory = nullptr;

	float travel = 0;
	bool alive = true;

	float startTime;
	float time;


	void Spawn();
	void Destroy();
	void Update(float deltaTime);
	void Draw();
};

void UpdateProjectiles(float deltaTime);
void DrawProjectiles();


struct StraightTrajectory : Trajectory
{
	Vector2 GetPosition(const Projectile& p, float t) override
	{
		return Vector2Add(p.startpos, Vector2Scale(p.velocity, t * p.stats.speed));
	}
};

struct OrbitTrajectory : Trajectory
{
    Vector2* center;
    float targetRadius = 100.0f;

    Vector2 GetPosition(const Projectile& p, float t) override
    {
        if (!center) return p.startpos;
		targetRadius = p.stats.distance / 20;
 
        float timeToReachOrbit = targetRadius / p.stats.speed;
 
        float startAngle = atan2f(p.velocity.y, p.velocity.x);

        if (t < timeToReachOrbit)
        {
 
            float dist = p.stats.speed * t;
            return {
                center->x + cosf(startAngle) * dist,
                center->y + sinf(startAngle) * dist
            };
        }
        else
        {
 
            float tRot = t - timeToReachOrbit;
 
            float rotationSpeed = p.stats.speed / targetRadius;
            float currentAngle = startAngle + (tRot * rotationSpeed);

            return {
                center->x + cosf(currentAngle) * targetRadius,
                center->y + sinf(currentAngle) * targetRadius
            };
        }
    }
};

extern std::vector<Projectile> projectiles;