////////////////////////////////////////////////////////////////////////////////
/// \copyright MIT License                                                   ///
/// \author    Caylen Lee                                                    ///
/// \date      2019                                                          ///
////////////////////////////////////////////////////////////////////////////////
#pragma once

#include <memory>

#include "GameObject.hpp"
#include "OverworldCharacter/OverworldCharacterInput.hpp"
#include "OverworldCharacter/OverworldCharacterPhysics.hpp"
#include "OverworldCharacter/OverworldCharacterGraphics.hpp"

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
	overworldCharacter();
};

} // namespace nemo