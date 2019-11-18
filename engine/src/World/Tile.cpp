////////////////////////////////////////////////////////////////////////////////
/// \copyright MIT License                                                   ///
/// \author    Caylen Lee                                                    ///
/// \date      2019                                                          ///
////////////////////////////////////////////////////////////////////////////////
#include "World/Tile.hpp"
#include "World/Tileset.hpp"
#include "type/RowColumnIndex.hpp"

#include <algorithm>

namespace nemo
{

////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

Tile::Tile()
{
	allowWalk(false);
}

////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

void
Tile::addTileIndex(const type::RowColumnIndex tile_idx)
{
	if (const auto duplicate = 
			std::find(_tile_indices.cbegin(), _tile_indices.cend(), tile_idx);
		duplicate != _tile_indices.cend())
	{
		// Avoid duplicate tile sprite indices. Just move the old one to the 
		// back.
		// std::rotate(duplicate, duplicate + 1, _tile_indices.cend());
		return;
	}

	// Tile sprites are drawn in order of when the indices were added, so a 
	// tile sprite whose indices are at the back would be the last drawn and, 
	// thus, be the topmost sprite on screen.
	_tile_indices.push_back(tile_idx);
}

////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

void
Tile::allowWalk(const bool walkable)
noexcept
{
	_is_walkable = walkable;
}

////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

bool
Tile::isWalkable()
const noexcept
{
	return _is_walkable;
}

////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

void
Tile::drawSprite(
	sf::RenderWindow&   window, 
	const Tileset&      tileset
) const
{
	for (const type::RowColumnIndex idx : _tile_indices) {
		window.draw( tileset.getTileSprite(idx) );
	}
}

////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

} // namespace nemo