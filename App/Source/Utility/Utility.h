#pragma once

#include "raylib.h"


namespace Utility
{
	float Linear(float t);

	float Lerp(float start, float end, float t);
	Vector2 Lerp(Vector2 start, Vector2 end, float t);
}