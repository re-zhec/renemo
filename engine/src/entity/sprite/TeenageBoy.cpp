////////////////////////////////////////////////////////////////////////////////
/// \copyright MIT License                                                   ///
/// \author    Caylen Lee                                                    ///
/// \date      2019                                                          ///
////////////////////////////////////////////////////////////////////////////////
#include "entity/sprite/TeenageBoy.hpp"
#include "entity/Entity.hpp"
#include "constants.hpp"

#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/Color.hpp>

namespace nemo::sprite
{

////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

void
TeenageBoy::displayEntity(sf::RenderWindow& window, const Entity& entity)
const
{
	const type::Vector2 position = entity.position();
	
	sf::RectangleShape graphics;
	graphics.setPosition(position.sfVector2< float >());
	graphics.setFillColor(sf::Color::Red);
	graphics.setSize({ 
		constants::_tile_side_length, constants::_tile_side_length
	});
	
	window.draw(graphics);
}

////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

} 