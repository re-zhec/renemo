////////////////////////////////////////////////////////////////////////////////
/// \copyright MIT License                                                   ///
/// \author    Caylen Lee                                                    ///
/// \date      2019                                                          ///
////////////////////////////////////////////////////////////////////////////////
#pragma once

/**
 * \brief
 * Compile-time log configurations.
 * 
 * \remark
 * These must be defined before including the spdlog library.
 */
#define SPDLOG_TRACE_ON /// Includes source file and line number in messages.
#define SPDLOG_ACTIVE_LEVEL SPDLOG_LEVEL_TRACE /// Log level threshold.

#include <spdlog/spdlog.h>
#include <spdlog/fmt/ostr.h>

#include <memory>
#include <ostream>
#include <filesystem>

namespace nemo::util
{

/**
 * \brief
 * Get an instance to the global logger singleton.
 * 
 * This logger is configured to print messages to both the console and a text 
 * file. Each message includes the source file and line number where it 
 * originated. The log files can be found at located at log/.
 * 
 * \return
 * Instance to global logger singleton.
 */
std::shared_ptr< spdlog::logger >
logger();

}

/**
 * \brief
 * Overloads std::ofstream's (<<) operator for filesystem path types.
 * 
 * \ref spdlog doesn't support printing std::filesystem::path values directly by
 * default. The client would need to use path::string(). This operator overload 
 * automates that process to allow direct use of path types.
 * 
 * \param os    Output stream.
 * \param p     Filepath to print.
 * 
 * \return Updated output stream.
 */
std::ostream&
operator << (std::ostream& os, const std::filesystem::path& p);

/**
 * \brief
 * Convenience logging macros.
 */
#define NEMO_TRACE(...) SPDLOG_LOGGER_TRACE(nemo::util::logger(), __VA_ARGS__)
#define NEMO_DEBUG(...) SPDLOG_LOGGER_DEBUG(nemo::util::logger(), __VA_ARGS__)
#define NEMO_INFO(...)  SPDLOG_LOGGER_INFO(nemo::util::logger(), __VA_ARGS__)
#define NEMO_WARN(...)  SPDLOG_LOGGER_WARN(nemo::util::logger(), __VA_ARGS__)
#define NEMO_ERROR(...) SPDLOG_LOGGER_ERROR(nemo::util::logger(), __VA_ARGS__)
#define NEMO_CRITICAL(...) SPDLOG_LOGGER_CRITICAL(nemo::util::logger(), __VA_ARGS__)