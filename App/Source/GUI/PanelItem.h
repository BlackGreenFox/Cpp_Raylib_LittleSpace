#pragma once


#include "Element.h"
#include "Utility/Utility.h"
#include "Utility/Rarity.h"
#include <string>


class PanelItem : public Element
{
private:

	std::string _title;
	std::string _description;
	std::string _rarity;

	int _titleFontSize = 35;
	int _descriptionFontSize = 20;
	int _rarityFontSize = 16;

	int _shapeSides = 3;

	Color _colorBackground = SECOND_BACKGROUND_COLOR;
	Color _color = MAIN_GOOD_COLOR;
	Color _colorHover = WHITE;

	float _borderThickness = 3;
	float _borderHoverThickness = 3;

	bool _isHovered = false;
	bool _isClicked = false;
	bool _wasClickedLastFrame = false;
	bool _wasJustClicked = false;


	Color RarityColor(Rarity r);
	int RaritySides(Rarity r);
	const char* RarityName(Rarity r);

public:
	PanelItem(Vector2 position, Vector2 size, std::string title, std::string description, Rarity rarity);
	~PanelItem();

	void Update(float deltaTime) override;
	void Draw() override;
	bool WasJustClicked() const;
private:
	Rectangle GetRect() const;
};

