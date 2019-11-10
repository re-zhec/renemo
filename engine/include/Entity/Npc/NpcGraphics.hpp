////////////////////////////////////////////////////////////////////////////////
/// \copyright MIT License                                                   ///
/// \author    Caylen Lee                                                    ///
/// \date      2019                                                          ///
////////////////////////////////////////////////////////////////////////////////
#pragma once

#include "Entity/EntityGraphics.hpp"

namespace nemo
{

/**
 * \brief 
 */
class NpcGraphics : public EntityGraphics
{
public:
	virtual void
	updateObjectDisplay(Entity& obj, sf::RenderWindow& window)
	const override;

private:
};

} // namespace nemo