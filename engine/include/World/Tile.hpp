////////////////////////////////////////////////////////////////////////////////
/// \copyright MIT License                                                   ///
/// \author    Caylen Lee                                                    ///
/// \date      2019                                                          ///
////////////////////////////////////////////////////////////////////////////////
#pragma once

#include <SFML/Graphics/RenderWindow.hpp>

#include <vector>

namespace nemo
{

class Tileset;
namespace type {
	class RowColumnIndex;
}

/**
 * \brief
 * Metadata for a tile at an area map.
 * 
 * Tiles make up the layout for all area maps. This class stores and operates
 * on only the tiles' metadata, which is everything about the tiles except the 
 * sprites themselves:
 * 
 *     1. Whether a character can walk into this tile i.e. isn't a wall or a
 *        closed space.
 * 
 *     2. Whether this tile is an exit that will take a character out of the 
 *        current area map, and where in the new area map it would take them to.
 * 
 *     2. Row and column indices of tile sprites from a tileset to render in the
 *        game window. The indices are not tied to a specific tilesets, so the 
 *        tileset can be easily swapped.
 */
class Tile
{
public:
	/**
	 * \brief
	 * Constructs an empty, non-walkable tile.
	 */
	Tile();

	/**
	 * \brief
	 * Adds a row and column indices of a new tileset tile sprite to render
	 * on screen.
	 * 
	 * \param tile_idx
	 * Row and column numbers of a new tileset tile to draw.
	 */
	void
	addTileIndex(const type::RowColumnIndex tile_idx);

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
	 * \return
	 * True if yes, false otherwise.
	 */
	bool 
	isWalkable()
	const noexcept;

	/**
	 * \brief
	 * Draws tile sprites from a tileset on the game's window.
	 * 
	 * \param window      Game's render window.
	 * \param tileset     Tileset to use.
	 * 
	 * This method uses row and column indices that were added via \link 
	 * addTileIndex to choose which tile sprites from \a tileset to draw.
	 */
	void
	drawSprite(sf::RenderWindow& window, const Tileset& tileset)
	const;

private:	
	/// Indicate whether characters can walk into this tile.
	bool _is_walkable;
	
	/// A collection of tiles to draw from a tileset via indices.
	std::vector< type::RowColumnIndex > _tile_indices;
};

////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

} 