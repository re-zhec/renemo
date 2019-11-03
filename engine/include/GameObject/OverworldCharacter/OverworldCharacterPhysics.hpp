////////////////////////////////////////////////////////////////////////////////
/// \copyright MIT License                                                   ///
/// \author    Caylen Lee                                                    ///
/// \date      2019                                                          ///
////////////////////////////////////////////////////////////////////////////////
#pragma once

#include "GameObject/GameObjectPhysics.hpp"

namespace nemo
{

/**
 * \brief 
 */
class OverworldCharacterPhysics : public GameObjectPhysics
{
public:
	virtual void
	updateObjectInteraction(GameObject& obj)
	const override;

private:
};

} // namespace nemo