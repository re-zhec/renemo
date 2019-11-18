////////////////////////////////////////////////////////////////////////////////
/// \copyright MIT License                                                   ///
/// \author    Caylen Lee                                                    ///
/// \date      2019                                                          ///
////////////////////////////////////////////////////////////////////////////////
#pragma once

#include <nlohmann/json.hpp>

#include <filesystem>
#include <optional>

namespace nemo::util
{
	/**
	 * \brief
	 */
	std::optional< nlohmann::json >
	readJsonFile(const std::filesystem::path& file);
}