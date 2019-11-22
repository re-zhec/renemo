////////////////////////////////////////////////////////////////////////////////
/// \copyright MIT License                                                   ///
/// \author    Caylen Lee                                                    ///
/// \date      2019                                                          ///
////////////////////////////////////////////////////////////////////////////////
#include "entity/EntityMake.hpp"
#include "entity/Entity.hpp"

#include "entity/ai/RandomPedestrian.hpp"
#include "entity/ai/Player.hpp"

#include "entity/sprite/TeenageBoy.hpp"
#include "entity/sprite/Hero.hpp"

namespace nemo
{

////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

namespace
{
	const auto make_entity_ = [] (
		std::unique_ptr< ai::EntityAI >&&        ai, 
		std::unique_ptr< sprite::EntitySprite>&& sprite)
	{
		return std::make_unique< Entity >( std::move(ai), std::move(sprite));
	};
}

EntityMake::entity_ptr_t
EntityMake::entity(const EntityID what)
{
	switch (what) {
		case EntityID::Hero:
		return hero();
		
		case EntityID::TeenageBoy:
		return teenageBoy();

		default:
		break;
	}

	return nullptr;
}

////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

EntityMake::entity_ptr_t
EntityMake::hero()
{
	return make_entity_(
		std::make_unique< ai::Player >(),
		std::make_unique< sprite::Hero >()
	);
}

////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

EntityMake::entity_ptr_t
EntityMake::teenageBoy()
{
	return make_entity_(
		std::make_unique< ai::RandomPedestrian >(),
		std::make_unique< sprite::TeenageBoy >()
	);
}

////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

}