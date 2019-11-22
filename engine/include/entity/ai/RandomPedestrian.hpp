////////////////////////////////////////////////////////////////////////////////
/// \copyright MIT License                                                   ///
/// \author    Caylen Lee                                                    ///
/// \date      2019                                                          ///
////////////////////////////////////////////////////////////////////////////////
#pragma once

#include "EntityAI.hpp"
#include <random>

namespace nemo::ai
{

/**
 * \brief
 * AI to make an entity stand still and sporadically walk around.
 */
class RandomPedestrian : public EntityAI
{
public:
	/**
	 * \brief           Commits an entity to an action.
	 * \param entity    Entity.
	 */
	virtual void
	commitAction(Entity& entity)
	override;

private:
	/**
	 * \brief     Indicates whether to move or stand still.
	 * \return    True for moving, false for standing still.
	 */
	bool
	timeToMove()
	const noexcept;

	/**
	 * \brief           Moves an entity to a random direction.
	 * \param entity    Entity to move.
	 */
	void
	goRandomDirection(Entity& entity)
	const noexcept;
};

}
