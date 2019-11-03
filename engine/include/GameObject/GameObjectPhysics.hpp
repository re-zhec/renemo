////////////////////////////////////////////////////////////////////////////////
/// \copyright MIT License                                                   ///
/// \author    Caylen Lee                                                    ///
/// \date      2019                                                          ///
////////////////////////////////////////////////////////////////////////////////
#pragma once

namespace nemo
{

class GameObject;

class GameObjectPhysics
{
public:
	virtual ~GameObjectPhysics() = default;

	virtual void
	updateObjectInteraction(GameObject& obj)
	const = 0;
};

} // namespace nemo