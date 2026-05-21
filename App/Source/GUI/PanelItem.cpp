#include "PanelItem.h"
#include <raymath.h>




Color PanelItem::RarityColor(Rarity r)
{
	switch (r)
	{
	case Rarity::COMMON:    return RARITY_COMMON_COLOR;
	case Rarity::UNCOMMON:  return RARITY_UNCOMMON_COLOR;
	case Rarity::RARE:      return RARITY_RARE_COLOR;
	case Rarity::EPIC:      return RARITY_EPIC_COLOR;
	case Rarity::LEGENDARY: return RARITY_LEGENDARY_COLOR;
	}
	return WHITE;
}

int PanelItem::RaritySides(Rarity r)
{
	switch (r)
	{
	case Rarity::COMMON:    return 4;
	case Rarity::UNCOMMON:  return 5;
	case Rarity::RARE:      return 6;
	case Rarity::EPIC:      return 7;
	case Rarity::LEGENDARY: return 8;
	}
	return 6;
}

const char* PanelItem::RarityName(Rarity r)
{
	switch (r)
	{
	case Rarity::COMMON:    return "COMMON";
	case Rarity::UNCOMMON:  return "UNCOMMON";
	case Rarity::RARE:      return "RARE";
	case Rarity::EPIC:      return "EPIC";
	case Rarity::LEGENDARY: return "LEGENDARY";
	}
	return "?";
}

PanelItem::PanelItem(Vector2 position, Vector2 size, std::string title, std::string description, Rarity rarity)
{
	_position = position;
	_size = size;
	_title = title;
	_description = description;
	_rarity = RarityName(rarity);
	_color = RarityColor(rarity);
	_shapeSides = RaritySides(rarity);
}

PanelItem::~PanelItem()
{

}


void PanelItem::Update(float deltaTime)
{
	if (!_isActive)
	{
		_isHovered = false;
		_isClicked = false;
		_wasJustClicked = false;
		_wasClickedLastFrame = false;
		return;
	}

	_isHovered = CheckCollisionPointRec(GetMousePosition(), GetRect());
	bool down = IsMouseButtonDown(MOUSE_LEFT_BUTTON);
	_isClicked = _isHovered && down;

	_wasJustClicked = (_wasClickedLastFrame && !down && _isHovered);
	_wasClickedLastFrame = _isClicked;
}

void PanelItem::Draw()
{
	if (!_isVisible)
		return;

	Rectangle panelRect = { _position.x, _position.y, _size.x, _size.y };
	DrawRectangleRounded(panelRect, 0.06, 6, _colorBackground);
	DrawRectangleRoundedLinesEx(panelRect, 0.06, 6, _borderThickness, _color);

	if (_isHovered)
	{
		Rectangle hoverRect = { _position.x - 6, _position.y - 6, panelRect.width + 12 , panelRect.height + 12 };
		DrawRectangleRoundedLinesEx(hoverRect, 0.06, 6, _borderHoverThickness, _colorHover);
	}

	Vector2 panelCenter = Vector2Add(_position, Vector2Scale(_size, 0.5f));
	int titlePositionX = (int)panelCenter.x - MeasureText(_title.c_str(), _titleFontSize) / 2;
	int titlePositionY = (int)panelCenter.y - _titleFontSize / 2 - (int)(_size.y / 3);
	DrawText(_title.c_str(), titlePositionX, titlePositionY, _titleFontSize, _color);

	float radius = _size.y / 9.0f;
	DrawPolyLinesEx(panelCenter, _shapeSides, radius, 0, 4.0f, _color);
	DrawPoly(panelCenter, _shapeSides, radius * 0.55f, 0, _color);

	if (!_rarity.empty())
	{
		int rx = (int)panelCenter.x - MeasureText(_rarity.c_str(), _rarityFontSize) / 2;
		int ry = (int)(panelCenter.y - radius - (float)_rarityFontSize - 6.0f);
		DrawText(_rarity.c_str(), rx, ry, _rarityFontSize, _color);
	}

	int descriptionPositionX = (int)panelCenter.x - MeasureText(_description.c_str(), _descriptionFontSize) / 2;
	int descriptionPositionY = (int)panelCenter.y - _descriptionFontSize / 2 + (int)(_size.y / 3);
	DrawText(_description.c_str(), descriptionPositionX, descriptionPositionY, _descriptionFontSize, WHITE);

}

bool PanelItem::WasJustClicked() const
{
	return _wasJustClicked;
}

Rectangle PanelItem::GetRect() const
{
	return Rectangle{ _position.x, _position.y, _size.x, _size.y };
}