////////////////////////////////////////////////////////////////////////////////
/// \copyright MIT License                                                   ///
/// \author    Caylen Lee                                                    ///
/// \date      2019                                                          ///
////////////////////////////////////////////////////////////////////////////////
#include "Game.hpp"
#include "GameObject/GameObjectCreator.hpp"
#include "common_utils.hpp"

namespace nemo
{

////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

Game::Game()
	: _is_playing(true)
	, _player(GameObjectCreator::overworldCharacter())
{
}

////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

Game&
Game::getInstance()
{
	static Game instance;
	return instance;
}

////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

void
Game::pause()
noexcept
{
	STDINFO("Game paused");
	_is_playing = false;
}

////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

void
Game::resume()
noexcept
{
	STDINFO("Game resumed");
	_is_playing = true;
}

////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

void
Game::updateFrame(sf::RenderWindow& window)
{
	if (!_is_playing) {
		return;
	}

	_player->updateObject(window);
}

////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

} // namespace nemo