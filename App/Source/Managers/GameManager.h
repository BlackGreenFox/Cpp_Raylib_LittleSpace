#pragma once
#include "raylib.h"
#include <vector>

#include <CommonInclude.h>
#include <GUI/Bar.h>
#include <GUI/PanelItem.h>
#include <GUI/Button.h>
#include <GUI/ButtonToggle.h>

#include "Model/Enemy.h"
#include <Model/Player.h>
#include <Model/ExperienceCube.h>
#include <Model/Projectile.h>
#include <Model/Item.h>


#include "CollisionManager.h"


using std::vector;

class GameManager
{
public:
	GameManager();
	~GameManager();

	void Init(float screenWidth, int screenHeight);
	void Update(float deltaTime);
	void Draw();

	//void SpawnEnemy();
	//void SpawnProjectile();


private:
	int _screenWidth;
	int _screenHeight;

	enum class GameState
	{
		Playing,
		LevelUp,
		Pause,
		GameOver
	};

	GameState _gameState = GameState::Playing;


	//void UpdateProjectiles(float deltaTime);
	void UpdateEnemies(float deltaTime);
	//void HandleCollisions();
	//void TrySpawnEnemy(float deltaTime);


	vector<Element> _gui;
	
	Player					 _player;

	vector<Enemy>			 _enemies;
	vector<Projectile>		 _projectiles;
	vector<ExperienceCube>	 _expCubes;


	int _level = 1;
	int _exp = 0;
	int _expToNextLevel = 100;



	int _enemiesMax = 5;
	int _bossLevel = 5;



};

