#include "Panel.h"
#include <raymath.h>

Panel::Panel(Vector2 position, Vector2 size, std::string title, std::string description)
{
	_position = position;
	_size = size;
	_title = title;
	_description = description;
}

Panel::~Panel()
{

}

void Panel::Update(float deltaTime)
{
	if (!_isActive)
		return;
}

void Panel::Draw()
{
	if (!_isActive)
		return;



	Rectangle panelRect = { _position.x, _position.y, _size.x, _size.y };
	DrawRectangleRounded(panelRect, 0.06, 6, _colorBackground);
	DrawRectangleRoundedLinesEx(panelRect, 0.06, 6, _borderThickness, _color);


	Vector2 panelCenter = Vector2Add(_position, Vector2Scale(_size, 0.5f));
	int titlePositionX = panelCenter.x - MeasureText(_title.c_str(), _titleFontSize) / 2;
	int titlePositionY = panelCenter.y - MeasureText(_title.c_str(), _titleFontSize) / 2 - (_size.y / 3);
	DrawText(_title.c_str(), titlePositionX, titlePositionY, _titleFontSize, _color);

	DrawPolyLinesEx(panelCenter, 6, _size.y / 9, 0, 8, _color);

	int descriptionPositionX = panelCenter.x - MeasureText(_description.c_str(), _descriptionFontSize) / 2;
	int descriptionPositionY = panelCenter.y - MeasureText(_description.c_str(), _descriptionFontSize) / 2 + (_size.y / 3);
	DrawText(_description.c_str(), descriptionPositionX, descriptionPositionY, _descriptionFontSize, WHITE);
}

Rectangle Panel::GetBounds() const
{
	return Rectangle{ _position.x, _position.y, _size.x, _size.y };
}