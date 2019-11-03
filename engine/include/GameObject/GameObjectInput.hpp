////////////////////////////////////////////////////////////////////////////////
/// \copyright MIT License                                                   ///
/// \author    Caylen Lee                                                    ///
/// \date      2019                                                          ///
////////////////////////////////////////////////////////////////////////////////
#pragma once

namespace nemo
{

class GameObject;

class GameObjectInput
{
public:
	virtual ~GameObjectInput() = default;
	
	virtual void
	updateObjectAction(GameObject& obj)
	const = 0;
};

} // namespace nemo