#include "Bar.h"
#include <iostream>


bool IsSizeEqual(Vector2 a, Vector2 b)
{
	return a.x - b.x < 0.5f && a.y - b.y < 0.5f;
}


Bar::Bar(Vector2 position, Vector2 size, Color color, float value, float maxValue)
{
	_position = position;
	_size = size;
	_maxSize = size;
	_color = color;

	_maxValue = maxValue;
	_value = value;

	float percent = _value / _maxValue;
	_size.x = _maxSize.x * percent;
	 
	_bufferSize = _size;
}

Bar::~Bar()
{
}

void Bar::SetValue(float value)
{
	float oldValue = _value;
	_value = value;


	float percent = _value / _maxValue;
	_targetSize = { _maxSize.x * percent, _size.y };

	if (_value > oldValue)
	{
		_state = AnimationState::IncreasingBuffer;
	}
	else if (_value < oldValue)
	{
		_state = AnimationState::DecreasingMain;
	}
}


void Bar::Update(float deltaTime)
{
	if (!_isActive)
		return;

	float mainFillSpeed = Utility::Linear(deltaTime / _animationTimeBuffer);
	float bufferFillSpeed = Utility::Linear(deltaTime / _animationTimeMain);

	switch (_state)
	{
	case Bar::AnimationState::IncreasingBuffer:
		_bufferSize = Utility::Lerp(_bufferSize, _targetSize, bufferFillSpeed);
		if (IsSizeEqual(_targetSize, _bufferSize))
		{
			_bufferSize = _targetSize;
			_state = AnimationState::IncreasingMain;
		}
		break;
	case Bar::AnimationState::DecreasingBuffer:
		_bufferSize = Utility::Lerp(_bufferSize, _targetSize, bufferFillSpeed);
		if (IsSizeEqual(_bufferSize, _targetSize))
		{
			_bufferSize = _targetSize;
			_state = AnimationState::None;
		}
		break;
	case Bar::AnimationState::IncreasingMain:
		_size = Utility::Lerp(_size, _targetSize, mainFillSpeed);
		if (IsSizeEqual(_targetSize, _size))
		{
			_size = _targetSize;
			_state = AnimationState::None;
		}
		break;
	case Bar::AnimationState::DecreasingMain:
		_size = Utility::Lerp(_size, _targetSize, mainFillSpeed);
		if (IsSizeEqual(_size, _targetSize))
		{
			_size = _targetSize;
			_state = AnimationState::DecreasingBuffer;
		}
		break;
	case Bar::AnimationState::None:
		break;
	default:
		break;
	}
}

void Bar::Draw()
{
	if (!_isActive) 
		return;
	
	DrawRectangleV(_position, _maxSize, SECOND_BACKGROUND_COLOR);
	DrawRectangleV(_position, _bufferSize, WHITE);
	DrawRectangleV(_position, _size, _color);
}