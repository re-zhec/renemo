////////////////////////////////////////////////////////////////////////////////
/// \copyright MIT License                                                   ///
/// \author    Caylen Lee                                                    ///
/// \date      2019                                                          ///
////////////////////////////////////////////////////////////////////////////////
#include <algorithm>
#include <utility>
#include <SFML/Graphics/Color.hpp>

#include "GameObject/GameObject.hpp"
#include "GameObject/GameObjectInput.hpp"
#include "GameObject/GameObjectPhysics.hpp"
#include "GameObject/GameObjectGraphics.hpp"

namespace nemo
{

////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

GameObject::GameObject(
	std::unique_ptr< GameObjectInput >&&    input,
	std::unique_ptr< GameObjectPhysics >&&  physics,
	std::unique_ptr< GameObjectGraphics >&& graphics
)
	: _input(std::move(input))
	, _physics(std::move(physics))
	, _graphics(std::move(graphics))
{
	_hitbox.setFillColor(sf::Color::Red);
	_hitbox.setSize({ 100.f, 100.f });
}

////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

void
GameObject::stopMoving()
{
	_velocity = { 0, 0 };
}

////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

void
GameObject::setToGoLeft(const float x)
{
	_velocity = { -x, 0 };
}

////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

void
GameObject::setToGoUp(const float y)
{
	_velocity = { 0, -y };
}

////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

void
GameObject::setToGoRight(const float x)
{
	_velocity = { x, 0 };
}

////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

void
GameObject::setToGoDown(const float y)
{
	_velocity = { 0, y };
}

////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

void
GameObject::goToNewPosition()
{
	_hitbox.move(_velocity);
}

////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

void
GameObject::drawOnWindow(sf::RenderWindow& window)
const
{
	window.draw(_hitbox);
}

////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

void
GameObject::updateObject(sf::RenderWindow& window)
{
	_input->updateObjectAction(*this);
	_physics->updateObjectInteraction(*this);
	_graphics->updateObjectDisplay(*this, window);
}

////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

} // namespace nemo