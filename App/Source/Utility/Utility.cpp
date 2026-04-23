
#include "Utility.h"

#include <cmath>

namespace Utility
{
	float Clamp(float t)
	{
		if (t < 0)
			return 0;
		else if (t > 1)
			return 1;
		else
			return t;
	}

	float Linear(float t)
	{
		return Clamp(t);
	}

	float Lerp(float start, float end, float t)
	{
		t = Clamp(t);
		return start + (end - start) * t;
	}

	Vector2 Lerp(Vector2 start, Vector2 end, float t)
	{
		t = Clamp(t);
		return { Lerp(start.x, end.x, t), Lerp(start.y, end.y, t) };
	}
}