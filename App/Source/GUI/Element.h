#pragma once
#include "raylib.h"
#include <CommonInclude.h>

class Element
{
protected:
	Vector2 _position;
	bool _isActive = true;

public:
	Element();
	~Element();

	Vector2 GetPosition() const;
	bool GetActive() const;

	void SetPosition(const Vector2 position);
	void SetActive(bool active);

	virtual void Update(float deltaTime);
	virtual void Draw();
};