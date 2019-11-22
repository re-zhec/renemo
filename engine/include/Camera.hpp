////////////////////////////////////////////////////////////////////////////////
/// \copyright MIT License                                                   ///
/// \author    Caylen Lee                                                    ///
/// \date      2019                                                          ///
////////////////////////////////////////////////////////////////////////////////
#pragma once

#include "type/Vector2.hpp"

#include <SFML/Graphics/RenderWindow.hpp>

namespace nemo
{

// Forward declarations.
class World;
class Entity;

/**
 * \brief
 * Top-down, third-person view of the area map.
 */
class Camera
{
public:
	/**
	 * \brief
	 * 
	 * 
	 * \param size
	 * Width and height dimensions of the camera view, usually native size of 
	 * the game window.
	 */
	Camera(const type::Vector2 size);

	/**
	 * \brief
	 * Move the center of the camera view.
	 * 
	 * \param entity
	 * Entity in the game.
	 */
	void
	setCenter(const Entity& entity)
	noexcept;

	/**
	 * \brief
	 */
	void
	moveBy(const type::Vector2 velocity)
	noexcept;

	/**
	 * \brief
	 * Draw the current camera view of the area map on to the game window.
	 * 
	 * \param window      Game's render window.
	 * \param world       Area map.
	 * \param entities    All the entities on the area map.
	 */
	void
	drawView(
		sf::RenderWindow&            window, 
		const World&                 world,
		const std::vector< Entity >& entities
	) const;

private:
	/// Center coordinates of the camera.
	type::Vector2 _position;

	/// Window wize of the camera.
	type::Vector2 _size;
};

} 