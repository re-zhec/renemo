////////////////////////////////////////////////////////////////////////////////
/// \copyright MIT License                                                   ///
/// \author    Caylen Lee                                                    ///
/// \date      2019                                                          ///
////////////////////////////////////////////////////////////////////////////////
#pragma once

#include <boost/filesystem/path.hpp>

namespace nemo
{

/**
 * \brief
 * Utility class for paths to game's resource directories.
 */
class GameRoot
{
public:
	/**
	 * \brief  Gets path to game's root directory.
	 * \return Absolute path to game root.
	 */
	static boost::filesystem::path
	getRootDir();

	/**
	 * \brief  Gets path to game's main asset directory.
	 * \return Absolute path to main assets.
	 */
	static boost::filesystem::path
	getAssetDir();

	/**
	 * \brief  Gets path to game's sprite directory
	 * \return Absolute path to sprites.
	 */
	static boost::filesystem::path
	getSpriteDir();
};

} // namespace nemo