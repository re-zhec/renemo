////////////////////////////////////////////////////////////////////////////////
/// \copyright MIT License                                                   ///
/// \author    Caylen Lee                                                    ///
/// \date      2019                                                          ///
////////////////////////////////////////////////////////////////////////////////
#pragma once

#include "Entity/EntityInput.hpp"

namespace nemo
{

/**
 * \brief 
 */
class NpcInput : public EntityInput
{
public:
	/**
	 * \brief
	 */
	NpcInput();

	/**
	 * \brief Controls player action on the overworld map.
	 */
	virtual void
	updateObjectAction(Entity& obj)
	const override;

private:
	/// NPC's moving speed.
	constexpr static float _moving_speed = 2.0f;
};

} // namespace nemo