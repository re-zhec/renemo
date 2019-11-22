////////////////////////////////////////////////////////////////////////////////
/// \copyright MIT License                                                   ///
/// \author    Caylen Lee                                                    ///
/// \date      2019                                                          ///
////////////////////////////////////////////////////////////////////////////////
#pragma once

#include "EntityAI.hpp"
#include "Controller.hpp"

#include <memory>

namespace nemo::ai
{

/**
 * \brief
 * Allows player to control an entity's action.
 */
class Player : public EntityAI
{
public:
	/**
	 * \brief
	 * Constructs player input handler for an entity.
	 */
	Player();

	/**
	 * \brief
	 * Commits an entity to an action.
	 * 
	 * \param entity
	 * Game entity.
	 */
	virtual void
	commitAction(Entity& entity)
	override;

private:
	std::unique_ptr< Controller > _controller; /// Player controller.
};

}