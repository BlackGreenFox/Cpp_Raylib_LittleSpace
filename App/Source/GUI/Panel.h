#pragma once


#include "Element.h"
#include "Utility/Utility.h"
#include <string>


class Panel : public Element
{
private:

	std::string _title;
	std::string _description;

	int _titleFontSize = 35;
	int _descriptionFontSize = 20;


	Color _colorBackground = SECOND_BACKGROUND_COLOR;
	Color _color = MAIN_GOOD_COLOR;
	Color _colorHover = WHITE;


	float _borderThickness = 3;
	float _borderHoverThickness = 3;

	bool _isHovered;
	bool _isClicked;



public:
	Panel(Vector2 position, Vector2 size, std::string title, std::string description);
	~Panel();

	void Update(float deltaTime) override;
	void Draw() override;
private:
	Rectangle GetRect() const;
};

