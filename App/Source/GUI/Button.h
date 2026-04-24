#pragma once

#include "Element.h"
#include <string>

class Button : public Element
{
private:


protected:
	std::string _text;
	int _fontSize = 24;

	float _borderThickness = 3;

	Color _color = SECOND_BACKGROUND_COLOR;
	Color _colorBorder = MAIN_GOOD_COLOR;
	Color _colorText = WHITE;

	Color _colorHover = MAIN_BACKGROUND_COLOR;
	Color _colorHoverBorder = MAIN_GOOD_COLOR;
	Color _colorTextHover = MAIN_GOOD_COLOR;

	bool _isClick;
	bool _isHovered;

	Rectangle GetRect() const;
public:
	Button(Vector2 position, Vector2 size, std::string text);
	~Button();

	void Update(float deltaTime) override;
	void Draw() override;
private:

};