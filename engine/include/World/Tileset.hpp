////////////////////////////////////////////////////////////////////////////////
/// \copyright MIT License                                                   ///
/// \author    Caylen Lee                                                    ///
/// \date      2019                                                          ///
////////////////////////////////////////////////////////////////////////////////
#pragma once

#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>

#include <memory>
#include <filesystem>
#include <string_view>

namespace nemo
{

namespace type {
	struct RowColumnIndex;
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
	Tileset(const std::filesystem::path& file);

	/**
	 * \brief 
	 * Set the Tile Pixel Size object
	 * 
	 * \param length 
	 */
	void
	setTilePixelSize(const int length);
	
	/**
	 * \brief
	 * 
	 * \param index
	 * Row and column the tile is located in the tileset image.
	 * 
	 * \throw
	 * std::ios_base::failure if the texture fails to load from the file for any
	 * reasons.
	 */
	sf::Sprite
	getTileSprite(const type::RowColumnIndex index)
	const;

private:
	sf::Texture _texture;
	int         _tile_side_length;
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
makeTileset(const std::string_view& type);

} 