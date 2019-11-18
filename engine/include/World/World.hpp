////////////////////////////////////////////////////////////////////////////////
/// \copyright MIT License                                                   ///
/// \author    Caylen Lee                                                    ///
/// \date      2019                                                          ///
////////////////////////////////////////////////////////////////////////////////
#pragma once

#include <boost/multi_array.hpp>
#include <SFML/Graphics/RenderWindow.hpp>

#include <memory>
#include <unordered_map>
#include <filesystem>
#include <string_view>

namespace nemo
{

namespace type {
	class RowColumnIndex;
}

class Tile;
class Tileset;
enum class TilesetType;

/**
 * \brief
 */
class World
{
public:
	virtual
	~World() = default;

	/**
	 * \brief
	 */
	World(const std::filesystem::path& file);

	/**
	 * \brief
	 */
	Tile&
	getTile(const type::RowColumnIndex world_index);

	/**
	 * \brief
	 */
	const Tile&
	getTile(const type::RowColumnIndex world_index)
	const;

	/**
	 * \brief
	 */
	void
	setTileset(const std::string_view& type);

private:
	using tile_array_t = boost::multi_array< Tile, 2 >;
	
	/**
	 * \brief
	 */
	void
	resetToSize(const type::RowColumnIndex num_tiles);

	tile_array_t               _tiles;
	std::shared_ptr< Tileset > _tileset;
};

class TutorialWorld : public World
{
public:
	TutorialWorld();
};

} // namespace nemo