////////////////////////////////////////////////////////////////////////////////
/// \copyright MIT License                                                   ///
/// \author    Caylen Lee                                                    ///
/// \date      2019                                                          ///
////////////////////////////////////////////////////////////////////////////////
#pragma once
#define SPDLOG_TRACE_ON
#define SPDLOG_ACTIVE_LEVEL SPDLOG_LEVEL_TRACE

#include <spdlog/spdlog.h>
#include <spdlog/fmt/ostr.h>

#include <memory>
#include <ostream>
#include <filesystem>

namespace nemo::util
{

std::shared_ptr< spdlog::logger >
logger();

}

std::ostream&
operator << (std::ostream& os, const std::filesystem::path& p);

#define NEMO_TRACE(...)    SPDLOG_LOGGER_TRACE(nemo::util::logger(), __VA_ARGS__)
#define NEMO_DEBUG(...)    SPDLOG_LOGGER_DEBUG(nemo::util::logger(), __VA_ARGS__)
#define NEMO_INFO(...)     SPDLOG_LOGGER_INFO(nemo::util::logger(), __VA_ARGS__)
#define NEMO_WARN(...)     SPDLOG_LOGGER_WARN(nemo::util::logger(), __VA_ARGS__)
#define NEMO_ERROR(...)    SPDLOG_LOGGER_ERROR(nemo::util::logger(), __VA_ARGS__)
#define NEMO_CRITICAL(...) SPDLOG_LOGGER_CRITICAL(nemo::util::logger(), __VA_ARGS__)