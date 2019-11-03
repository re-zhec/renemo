////////////////////////////////////////////////////////////////////////////////
/// \copyright MIT License                                                   ///
/// \author    Caylen Lee                                                    ///
/// \date      2019                                                          ///
////////////////////////////////////////////////////////////////////////////////
#pragma once

#include <memory>

#include "GameObject.hpp"
#include "OverworldNpc/OverworldPlayerInput.hpp"
#include "OverworldNpc/OverworldNpcInput.hpp"
#include "OverworldNpc/OverworldNpcPhysics.hpp"
#include "OverworldNpc/OverworldNpcGraphics.hpp"

namespace nemo
{

class GameObject;

class GameObjectCreator
{
public:
	/**
	 * \return A character on the overworld map.
	 */
	static std::unique_ptr< GameObject >
	overworldNpc();

	/**
	 * \return A playable character on the overworld map.
	 */
	static std::unique_ptr< GameObject >
	overworldPlayer();
};

} // namespace nemo