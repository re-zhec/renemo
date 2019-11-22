////////////////////////////////////////////////////////////////////////////////
/// \copyright MIT License                                                   ///
/// \author    Caylen Lee                                                    ///
/// \date      2019                                                          ///
////////////////////////////////////////////////////////////////////////////////
#pragma once

#include "EntitySprite.hpp"

namespace nemo::sprite
{

/**
 * \brief 
 */
class TeenageBoy : public EntitySprite
{
public:
	virtual void
	displayEntity(sf::RenderWindow& window, const Entity& entity)
	const override;
};

}