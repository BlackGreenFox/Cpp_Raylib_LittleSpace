#include "GameManager.h"


GameManager::GameManager()
{

}

GameManager::~GameManager()
{

}

void GameManager::Init(float screenWidth, int screenHeight)
{
	_screenWidth = screenWidth;
	_screenHeight = screenHeight;

	_player.Init({ (float)screenWidth / 2, (float)screenHeight / 2 });


	Vector2 size_level = Vector2{ 1700, 20 };
	Vector2 pos_level = { (float)(GetScreenWidth() / 2 - size_level.x / 2), (float)(GetScreenHeight() - 100) };

	_expBar.Init(pos_level, size_level, MAIN_GOOD_COLOR, _exp, _expToNextLevel);

	_expCubes.push_back(ExperienceCube());
	_expCubes[0].Init({ 300, 300 }, { 0, 0 }, _player.GetPositionPtr());
}

void GameManager::Update(float deltaTime)
{
	switch (_gameState)
	{
	case GameManager::GameState::Playing:

		int roll = GetRandomValue(0, 99);
		ENEMY_TYPE type;

		if (_level <= 2)
		{
			type = TRIANGLE;
		}



		_player.Update(deltaTime);
		UpdateEnemies(deltaTime);



		ProcessExpirience(deltaTime);
		


		break;
	case GameManager::GameState::LevelUp:
		break;
	case GameManager::GameState::Pause:
		break;
	case GameManager::GameState::GameOver:
		break;
	default:
		break;
	}
}



void GameManager::UpdateEnemies(float deltaTime)
{
	for (auto& enemy : _enemies)
	{
		enemy.Update(deltaTime);
	}
}



void GameManager::Draw()
{
	// Draw game world

	_player.Draw();


	for (auto& exp : _expCubes)
	{
		exp.Draw();
	}

	// Draw GUI
	_expBar.Draw();

}


// Processes
void GameManager::ProcessEnemies(float deltaTime)
{


}

void GameManager::ProcessExpirience(float deltaTime)
{
	for (auto& exp : _expCubes)
	{
		exp.Update(deltaTime);
	}

	CollisionManager::Update(_player, _enemies, _projectiles, _expCubes, deltaTime);
	_expBar.Update(deltaTime);
	for (auto& exp : _expCubes)
	{
		if (exp.GetActive()) continue;
		
		_exp += exp.GetExpValue();
		_expBar.SetValue(_exp);
	}

	_expCubes.erase(std::remove_if(_expCubes.begin(), _expCubes.end(), [](ExperienceCube& exp) { return !exp.GetActive(); }), _expCubes.end());

}




// Spawns

void GameManager::SpawnEnemy(Vector2 position, Vector2 velocity, ENEMY_TYPE type)
{
	Enemy e;
	e.Init(position, velocity, type);
	_enemies.push_back(e);
}


void GameManager::SpawnExp(Vector2 position, int amount)
{
	ExperienceCube exp;
	exp.Init(position, { 0, 0 }, _player.GetPositionPtr(), amount);
	_expCubes.push_back(exp);
}