#include "Game.hpp"
#include "Controller.hpp"

#include <cstdlib>

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Window/Event.hpp>
#include <SFML/Window/VideoMode.hpp>

int
main()
{
	// Open a window for the game.
	sf::RenderWindow window(sf::VideoMode(1280, 720), "Nemo");
	window.setFramerateLimit(30);
	window.setKeyRepeatEnabled(false);

	// Run the game for as long as its window is open.
	while (window.isOpen()) {
		// Update game.
		nemo::Game& game = nemo::Game::getInstance();
		window.clear();
		game.updateFrame(window);
		window.display();
		
		// Get whatever event happened.
		sf::Event event;

		if (!window.pollEvent(event)) {
			// No pending events.
			continue;
		}
		
		switch (event.type) {
			case sf::Event::Closed:
			window.close();
			break;
			
			case sf::Event::LostFocus:
			game.pause();
			break;

			case sf::Event::GainedFocus:
			game.resume();
			break;

			case sf::Event::KeyPressed:
			nemo::Controller::registerKeyPress(event.key.code);
			break;

			case sf::Event::KeyReleased:
			nemo::Controller::registerKeyRelease(event.key.code);
			break;

			default:
			break;
		}
	}

	return EXIT_SUCCESS;
}