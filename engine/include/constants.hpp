////////////////////////////////////////////////////////////////////////////////
/// \copyright MIT License                                                   ///
/// \author    Caylen Lee                                                    ///
/// \date      2019                                                          ///
////////////////////////////////////////////////////////////////////////////////
#pragma once

#include <filesystem>

namespace nemo::constants
{

const std::filesystem::path _root_dir   = std::filesystem::current_path();
const std::filesystem::path _asset_dir  = _root_dir  / "asset";
const std::filesystem::path _sprite_dir = _asset_dir / "sprite";
constexpr int _tile_pixel_length        = 16;

} // namespace nemo::constants