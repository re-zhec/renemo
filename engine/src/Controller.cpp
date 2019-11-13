////////////////////////////////////////////////////////////////////////////////
/// \copyright MIT License                                                   ///
/// \author    Caylen Lee                                                    ///
/// \date      2019                                                          ///
////////////////////////////////////////////////////////////////////////////////
#include "Controller.hpp"
#include "debug.hpp"
#include "GameRoot.hpp"

#include <fstream>
#include <string>
#include <algorithm>

#include <boost/assign/list_of.hpp>
#include <boost/range/adaptor/reversed.hpp>
#include <boost/filesystem.hpp>
#include <nlohmann/json.hpp>
#include <magic_enum.hpp>

namespace nemo
{

////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

namespace
{
	// Default path to a directory for keyboard mapping files.
	const boost::filesystem::path controller_dir_ = GameRoot::getAssetDir() 
		/ "controller";
}

////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

std::vector< Controller::key_t >
Controller::_pressed_keys = {};

////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

Controller::Controller()
{
	useDefaultKeyMappings();
}

////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

Controller::Controller(const boost::filesystem::path& file)
	: _config_file(file)
{
	std::ifstream config_ifs(_config_file.string());

	if (!config_ifs) {
		STDWARN("Failed to open " << _config_file);
		useDefaultKeyMappings();
		return;
	}

	nlohmann::json config;
	
	try {
		config = nlohmann::json::parse(config_ifs);
	} 
	catch (const nlohmann::json::parse_error& e) {
		STDWARN("Parse error in " << _config_file);
		useDefaultKeyMappings();
		return;
	}
		
	for (const auto& [button_field, keycode] : config.items()) {
		// Warning message to issue should this particular mapping fails.
		const auto warn_skipped_mapping = [b = &button_field, k = keycode] () {
			STDWARN("Skipped mapping [" << b << "] to key " << k);
		};

		// Identify controller button from json property name.
		const auto button = magic_enum::enum_cast< Button >(button_field);

		if (!button) {
			STDWARN("Unknown control found: [" << button_field << "]");
			warn_skipped_mapping();
			continue;
		}

		// Keys are represented as integers in the json file.
		const auto key = magic_enum::enum_cast< key_t >(keycode);
		
		if (!key) {
			STDWARN("Invalid key: " << keycode);
			warn_skipped_mapping();
			continue;
		}

		// Add new mapping.
		changeKeyMapping(*key, *button);
	}

	if (!isValidController()) {
		STDWARN("Incomplete/missing mapping(s) in " << _config_file);
		useDefaultKeyMappings();
		return;
	}

	STDINFO("Loaded " << _config_file << " config for controller " << this);
}

////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

Controller::~Controller()
{
	if (_config_file.empty()) {
		return;
	}

	saveKeyMappings(_config_file);
}

////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

void
Controller::useDefaultKeyMappings()
{
	STDINFO("Used default key mapping for controller " << this);

	changeKeyMapping(key_t::A,     Button::Left  );
	changeKeyMapping(key_t::W,     Button::Up    );
	changeKeyMapping(key_t::D,     Button::Right );
	changeKeyMapping(key_t::S,     Button::Down  );
	changeKeyMapping(key_t::Q,     Button::Cancel);
	changeKeyMapping(key_t::P,     Button::Pause );
	changeKeyMapping(key_t::Enter, Button::Select);

	if (!isValidController()) {
		STDERR("Default key mapping needs to change");
	}
}

////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

void
Controller::registerKeyPress(const key_t key)
{
	// Avoid adding a key already being pressed to the list of pressed keys.
	if (std::none_of(
		_pressed_keys.cbegin(), _pressed_keys.cend(), 
		[key] (const key_t p) { return p == key; }
	)) {
		// Newly pressed key.
		_pressed_keys.push_back(key);
		STDINFO("Key " << key << " pressed");
	}
}

////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

void
Controller::registerKeyRelease(const key_t key)
{
	// Remove key from the list of pressed keys.
	auto keys_to_rm = std::remove(_pressed_keys.begin(), _pressed_keys.end(), key);
	_pressed_keys.erase(keys_to_rm, _pressed_keys.end());
	STDINFO("Key " << key << " released");
}

////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

std::optional< Button >
Controller::getPressedDirection()
const
{
	const static std::vector< Button > limit_buttons_to = { 
		Button::Left, Button::Up, Button::Right, Button::Down
	};

	// Limit the query to directional buttons only.
	return getPressedButton(limit_buttons_to);
}

////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

std::optional< Button >
Controller::getPressedSelection()
const
{
	const static std::vector< Button > limit_buttons_to = { 
		Button::Cancel, Button::Select, Button::Pause
	};

	// Limit the query to selection buttons only.
	return getPressedButton(limit_buttons_to);
}

////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

std::optional< Button >
Controller::getPressedButton(const std::vector< Button > button_filters)
const
{
	// Iterating in reverse order priortizes more recently pressed keys. If the
	// up button is pressed while the left button is still pressed, for example,
	// the up button will be used instead of the left button as long as both 
	// buttons are held (assuming we're looking for any directional input).
	for (const key_t k : boost::adaptors::reverse(_pressed_keys)) {
		const auto key_to_button = _key_mappings.left.find(k);
		
		if (key_to_button == _key_mappings.left.end()) {
			// This pressed key isn't mapped to any control.
			continue;
		}

		const Button button = key_to_button->second;
		
		if (!button_filters.empty() && // button search filter is supplied
			std::none_of(
				button_filters.cbegin(), button_filters.cend(), 
				[button] (const Button allowed) { return allowed == button; }
			)) 
		{
			// The controller button mapped to this pressed key isn't one of the
			// buttons we are looking for.
			continue;
		}

		return button;
	}

	return {};
}

////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

void
Controller::changeKeyMapping(const key_t key, const Button button)
{
	// Delete whatever the control and key were previously mapped to. A key 
	// cannot be mapped to multiple controls, and vice versa.
	_key_mappings.left.erase(key);
	_key_mappings.right.erase(button);

	// Add new mapping.
	_key_mappings.push_back({ key, button });
}

////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

bool
Controller::saveKeyMappings(const boost::filesystem::path& file)
const
{
	boost::system::error_code ec;
	boost::filesystem::create_directories(file.parent_path(), ec);
	std::ofstream config_ofs(file.string());

	if (!config_ofs) {
		STDWARN("Failed to create " << file);
		return false;
	}

	nlohmann::json config;

	for (const auto& [key, button] : _key_mappings.right) {
		// Use the controller input's name as the json property name.
		const auto button_field = std::string(magic_enum::enum_name(button));
		config[button_field] = key;
	}

	// Dump json to file, using a 4-space indentation.
	config_ofs << config.dump(4);

	if (!config_ofs) {
		STDWARN("Write error in " << file);
		return false;
	}

	STDINFO("Saved controller " << this << " settings to " << file);
	return true;
}

////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

bool
Controller::isValidController()
const noexcept
{
	// With 1:1 bidrectional mapping being enforced, the controller is valid if 
	// we have the same number of mappings as the number of possible buttons.
	return _key_mappings.size() == magic_enum::enum_count< Button >();
}

////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

PlayerController::PlayerController()
	: Controller(controller_dir_ / "player.json")
{
}

////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

EnemyController::EnemyController()
	: Controller(controller_dir_ / "enemy.json")
{
}

////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

} // namespace nemo