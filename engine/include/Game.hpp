////////////////////////////////////////////////////////////////////////////////
/// \copyright MIT License                                                   ///
/// \author    Caylen Lee                                                    ///
/// \date      2019                                                          ///
////////////////////////////////////////////////////////////////////////////////
#pragma once

#include "entity/Entity.hpp"
#include <SFML/Graphics/RenderWindow.hpp>

namespace nemo
{

/**
 * \brief Game
 */
class Game
{
public:
	/**
	 * \brief Creates and shares single game session.
	 * 
	 * \return Game session.
	 */
	static Game&
	getInstance();

	/**
	 * \brief Pauses game.
	 */
	void
	pause()
	noexcept;

	/**
	 * \brief Resumes game.
	 */
	void
	resume()
	noexcept;

	/**
	 * \brief Updates the current frame in the game loop.
	 * 
	 * \param window Game window to display new frame.
	 */
	void
	updateFrame(sf::RenderWindow& window);
	
private:
	/**
	 * \brief Creates game.
	 */
	Game();

	/// Whether game is paused or running.
	bool _is_playing;

	std::unique_ptr< Entity > _player;
	std::unique_ptr< Entity > _npc;
};

} 