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

	Vector2 _size;
	Vector2 _position;

	float _borderThickness = 3;

public:
	Panel(Vector2 position, Vector2 size, std::string title, std::string description);
	~Panel();

	void Update(float deltaTime) override;
	void Draw() override;

};

