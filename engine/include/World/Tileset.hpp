////////////////////////////////////////////////////////////////////////////////
/// \copyright MIT License                                                   ///
/// \author    Caylen Lee                                                    ///
/// \date      2019                                                          ///
////////////////////////////////////////////////////////////////////////////////
#pragma once

#include <memory>
#include <filesystem>

#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>

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
	 * \param rc
	 * Row and column the tile is located in the tileset image.
	 * 
	 * \throw
	 * std::ios_base::failure if the texture fails to load from the file for any
	 * reasons.
	 */
	sf::Sprite
	getTileSprite(const type::RowColumnIndex rc)
	const;

private:
	sf::Texture _texture;
	int         _tile_pixel_length;
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