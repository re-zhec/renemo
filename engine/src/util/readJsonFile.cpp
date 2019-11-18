////////////////////////////////////////////////////////////////////////////////
/// \copyright MIT License                                                   ///
/// \author    Caylen Lee                                                    ///
/// \date      2019                                                          ///
////////////////////////////////////////////////////////////////////////////////
#include "util/readJsonFile.hpp"
#include "util/debug.hpp"

#include <fstream>

namespace nemo::util
{

////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

std::optional< nlohmann::json >
readJsonFile(const std::filesystem::path& file)
{
	nlohmann::json json;

	try {
		std::ifstream ifs;
		ifs.exceptions(std::ifstream::failbit | std::ifstream::badbit);
		ifs.open(file);

		json = nlohmann::json::parse(ifs);
	}
	catch (const nlohmann::json::parse_error& e) {
		STDERR("Parse json error in " << file);
		STDERR(e.what());
		return {};
	}
	catch (const std::ios_base::failure& e) {
		STDERR("Read I/O failure in " << file);
		STDERR(e.what() << " : " << e.code());
		return {};
	}
	catch (...) {
		STDERR("Unknown failure in " << file);
		return {};
	}

	return json;
}

////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

}