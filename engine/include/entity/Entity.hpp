////////////////////////////////////////////////////////////////////////////////
/// \copyright MIT License                                                   ///
/// \author    Caylen Lee                                                    ///
/// \date      2019                                                          ///
////////////////////////////////////////////////////////////////////////////////
#pragma once

#include "ai/EntityAI.hpp"
#include "sprite/EntitySprite.hpp"
#include "Movement.hpp"
#include "attributes.hpp"
#include "type/Vector2.hpp"

#include <SFML/Graphics/RenderWindow.hpp>

#include <memory>

namespace nemo
{

/**
 * \brief
 * Game entity.
 */
class Entity
{
public:
	virtual 
	~Entity() = default;
	
	/**
	 * \brief
	 */
	Entity(
		std::unique_ptr< ai::EntityAI >&&         ai,
		std::unique_ptr< sprite::EntitySprite >&& sprite
	);

	/**
	 * \brief     Gets entity's current coordinates.
	 * \return    Entity's coordinates.
	 */
	type::Vector2
	position()
	const noexcept;

	/**
	 * \brief             Changes entity's current coordinates.
	 * \param position    Entity's new coordinates.
	 */
	void
	setPosition(const type::Vector2 position)
	noexcept;

	/**
	 * \brief     Gets entity's movement handler.
	 * \return    Entity's movement handler.
	 */
	const attr::Movement&
	movement()
	const noexcept;

	/**
	 * \brief             Changes entity's movement handler.
	 * \param movement    Entity's new movement handler.
	 */
	void
	setMovability(std::unique_ptr< attr::Movement >&& movement)
	noexcept;

	/**
	 * \brief     Gets entity's movement speeds.
	 * \return    Movement's walking and running speed.
	 */
	attr::MovementSpeed
	speed()
	const noexcept;

	/**
	 * \brief       Changes an entity's AI.
	 * \param ai    New AI to swap in.
	 */
	void
	changeAI(std::unique_ptr< ai::EntityAI >&& ai);

	/**
	 * \brief           Changes an entity's sprite renderer
	 * \param sprite    New sprite renderer to use.
	 */
	void
	changeSprite(std::unique_ptr< sprite::EntitySprite >&& sprite);

	/**
	 * \brief           Updates the object for the game loop's current frame.
	 * \param window    Game window.
	 */
	void
	updateObject(sf::RenderWindow &window);

private:
	type::Vector2       _position; /// Current position.
	attr::MovementSpeed _speed;    /// Movement speeds.
	
	std::unique_ptr< attr::Movement >       _movement; /// Handles movements.
	std::unique_ptr< ai::EntityAI >         _ai;       /// AI.
	std::unique_ptr< sprite::EntitySprite > _sprite;   /// Handles sprites.
};

} 