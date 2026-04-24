#include "Element.h"

Element::Element()
{
	_position = { 0, 0 };
	_isActive = true;
}

Element::~Element()
{

}

void Element::Update(float deltaTime)
{

}
void Element::Draw()
{

}

Vector2 Element::GetPosition() const
{
	return _position;
}

bool Element::GetActive() const
{
	return _isActive;
}


void Element::SetPosition(const Vector2 position)
{
	_position = position;
}

void Element::SetActive(bool active)
{
	_isActive = active;
}

void Element::SetVisible(bool value)
{
	_isVisible = value;
}
