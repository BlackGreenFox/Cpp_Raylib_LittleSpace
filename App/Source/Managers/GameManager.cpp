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


	_expCubes.push_back(ExperienceCube());
	_expCubes[0].Init({ 300, 300 }, { 0, 0 }, _player.GetPositionPtr());
}

void GameManager::Update(float deltaTime)
{
	switch (_gameState)
	{
	case GameManager::GameState::Playing:

		_player.Update(deltaTime);
		UpdateEnemies(deltaTime);


		for(auto& exp : _expCubes)
		{
			exp.Update(deltaTime);
		}

		CollisionManager::Update(_player, _enemies, _projectiles, _expCubes, deltaTime);

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
	_player.Draw();

	for (auto& exp : _expCubes)
	{
		exp.Draw();
	}
}