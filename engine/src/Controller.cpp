////////////////////////////////////////////////////////////////////////////////
/// \copyright MIT License                                                   ///
/// \author    Caylen Lee                                                    ///
/// \date      2019                                                          ///
////////////////////////////////////////////////////////////////////////////////
#include "Controller.hpp"
#include "util/readJsonFile.hpp"
#include "util/debug.hpp"
#include "constants.hpp"

#include <nlohmann/json.hpp>
#include <magic_enum.hpp>
#include <boost/assign/list_of.hpp>

#include <fstream>
#include <string>
#include <algorithm>
#include <vector>

namespace nemo
{

////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

namespace
{
	// Default path to a directory of keyboard mapping files.
	const std::filesystem::path controller_dir_ = constants::_asset_dir / 
		"controller";
}

////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

std::deque< Controller::key_t >
Controller::_pressed_keys = {};

////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

Controller::Controller()
{
	useDefaultKeyMappings();
}

////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

Controller::Controller(const std::filesystem::path& file)
	: _config_file(file)
{
	const std::optional< nlohmann::json > 
		config = util::readJsonFile(_config_file);

	if (!config) {
		OBJ_STDWARN("Failed to read controller config file " << _config_file);
		useDefaultKeyMappings();
		return;
	}
		
	for (const auto& [button_field, keycode] : config->items()) {
		// Warning message to issue should this particular mapping fails.
		const auto warn_skipped_mapping = 
			[this, b = &button_field, k = keycode] () {
			OBJ_STDWARN(
				"Skipped mapping [" << b << "] to key " << k << " in " << 
				_config_file
			); 
		};

		// Identify controller button from json property's key name.
		const auto button = magic_enum::enum_cast< Button >(button_field);

		if (!button) {
			OBJ_STDWARN("Unknown control found: [" << button_field << "]");
			warn_skipped_mapping();
			continue;
		}

		// Keys are represented as integers in the json file.
		const auto key = magic_enum::enum_cast< key_t >(keycode);
		
		if (!key) {
			OBJ_STDWARN("Invalid key found: " << keycode);
			warn_skipped_mapping();
			continue;
		}

		// Add new mapping.
		changeKeyMapping(*key, *button);
	}

	if (!isValidController()) {
		OBJ_STDWARN("Incomplete mapping(s) in " << _config_file);
		useDefaultKeyMappings();
		return;
	}

	OBJ_STDINFO("Used keyboard mapping config from " << _config_file);
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
	OBJ_STDINFO("Used default keyboard mapping for controller");

	changeKeyMapping(key_t::A,     Button::Left  );
	changeKeyMapping(key_t::W,     Button::Up    );
	changeKeyMapping(key_t::D,     Button::Right );
	changeKeyMapping(key_t::S,     Button::Down  );
	changeKeyMapping(key_t::Q,     Button::Cancel);
	changeKeyMapping(key_t::P,     Button::Pause );
	changeKeyMapping(key_t::Enter, Button::Select);

	if (!isValidController()) {
		STDERR("Default keyboard mapping needs to change");
	}
}

////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

void
Controller::registerKeyPress(const key_t key)
{
	if (std::any_of(
		_pressed_keys.cbegin(), _pressed_keys.cend(), 
		[key] (const key_t p) { return p == key; }
	)) {
		// Avoid adding a key already being pressed to the list of pressed keys.
		return;
	}

	// Newly pressed key.
	_pressed_keys.push_front(key);
	STDDEBUG("Key " << key << " pressed");
}

////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

void
Controller::registerKeyRelease(const key_t key)
{
	// Remove key from the list of pressed keys.
	const auto keys_to_remove = std::remove(
		_pressed_keys.begin(), _pressed_keys.end(), key
	);

	_pressed_keys.erase(keys_to_remove, _pressed_keys.end());
	STDDEBUG("Key " << key << " released");
}

////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

std::optional< Button >
Controller::pressedDirection()
const
{
	const static std::vector< Button > limit_buttons_to = { 
		Button::Left, Button::Up, Button::Right, Button::Down
	};

	// Limit the query to directional buttons only.
	return pressedButton(limit_buttons_to);
}

////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

std::optional< Button >
Controller::pressedSelection()
const
{
	const static std::vector< Button > limit_buttons_to = { 
		Button::Cancel, Button::Select, Button::Pause
	};

	// Limit the query to selection buttons only.
	return pressedButton(limit_buttons_to);
}

////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

std::optional< Button >
Controller::pressedButton(const std::vector< Button > button_filters)
const
{
	// Prioritize more recently pressed keys. If the up button is pressed while 
	// the left button is still pressed, for example, the up button will be used 
	// instead of the left button as long as both buttons are held (assuming 
	// we're looking for any directional input).
	for (const key_t k : _pressed_keys) {
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

		const auto button_field = magic_enum::enum_name(button);
		OBJ_STDDEBUG("Found [" << button_field << "] being pressed.");

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
Controller::saveKeyMappings(const std::filesystem::path& file)
const
{
	std::error_code ec;
	std::filesystem::create_directories(file.parent_path(), ec);
	std::ofstream config_ofs(file);

	if (!config_ofs) {
		OBJ_STDWARN("Failed to create " << file);
		return false;
	}

	nlohmann::json config;

	for (const auto& [key, button] : _key_mappings.right) {
		// Use the controller input's name as the json property's key.
		const auto button_field = std::string(magic_enum::enum_name(button));
		config[button_field] = key;
	}

	// Dump json to file, using a 4-space indentation.
	config_ofs << config.dump(4);

	if (!config_ofs) {
		OBJ_STDWARN("Write error in " << file);
		return false;
	}

	OBJ_STDINFO("Saved settings to " << file);
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

} 