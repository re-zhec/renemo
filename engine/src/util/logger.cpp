////////////////////////////////////////////////////////////////////////////////
/// \copyright MIT License                                                   ///
/// \author    Caylen Lee                                                    ///
/// \date      2019                                                          ///
////////////////////////////////////////////////////////////////////////////////
#include "util/logger.hpp"
#include "constants.hpp"

#include <spdlog/sinks/basic_file_sink.h>
#include <spdlog/sinks/stdout_color_sinks.h>

#include <string_view>

namespace nemo::util
{

////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

std::shared_ptr< spdlog::logger >
logger()
{
	static auto init_global_logger = [] () {
		// Create console sink.
		const std::filesystem::path logfile = constants::_log_dir / "dump.log";
		auto console_sink = std::make_shared< spdlog::sinks::stdout_color_sink_mt >();
		console_sink->set_level(spdlog::level::trace);
		
		// Create text file sink.
		auto file_sink = std::make_shared< spdlog::sinks::basic_file_sink_mt >(
			logfile.string(), true
		);
		file_sink->set_level(spdlog::level::trace);

		// Logger to print to both sinks.
		spdlog::logger logger("nemo", {console_sink, file_sink});
		logger.set_level(spdlog::level::trace);
		return logger;
	};

	// Make logger a singleton.
	static auto logger = std::make_shared< spdlog::logger >(init_global_logger());
	return logger;
}

////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

}

std::ostream&
operator << (std::ostream& os, const std::filesystem::path& p)
{
	// Attempted to use c_str(), but addresses were printed instead.
	// Attempted basic_string_view on c_str(), but that led game to crash.
	return os << p.string();
}

////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////