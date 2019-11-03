////////////////////////////////////////////////////////////////////////////////
/// \copyright MIT License                                                   ///
/// \author    Caylen Lee                                                    ///
/// \date      2019                                                          ///
////////////////////////////////////////////////////////////////////////////////
#pragma once

#include "GameObject/GameObjectGraphics.hpp"

namespace nemo
{

/**
 * \brief 
 */
class OverworldNpcGraphics : public GameObjectGraphics
{
public:
	virtual void
	updateObjectDisplay(GameObject& obj, sf::RenderWindow& window)
	const override;

private:
};

} // namespace nemo