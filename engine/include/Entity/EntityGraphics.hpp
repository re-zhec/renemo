////////////////////////////////////////////////////////////////////////////////
/// \copyright MIT License                                                   ///
/// \author    Caylen Lee                                                    ///
/// \date      2019                                                          ///
////////////////////////////////////////////////////////////////////////////////
#pragma once

#include <SFML/Graphics/RenderWindow.hpp>

namespace nemo
{

class Entity;

class EntityGraphics
{
public:
	virtual ~EntityGraphics() = default;

	virtual void
	updateObjectDisplay(Entity& obj, sf::RenderWindow& window)
	const = 0;
};

} // namespace nemo