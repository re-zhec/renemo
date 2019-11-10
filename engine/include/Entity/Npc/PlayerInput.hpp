////////////////////////////////////////////////////////////////////////////////
/// \copyright MIT License                                                   ///
/// \author    Caylen Lee                                                    ///
/// \date      2019                                                          ///
////////////////////////////////////////////////////////////////////////////////
#pragma once

#include "Entity/EntityInput.hpp"
#include "Controller.hpp"

#include <memory>

namespace nemo
{

/**
 * \brief 
 */
class PlayerInput : public EntityInput
{
public:
	/**
	 * \brief
	 */
	PlayerInput();

	/**
	 * \brief Controls player action on the overworld map.
	 */
	virtual void
	updateObjectAction(Entity& obj)
	const override;

private:
	/// Player controller.
	std::unique_ptr< Controller > _controller;

	/// Player's moving speed.
	constexpr static float _moving_speed = 2.0f;
};

}