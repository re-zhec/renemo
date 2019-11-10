////////////////////////////////////////////////////////////////////////////////
/// \copyright MIT License                                                   ///
/// \author    Caylen Lee                                                    ///
/// \date      2019                                                          ///
////////////////////////////////////////////////////////////////////////////////
#pragma once

#include "type/Vector2.hpp"

#include <memory>
#include <SFML/Graphics/RenderWindow.hpp>

namespace nemo
{

class Tileset;

/**
 * \brief
 */
class Tile
{
public:
	virtual 
	~Tile() = default;

	/**
	 * \brief
	 * 
	 * \param tileset_idx
	 * Row and column of the tile to draw.
	 */
	Tile(const type::Vector2 tileset_idx)
	noexcept;

	/**
	 * \brief
	 * Allow/disallow characters from walking into this tile.
	 * 
	 * \param walkable
	 * True to allow, false to disallow.
	 */
	void
	allowWalk(const bool walkable)
	noexcept;

	/**
	 * \brief
	 * Indicate whether characters can walk into this tile.
	 * 
	 * \brief
	 * True if yes, false otherwise.
	 */
	bool 
	isWalkable()
	const noexcept;

	/**
	 * \brief
	 * Draw tile's sprite on the game's window.
	 * 
	 * \param window      Game's render window.
	 * \param tileset     Tileset to use.
	 */
	void
	drawSprite(
		sf::RenderWindow&   window, 
		const Tileset&      tileset
	) const;

private:	
	/// Indicate whether characters can walk into this tile.
	bool          _is_walkable;
	type::Vector2 _tileset_idx;
};

////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

} // namespace nemo