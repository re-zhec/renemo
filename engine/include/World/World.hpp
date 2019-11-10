////////////////////////////////////////////////////////////////////////////////
/// \copyright MIT License                                                   ///
/// \author    Caylen Lee                                                    ///
/// \date      2019                                                          ///
////////////////////////////////////////////////////////////////////////////////
#pragma once

#include <memory>
#include <unordered_map>

#include <boost/multi_array.hpp>
#include <SFML/Graphics/RenderWindow.hpp>

namespace nemo
{

namespace type {
	struct x_t;
	struct y_t;
	class  Vector2;
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
	void
	resetToSize(type::Vector2 size)
	noexcept;

	/**
	 * \brief
	 */
	void
	setTileset(const TilesetType type);

	/**
	 * \brief
	 */
	void
	drawWorld(sf::RenderWindow& window)
	const;

private:
	using tile_array_t = boost::multi_array< std::shared_ptr<Tile>, 2 >;
	
	tile_array_t               _tiles;
	std::shared_ptr< Tileset > _tileset;
};

} // namespace nemo