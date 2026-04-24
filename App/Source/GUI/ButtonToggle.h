#pragma once

#include "Button.h"
#include <string>

class ButtonToggle : public Button
{
private:
	Color _colorFigure = MAIN_BAD_COLOR;
	Color _colorToggleBorder = MAIN_BAD_COLOR;
	Color _colorTextToggle = MAIN_BAD_COLOR;


	bool _isToggled = false;
public:
	ButtonToggle(Vector2 position, Vector2 size, std::string text);
	~ButtonToggle();
	void Update(float deltaTime) override;
	void Draw() override;

	bool GetToggled() const;
};



