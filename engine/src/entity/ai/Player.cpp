////////////////////////////////////////////////////////////////////////////////
/// \copyright MIT License                                                   ///
/// \author    Caylen Lee                                                    ///
/// \date      2019                                                          ///
////////////////////////////////////////////////////////////////////////////////
#include "entity/ai/Player.hpp"
#include "entity/Movement.hpp"
#include "entity/Entity.hpp"

namespace nemo::ai
{

////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

Player::Player()
	: _controller(std::make_unique< PlayerController >())
{
}

////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

void
Player::commitAction(Entity& entity)
{
	if (const auto direction = _controller->pressedDirection(); direction) {
		const attr::Movement& movement = entity.movement();

		const int speed = _controller->pressedButton({Button::Cancel}).has_value()
			? entity.speed()._running
			: entity.speed()._walking;

		switch (*direction) {
			case Button::Left:  movement.moveLeft(entity, speed);  break;
			case Button::Up:    movement.moveUp(entity, speed);    break;
			case Button::Right: movement.moveRight(entity, speed); break;
			case Button::Down:  movement.moveDown(entity, speed);  break;
			
			default:
			break;
		}
	}

	if (const auto selection = _controller->pressedSelection(); selection) {
		switch (*selection) {
			case Button::Cancel:
			break;

			case Button::Select:
			break;

			case Button::Pause:
			break;

			default:
			break;
		}
	}
	
}

////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

} 