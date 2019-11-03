////////////////////////////////////////////////////////////////////////////////
/// \copyright MIT License                                                   ///
/// \author    Caylen Lee                                                    ///
/// \date      2019                                                          ///
////////////////////////////////////////////////////////////////////////////////
#pragma once

#include <SFML/Graphics/RenderWindow.hpp>

namespace nemo
{

class GameObject;

class GameObjectGraphics
{
public:
	virtual ~GameObjectGraphics() = default;

	virtual void
	updateObjectDisplay(GameObject& obj, sf::RenderWindow& window)
	const = 0;
};

} // namespace nemo