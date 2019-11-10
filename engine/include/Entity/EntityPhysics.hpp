////////////////////////////////////////////////////////////////////////////////
/// \copyright MIT License                                                   ///
/// \author    Caylen Lee                                                    ///
/// \date      2019                                                          ///
////////////////////////////////////////////////////////////////////////////////
#pragma once

namespace nemo
{

class Entity;

class EntityPhysics
{
public:
	virtual ~EntityPhysics() = default;

	virtual void
	updateObjectInteraction(Entity& obj)
	const = 0;
};

} // namespace nemo