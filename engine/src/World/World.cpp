////////////////////////////////////////////////////////////////////////////////
/// \copyright MIT License                                                   ///
/// \author    Caylen Lee                                                    ///
/// \date      2019                                                          ///
////////////////////////////////////////////////////////////////////////////////
#include "World/World.hpp"
#include "World/Tileset.hpp"
#include "World/Tile.hpp"
#include "type/Vector2.hpp"

#include <algorithm>

namespace nemo
{

namespace {
	using row_t    = type::x_t;
	using column_t = type::y_t;
}
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

void
World::resetToSize(const type::Vector2 size)
noexcept
{
	const auto [width, height] = size.sfVector2< int >();
	_tiles = tile_array_t(boost::extents[width][height]);

	for (tile_array_t::index r = 0; r < height; ++r) {
		for (tile_array_t::index c = 0; c < width; ++c) {
			const type::Vector2 idx = { row_t(r), column_t(c) };
			_tiles[r][c] = std::make_unique< Tile >(idx);
		}
	};
}

////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

void
World::setTileset(const TilesetType type)
{
	_tileset = makeTileset(type);
}

////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

void
World::drawWorld(sf::RenderWindow& window)
const
{ 
}

} // namespace nemo