////////////////////////////////////////////////////////////////////////////////
/// \copyright MIT License                                                   ///
/// \author    Caylen Lee                                                    ///
/// \date      2019                                                          ///
////////////////////////////////////////////////////////////////////////////////
#pragma once

#include "Entity.hpp"
#include "Npc/PlayerInput.hpp"
#include "Npc/NpcInput.hpp"
#include "Npc/NpcPhysics.hpp"
#include "Npc/NpcGraphics.hpp"

#include <memory>

namespace nemo
{

class Entity;

class EntityCreator
{
public:
	/**
	 * \return A character on the overworld map.
	 */
	static std::unique_ptr< Entity >
	npc();

	/**
	 * \return A playable character on the overworld map.
	 */
	static std::unique_ptr< Entity >
	player();
};

} // namespace nemo