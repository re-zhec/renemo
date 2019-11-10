////////////////////////////////////////////////////////////////////////////////
/// \copyright MIT License                                                   ///
/// \author    Caylen Lee                                                    ///
/// \date      2019                                                          ///
////////////////////////////////////////////////////////////////////////////////
#pragma once

namespace nemo
{

class Entity;

class EntityInput
{
public:
	virtual ~EntityInput() = default;
	
	virtual void
	updateObjectAction(Entity& obj)
	const = 0;
};

} // namespace nemo