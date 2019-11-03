////////////////////////////////////////////////////////////////////////////////
/// \copyright MIT License                                                   ///
/// \author    Caylen Lee                                                    ///
/// \date      2019                                                          ///
////////////////////////////////////////////////////////////////////////////////
#include "GameObject/OverworldNpc/OverworldPlayerInput.hpp"
#include "GameObject/GameObject.hpp"

namespace nemo
{

////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

OverworldPlayerInput::OverworldPlayerInput()
	: _controller(std::make_unique< PlayerController >())
{
}

////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

void
OverworldPlayerInput::updateObjectAction(GameObject& obj)
const
{
	switch (_controller->getPressedSelection().value_or(Button::Left)) {
		case Button::Cancel:
		break;

		case Button::Select:
		break;

		case Button::Pause:
		break;

		default:
		break;
	}

	switch (_controller->getPressedDirection().value_or(Button::Cancel)) {
		case Button::Left:  obj.setToGoLeft (_moving_speed); break;
		case Button::Up:    obj.setToGoUp   (_moving_speed); break;
		case Button::Right: obj.setToGoRight(_moving_speed); break;
		case Button::Down:  obj.setToGoDown (_moving_speed); break;
		default:            obj.stopMoving();                break;
	}
}

////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

} // namespace nemo