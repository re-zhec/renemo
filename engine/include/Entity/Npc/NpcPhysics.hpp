////////////////////////////////////////////////////////////////////////////////
/// \copyright MIT License                                                   ///
/// \author    Caylen Lee                                                    ///
/// \date      2019                                                          ///
////////////////////////////////////////////////////////////////////////////////
#pragma once

#include "Entity/EntityPhysics.hpp"

namespace nemo
{

/**
 * \brief 
 */
class NpcPhysics : public EntityPhysics
{
public:
	virtual void
	updateObjectInteraction(Entity& obj)
	const override;

private:
};

} // namespace nemo