////////////////////////////////////////////////////////////////////////////////
/// \copyright MIT License                                                   ///
/// \author    Caylen Lee                                                    ///
/// \date      2019                                                          ///
////////////////////////////////////////////////////////////////////////////////
#pragma once

#include <memory>

namespace nemo
{

class Entity;

/**
 * \brief
 * Enumeration identifiers used for generating entity objects.
 */
enum class EntityID
{
	Hero,       /// Hero character.
	TeenageBoy, /// Generic teenage boy.
};

class EntityMake
{
public:
	using entity_ptr_t = std::unique_ptr< Entity >;
	EntityMake() = delete;

	static entity_ptr_t
	entity(const EntityID what);

	static entity_ptr_t
	hero();

	static entity_ptr_t
	teenageBoy();
};

}