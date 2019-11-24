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
const std::filesystem::path _log_dir    = _root_dir  / "log";
constexpr auto _tile_side_length        = 16;
constexpr auto _walking_speed           = 4;
constexpr auto _running_speed           = 8;

}