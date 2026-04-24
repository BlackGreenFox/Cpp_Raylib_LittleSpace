#include "ButtonToggle.h"
#include <raymath.h>


ButtonToggle::ButtonToggle(Vector2 position, Vector2 size, std::string text) : Button(position, size, text)
{
	_isToggled = false;
}

ButtonToggle::~ButtonToggle()
{
}

void ButtonToggle::Update(float deltaTime)
{
	Button::Update(deltaTime);
	if (_isClick)
	{
		_isToggled = !_isToggled;
	}
}

void ButtonToggle::Draw()
{
	if (!_isVisible)
	{
		return;
	}

	Rectangle buttonRect = GetRect();
	int textWidth = MeasureText(_text.c_str(), _fontSize);
	int textPosX = (buttonRect.x + (buttonRect.width - textWidth) / 2);
	int textPosY = (buttonRect.y + (buttonRect.height - _fontSize) / 2);

	Vector2 center = Vector2Add(_position, Vector2Scale(_size, 0.5f));


	if (_isToggled)
	{
		DrawRectangleRounded(buttonRect, 0.06, 6, _colorHover);
		DrawRectangleRoundedLinesEx(buttonRect, 0.06, 6, _borderThickness, _colorToggleBorder);
		DrawPolyLinesEx(center, 6, _size.y / 4, 0, 6, _colorFigure);
	}
	else if (_isHovered)
	{
		DrawRectangleRounded(buttonRect, 0.06, 6, _colorHover);
		DrawRectangleRoundedLinesEx(buttonRect, 0.06, 6, _borderThickness, _colorHoverBorder);
		DrawText(_text.c_str(), textPosX, textPosY, _fontSize, _colorTextHover);
	}
	else
	{
		DrawRectangleRounded(buttonRect, 0.06, 6, _color);
		DrawRectangleRoundedLinesEx(buttonRect, 0.06, 6, _borderThickness, _colorBorder);
		DrawText(_text.c_str(), textPosX, textPosY, _fontSize, _colorText);
	}


}

bool ButtonToggle::GetToggled() const
{
	return _isToggled;
}