////////////////////////////////////////////////////////////////////////////////
/// \copyright MIT License                                                   ///
/// \author    Caylen Lee                                                    ///
/// \date      2019                                                          ///
////////////////////////////////////////////////////////////////////////////////
#pragma once

#include "constants.hpp"

namespace nemo::attr
{

/**
 * \brief
 * Speed at which an entity can move, in pixels per frame.
 */
struct MovementSpeed
{
	int _walking = constants::_walking_speed; /// Walking speed.
	int _running = constants::_running_speed; /// Running speed.
};

}