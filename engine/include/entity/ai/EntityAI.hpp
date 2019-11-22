////////////////////////////////////////////////////////////////////////////////
/// \copyright MIT License                                                   ///
/// \author    Caylen Lee                                                    ///
/// \date      2019                                                          ///
////////////////////////////////////////////////////////////////////////////////
#pragma once

#include <memory>

namespace nemo {
	class Entity; // Forward declaration.
}

namespace nemo::ai
{

/**
 * \brief
 * Artificial intelligence that decides an entity's action.
 */
class EntityAI
{
public:
	virtual 
	~EntityAI() = default;
	
	/**
	 * \brief           Commits an entity to an action.
	 * \param entity    Entity.
	 */
	virtual void
	commitAction(Entity& entity) = 0;
};

using entity_ai_uptr_t = std::unique_ptr< EntityAI >;

}