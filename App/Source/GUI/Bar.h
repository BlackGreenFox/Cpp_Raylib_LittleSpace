#pragma once
#include "Element.h"
#include "Utility/Utility.h"

class Bar : public Element
{
private:
	enum class AnimationState
	{
		None,
		IncreasingBuffer,
		DecreasingBuffer,
		IncreasingMain,
		DecreasingMain
	};


	AnimationState _state = AnimationState::None;

	float _value = 0;
	float _maxValue = 100;
	float _minValue = 0;

	Color _color;
	Vector2 _size;
	Vector2 _maxSize;
	Vector2 _bufferSize;
	Vector2 _targetSize;

	float _animationTimeBuffer = 0.18f;
	float _animationTimeMain = 0.45f;

public:
	Bar(Vector2 position, Vector2 size, Color color, float value, float maxValue);
	~Bar();
	void Update(float deltaTime) override;
	void Draw() override;

	void SetValue(float value);
	float GetValue() const { return _value; }
};