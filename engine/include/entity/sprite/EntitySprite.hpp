////////////////////////////////////////////////////////////////////////////////
/// \copyright MIT License                                                   ///
/// \author    Caylen Lee                                                    ///
/// \date      2019                                                          ///
////////////////////////////////////////////////////////////////////////////////
#pragma once

#include <SFML/Graphics/RenderWindow.hpp>

namespace nemo {
	class Entity; // Forward declaration.
}

namespace nemo::sprite
{

class EntitySprite
{
public:
	virtual
	~EntitySprite() = default;

	/**
	 * \brief
	 */
	virtual void
	displayEntity(sf::RenderWindow& window, const Entity& entity)
	const = 0;
};

using entity_sprite_uptr_t = std::unique_ptr< EntitySprite >;

}