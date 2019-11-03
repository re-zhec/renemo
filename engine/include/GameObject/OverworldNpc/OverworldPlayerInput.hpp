////////////////////////////////////////////////////////////////////////////////
/// \copyright MIT License                                                   ///
/// \author    Caylen Lee                                                    ///
/// \date      2019                                                          ///
////////////////////////////////////////////////////////////////////////////////
#pragma once

#include <memory>

#include "GameObject/GameObjectInput.hpp"
#include "Controller.hpp"

namespace nemo
{

/**
 * \brief 
 */
class OverworldPlayerInput : public GameObjectInput
{
public:
	/**
	 * \brief
	 */
	OverworldPlayerInput();

	/**
	 * \brief Controls player action on the overworld map.
	 */
	virtual void
	updateObjectAction(GameObject& obj)
	const override;

private:
	/// Player controller.
	std::unique_ptr< Controller > _controller;

	/// Player's moving speed.
	constexpr static float _moving_speed = 2.0f;
};

}