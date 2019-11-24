////////////////////////////////////////////////////////////////////////////////
/// \copyright MIT License                                                   ///
/// \author    Caylen Lee                                                    ///
/// \date      2019                                                          ///
////////////////////////////////////////////////////////////////////////////////
#include "Controller.hpp"
#include "util/readJsonFile.hpp"
#include "util/logger.hpp"
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
		NEMO_WARN("Failed reading controller file {}", _config_file);
		useDefaultKeyMappings();
		return;
	}

	// Warning message to issue should a particular mapping fails.
	const auto warn_skipped_mapping = 
		[f = _config_file] (const std::string& but, const int key) {
			NEMO_WARN("Skipped [{}] -> key {} mapping in {}", but, key, f);
	};
		
	for (const auto& [button_field, keycode] : config->items()) {
		// Identify controller button from json property's key name.
		const auto button = magic_enum::enum_cast< Button >(button_field);

		if (!button) {
			NEMO_WARN("Unknown control [{}] in {}", button_field, _config_file);
			warn_skipped_mapping(button_field, keycode);
			continue;
		}

		// Keys are represented as integers in the json file.
		const auto key = magic_enum::enum_cast< key_t >(keycode);
		
		if (!key) {
			NEMO_WARN("Invalid key {} in {}", keycode, _config_file);
			warn_skipped_mapping(button_field, keycode);
			continue;
		}

		// Add new mapping.
		changeKeyMapping(*key, *button);
	}

	if (!isValidController()) {
		NEMO_WARN("{} has incomplete mapping(s)", _config_file);
		useDefaultKeyMappings();
		return;
	}

	NEMO_INFO("Used keyboard mapping from {}", _config_file);
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
	NEMO_INFO("Used default keyboard mapping for controller");

	changeKeyMapping(key_t::A,     Button::Left  );
	changeKeyMapping(key_t::W,     Button::Up    );
	changeKeyMapping(key_t::D,     Button::Right );
	changeKeyMapping(key_t::S,     Button::Down  );
	changeKeyMapping(key_t::Q,     Button::Cancel);
	changeKeyMapping(key_t::P,     Button::Pause );
	changeKeyMapping(key_t::Enter, Button::Select);

	if (!isValidController()) {
		NEMO_ERROR("Default keyboard mapping needs to change");
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
	NEMO_DEBUG("Key {} pressed", key);
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
	NEMO_DEBUG("Key {} released", key);
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

		NEMO_DEBUG("Found [{}] being pressed", magic_enum::enum_name(button));

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
		NEMO_WARN("Failed to create {}", file);
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
		NEMO_WARN("Write error in {}", file);
		return false;
	}

	NEMO_INFO("Saved settings to {}", file);
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