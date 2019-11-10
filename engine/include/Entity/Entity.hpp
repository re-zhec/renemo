////////////////////////////////////////////////////////////////////////////////
/// \copyright MIT License                                                   ///
/// \author    Caylen Lee                                                    ///
/// \date      2019                                                          ///
////////////////////////////////////////////////////////////////////////////////
#pragma once

#include <memory>

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/RectangleShape.hpp>

namespace nemo
{

class EntityInput;
class EntityPhysics;
class EntityGraphics;

/**
 * \brief A base game object
 */
class Entity
{
public:
	virtual ~Entity() = default;
	
	/**
	 * \brief
	 */
	Entity(
		std::unique_ptr< EntityInput >&&    input,
		std::unique_ptr< EntityPhysics >&&  physics,
		std::unique_ptr< EntityGraphics >&& graphics
	);

	/**
	 * \brief Stops object from moving.
	 */
	void
	stopMoving();

	/**
	 * \brief Moves object left.
	 * 
	 * \param x Velocity for left-moving object.
	 */
	void
	setToGoLeft(const float x);

	/**
	 * \brief Moves object upward.
	 * 
	 * \param y Velocity for right-moving object.
	 */
	void
	setToGoUp(const float y);

	/**
	 * \brief Moves object right.
	 * 
	 * \param x Velocity for upward-moving object.
	 */
	void
	setToGoRight(const float x);

	/**
	 * \brief Moves object downward.
	 * 
	 * \param y Velocity for downward-moving object.
	 */
	void
	setToGoDown(const float y);

	/**
	 * \brief Changes object's coordinate based on its current velocity.
	 */
	void
	goToNewPosition();

	/**
	 * \brief Draw object on game window.
	 * 
	 * \param window Game window.
	 */
	void
	drawOnWindow(sf::RenderWindow& window)
	const;

	/**
	 * \brief Updates the object for the game loop's current frame.
	 * 
	 * \param window Game window.
	 */
	void
	updateObject(sf::RenderWindow &window);

private:
	/// Commits the object to an action.
	std::unique_ptr< EntityInput >    _input;

	/// Physical interaction with the game world.  
	std::unique_ptr< EntityPhysics >  _physics;
	
	/// Graphical display in the game window.
	std::unique_ptr< EntityGraphics > _graphics;

	/// Object's hitbox.
	sf::RectangleShape                    _hitbox;

	/// Object's velocity.
	sf::Vector2f                          _velocity;
};

} // namespace nemo