////////////////////////////////////////////////////////////////////////////////
/// \copyright MIT License                                                   ///
/// \author    Caylen Lee                                                    ///
/// \date      2019                                                          ///
////////////////////////////////////////////////////////////////////////////////
#include "entity/ai/RandomPedestrian.hpp"
#include "entity/Entity.hpp"
#include "entity/Movement.hpp"

#include <array>
#include <functional>

namespace nemo::ai
{

////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

namespace 
{
	/// Random number generator for deciding pedestrian's actions.
	std::mt19937 rng_((std::random_device())());
}

////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

void
RandomPedestrian::commitAction(Entity& entity)
{
	if (!timeToMove()) {
		return;
	}

	goRandomDirection(entity);
}

////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

bool
RandomPedestrian::timeToMove()
const noexcept
{
	// Entity would stand still for roughly 80% of the time and walk for the 
	// other 20%.
	constexpr auto odds_of_standing = 8;
	constexpr auto odds_of_moving = 2;
	std::uniform_int_distribution distrib(1, odds_of_standing + odds_of_moving);
	
	return distrib(rng_) <= odds_of_moving;
}

////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

void
RandomPedestrian::goRandomDirection(Entity& entity)
const noexcept
{
	const int speed = entity.speed()._walking;
	const attr::Movement& movement = entity.movement();
	constexpr auto num_directions = 4;	
	 
	const auto movers = std::array< std::function<void()>, num_directions > ({
		[&entity, &movement, speed] () { movement.moveLeft(entity, speed);  },
		[&entity, &movement, speed] () { movement.moveUp(entity, speed);    },
		[&entity, &movement, speed] () { movement.moveRight(entity, speed); },
		[&entity, &movement, speed] () { movement.moveDown(entity, speed);  }
	});

	std::uniform_int_distribution<unsigned> distrib(0, num_directions - 1);
	// movers[distrib(_rng)]();
}

////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

}