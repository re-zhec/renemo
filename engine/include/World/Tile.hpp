////////////////////////////////////////////////////////////////////////////////
/// \copyright MIT License                                                   ///
/// \author    Caylen Lee                                                    ///
/// \date      2019                                                          ///
////////////////////////////////////////////////////////////////////////////////
#pragma once

#include <vector>
#include <SFML/Graphics/RenderWindow.hpp>

namespace nemo
{

namespace type
{
	class RowColumnIndex;
}
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
	 * Constructs metadata for a world map tile.
	 * 
	 * \param tile_indices
	 * Row-column indices of the tileset tiles to draw.
	 */
	Tile(const std::vector< type::RowColumnIndex > tile_indices = {});

	/**
	 * \brief
	 * Adds a new tileset tile to draw via another row-column index.
	 * 
	 * \param tile_idx
	 * Row and column number of a new tileset tile to draw.
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
	 * \brief
	 * True if yes, false otherwise.
	 */
	bool 
	isWalkable()
	const noexcept;

	/**
	 * \brief
	 * Draw tiles from a tileset on the game's window.
	 * 
	 * \param window      Game's render window.
	 * \param tileset     Tileset to use.
	 * 
	 * This method uses row and column references stored in this object to 
	 * decide which tiles from \a tileset to draw.
	 */
	void
	drawSprite(sf::RenderWindow& window, const Tileset& tileset)
	const;

private:	
	/// Indicate whether characters can walk into this tile.
	bool _is_walkable;
	
	/// Keeps track of tiles to draw from a tileset via indices.
	std::vector< type::RowColumnIndex > _tile_indices;
};

////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

} // namespace nemo