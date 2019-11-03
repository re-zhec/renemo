////////////////////////////////////////////////////////////////////////////////
/// \copyright MIT License                                                   ///
/// \author    Caylen Lee                                                    ///
/// \date      2019                                                          ///
////////////////////////////////////////////////////////////////////////////////
#pragma once

#include "GameObject/GameObjectInput.hpp"

namespace nemo
{

/**
 * \brief 
 */
class OverworldNpcInput : public GameObjectInput
{
public:
	/**
	 * \brief
	 */
	OverworldNpcInput();

	/**
	 * \brief Controls player action on the overworld map.
	 */
	virtual void
	updateObjectAction(GameObject& obj)
	const override;

private:
	/// NPC's moving speed.
	constexpr static float _moving_speed = 2.0f;
};

}