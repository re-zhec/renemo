////////////////////////////////////////////////////////////////////////////////
/// \copyright MIT License                                                   ///
/// \author    Caylen Lee                                                    ///
/// \date      2019                                                          ///
////////////////////////////////////////////////////////////////////////////////
#include "World/World.hpp"
#include "World/Tileset.hpp"
#include "World/Tile.hpp"
#include "type/RowColumnIndex.hpp"
#include "util/readJsonFile.hpp"
#include "util/debug.hpp"
#include "constants.hpp"

#include <algorithm>

namespace nemo
{

namespace
{
	constexpr auto size_key_          = "size";
	constexpr auto tileset_key_       = "tileset";
	constexpr auto layout_key_        = "tiles";
	constexpr auto world_index_key_   = "world";
	constexpr auto sprite_index_key_  = "sprite";
	constexpr auto walkable_key_      = "walkable";

	const std::filesystem::path world_dir_ = constants::_asset_dir / "world";
}

////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

World::World(const std::filesystem::path& file)
{
	const auto error_parse_failure = [&file] () {
		STDERR("Failed to load world map " << file);
	};

	const std::optional< nlohmann::json > config = util::readJsonFile(file);

	if (!config) {
		error_parse_failure();
	}

	try {
		using indices_t = std::array< unsigned, 2 >;

		setTileset( config->at(tileset_key_).get< std::string_view >() );
		resetToSize( config->at(size_key_).get< indices_t >() );
		
		for (const auto& tile : config->at(layout_key_)) {
			const auto world_index = tile.at(world_index_key_).get< indices_t >();
	
			getTile(world_index).addTileIndex(
				tile.at(sprite_index_key_).get< indices_t >()
			);

			getTile(world_index).allowWalk(
				tile.at(walkable_key_).get< bool >()
			);
		}
	}
	catch (const nlohmann::json::out_of_range& e) {
		error_parse_failure();
	}
}

////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

void
World::resetToSize(const type::RowColumnIndex num_tiles)
{
	const auto rows = static_cast< int >(num_tiles._r);
	const auto cols = static_cast< int >(num_tiles._c);

	_tiles = tile_array_t(boost::extents[rows][cols]);
}

////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

Tile&
World::getTile(const type::RowColumnIndex world_index)
{
	return _tiles[world_index._r][world_index._c];
}

////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

const Tile&
World::getTile(const type::RowColumnIndex world_index)
const
{
	return _tiles[world_index._r][world_index._c];
}

////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

void
World::setTileset(const std::string_view& type)
{
	_tileset = makeTileset(type);
}

////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

TutorialWorld::TutorialWorld()
	: World(world_dir_ / "tutorial.json")
{
}

////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

} 