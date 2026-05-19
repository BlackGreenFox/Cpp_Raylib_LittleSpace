#include "GameManager.h"

const float ASTEROID_RANDOM_ANGLE = 30 * DEG2RAD;


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
	_player.SetProjectileBuffer(&_projectiles);

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
	case GameState::Playing:
	{
		UpdateProjectiles(deltaTime);
		UpdateEnemies(deltaTime);


		_player.Update(deltaTime);

		ProcessExpirience(deltaTime);
		ProcessEnemies(deltaTime);

		// Clear inactive entities

		_projectiles.erase(
			std::remove_if(_projectiles.begin(), _projectiles.end(),
				[](const Projectile& p) { return !p.alive; }),
			_projectiles.end());

		_enemies.erase(
			std::remove_if(_enemies.begin(), _enemies.end(),
				[](const Enemy& e) { return !e.GetActive(); }),
			_enemies.end());

		_expCubes.erase(
			std::remove_if(_expCubes.begin(), _expCubes.end(),
				[](const ExperienceCube& c) { return !c.GetActive(); }),
			_expCubes.end());
	}
		break;
	case GameState::LevelUp:

		break;
	case GameState::Pause:

		break;
	case GameState::GameOver:

		break;
	default:

		break;
	}
}


void GameManager::UpdateProjectiles(float deltaTime)
{

	for (auto& projectile : _projectiles)
	{
		projectile.Update(deltaTime);
	}
}

void GameManager::UpdateEnemies(float deltaTime)
{
	_spawnTimer -= deltaTime;
	if (_spawnTimer > 0)
		return;

	float interval = _enemySpawnInterval - (_level * 0.1f);
	_spawnTimer = interval;

	int random = GetRandomValue(0, 99);
	ENEMY_TYPE type;


	if (_level <= 2)		type = TRIANGLE;
	else if (_level <= 3)   type = (random < 70) ? TRIANGLE : SQUARE;
	else if (_level <= 4)   type = (random < 70) ? TRIANGLE : SQUARE;


	int dir = GetRandomValue(0, 3);
	Vector2 pos;
	switch (dir)
	{
	case 0:
		pos = { (float)GetRandomValue(0, _screenWidth), -40 };
		break;
	case 1:
		pos = { (float)_screenWidth + 40, (float)GetRandomValue(0, _screenHeight) };
		break;
	case 2:
		pos = { (float)GetRandomValue(0, _screenWidth), (float)_screenHeight + 40 };
		break;
	case 3:
		pos = { -50, (float)GetRandomValue(0, _screenHeight) };
		break;
	}

	Vector2 velocity = Vector2Subtract(Vector2{ (float)_screenWidth / 2, (float)_screenHeight / 2 }, pos);
	velocity = Vector2Scale(Vector2Normalize(velocity), (float)GetRandomValue(5, 15));
	velocity = Vector2Rotate(velocity, (float)GetRandomValue(-ASTEROID_RANDOM_ANGLE, ASTEROID_RANDOM_ANGLE));

	SpawnEnemy(pos, velocity, type);
}



void GameManager::Draw()
{
	// Draw game world

	_player.Draw();


	for (auto& exp : _expCubes)
	{
		exp.Draw();
	}

	for (auto& enemy : _enemies)
	{
		enemy.Draw();
	}

	for (auto& projectile : _projectiles)
	{
		projectile.Draw();
	}



	// Draw GUI
	_expBar.Draw();

}


// Processes
void GameManager::ProcessEnemies(float deltaTime)
{
	for (auto& enemy : _enemies)
	{
		enemy.Update(deltaTime);
	}


	const float pad = 80.0f;
	for (auto& enemy : _enemies)
	{
		if (!enemy.GetActive())
			continue;

		Vector2 pos = enemy.GetPosition();
		if (pos.x < -pad || pos.x > _screenWidth + pad || pos.y < -pad || pos.y > _screenHeight + pad)
		{
			enemy.SetOutSide(true);
			enemy.SetActive(false);
		}
	}


	vector<std::pair<Vector2, int>> expDrops;
	vector<std::pair<Vector2, ENEMY_TYPE>> enemySplit;

	for (auto& enemy : _enemies)
	{
		if (enemy.GetActive() || enemy.GetOutSide())
			continue;

		expDrops.push_back({ enemy.GetPosition(), (int)enemy.GetSize() * 10 * _level });
		int splitCount = enemy.GetSize() / 3;

		switch (enemy.GetEnemyType())
		{
		case SIX_SIDES:
			enemySplit.push_back({ enemy.GetPosition(), ENEMY_TYPE::TRIANGLE });
			enemySplit.push_back({ enemy.GetPosition(), ENEMY_TYPE::TRIANGLE });
			break;
		case EIGHT_SIDES:
			enemySplit.push_back({ enemy.GetPosition(), ENEMY_TYPE::SQUARE });
			enemySplit.push_back({ enemy.GetPosition(), ENEMY_TYPE::SQUARE });
			break;
		case NINE_SIDES:
			enemySplit.push_back({ enemy.GetPosition(), ENEMY_TYPE::TRIANGLE });
			enemySplit.push_back({ enemy.GetPosition(), ENEMY_TYPE::TRIANGLE });
			enemySplit.push_back({ enemy.GetPosition(), ENEMY_TYPE::TRIANGLE });
			break;
		default:
			break;
		}

		for (auto& drop : expDrops)
		{
			SpawnExp(drop.first, drop.second);
		}

		for (auto& split : enemySplit)
		{
			float angle = GetRandomValue(0, 360) * DEG2RAD;
			Vector2 velocity = Vector2{ cosf(angle), sinf(angle) };
			Vector2 spawnPos = Vector2Add(split.first, Vector2Scale(velocity, 20.0f));
			
			SpawnEnemy(spawnPos, velocity, split.second);
		}
	}

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


//

void GameManager::StateLevelUp()
{
	_gameState = GameState::LevelUp;
	
	_itemChoices = RollItems(5, _level);
	int count = _itemChoices.size();

	Vector2 panelSize = { 300, 150 };
	float gap = 30.0f;
	float totalWidth = count * panelSize.x + (count - 1) * gap;
	float startX = (_screenWidth - totalWidth) * 0.5f;
	
	float y = (_screenHeight - panelSize.y) * 0.5f;

	_itemPanel.clear();
	
	for (int index = 0; index < count; index++)
	{
		Item& item = _itemChoices[index];
		float x = startX + index * (panelSize.x + gap);

		_itemPanel.push_back({ item, {x, y}, panelSize });
	}

}