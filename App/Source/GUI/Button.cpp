#include "Button.h"

 
Button::Button(Vector2 position, Vector2 size, std::string text)
{
	_position = position;
	_size = size;
	_text = text;
}


Button::~Button()
{
}

void Button::Update(float deltaTime)
{
	if (!_isActive)
	{
		_isHovered = false;
		_isClick = false;
		return;
	}
	_isHovered = CheckCollisionPointRec(GetMousePosition(), GetRect());
	_isClick = _isHovered && IsMouseButtonReleased(MOUSE_LEFT_BUTTON);
}


void Button::Draw()
{
	if (!_isVisible)
	{
		return;
	}

	Rectangle buttonRect = GetRect();
	int textWidth = MeasureText(_text.c_str(), _fontSize);
	int textPosX = (buttonRect.x + (buttonRect.width - textWidth) / 2);
	int textPosY = (buttonRect.y + (buttonRect.height - _fontSize) / 2);



	if (_isHovered)
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


Rectangle Button::GetRect() const
{
	return Rectangle{ _position.x, _position.y, _size.x, _size.y };
}