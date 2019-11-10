////////////////////////////////////////////////////////////////////////////////
/// \copyright MIT License                                                   ///
/// \author    Caylen Lee                                                    ///
/// \date      2019                                                          ///
////////////////////////////////////////////////////////////////////////////////
#pragma once

#include <memory>

#include <boost/filesystem/path.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>

namespace nemo
{

namespace type {
	class Vector2;
}

/**
 * \brief Enumeration for tileset types
 */
enum class TilesetType
{
	Urban,  /// Urban
	Forest  /// Forest
};

/**
 * \brief Tileset
 */
class Tileset
{
public:
	virtual ~Tileset() = default;

	/**
	 * \brief
	 */
	Tileset(boost::filesystem::path tilemap_file);

	/**
	 * \brief
	 */
	sf::Sprite
	getSprite(const type::Vector2 idx)
	const;

private:
	/**
	 * \brief
	 */
	static boost::filesystem::path
	getTilesetDir();

	sf::Texture _texture;
};

/**
 * \brief Urban tileset.
 */
class UrbanTilemap : public Tileset
{
public:
	UrbanTilemap();
};

/**
 * \brief Forest tileset.
 */
class ForestTilemap : public Tileset
{
public:
	ForestTilemap();
};

/**
 * \brief
 * Factory to create tilesets.
 * 
 * \param type
 * Which tileset to create.
 * 
 * \return
 * Tileset.
 */
std::unique_ptr< Tileset >
makeTileset(const TilesetType type);

} // namespace nemo