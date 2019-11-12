////////////////////////////////////////////////////////////////////////////////
/// \copyright MIT License                                                   ///
/// \author    Caylen Lee                                                    ///
/// \date      2019                                                          ///
////////////////////////////////////////////////////////////////////////////////

/**
 * \todo Replace \a fields_to_buttons_ and reimplement \link 
 * nemo::Controller::isValidKeyCode with Neargye's magic_enum 
 * (https://github.com/Neargye/magic_enum) when MinGW comes with GCC 9.0+ 
 * install.
 */

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

namespace nemo
{

////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

namespace
{
	using fields_to_controller_t = boost::bimap< 
		boost::bimaps::unordered_set_of< std::string >, 
		boost::bimaps::unordered_set_of< Button >,
		boost::bimaps::list_of_relation
	>;
	
	// Mapping JSON property names to their respective controller buttons.
	const static fields_to_controller_t fields_to_buttons_ 
		= boost::assign::list_of< fields_to_controller_t::relation >
		( "left"  , Button::Left   )
		( "up"    , Button::Up     )
		( "right" , Button::Right  )
		( "down"  , Button::Down   )
		( "cancel", Button::Cancel )
		( "select", Button::Select )
		( "pause" , Button::Pause  );

	// Default path to a directory for keyboard mapping files.
	const boost::filesystem::path controller_dir_ = GameRoot::getAssetDir() 
		/ "controller";


	// Checks if a key code is a valid sf::Keyboard::Key enum value.
	bool
	isValidKeyCode(const int keycode)
	noexcept
	{
		return keycode > static_cast< int >(sf::Keyboard::Unknown) &&
		keycode <= static_cast< int >(sf::Keyboard::Enter);
	}
}

////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

std::vector< sf::Keyboard::Key >
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
		
	for (const auto& [button_field, key] : config.items()) {
		bool valid_mapping = false;
		
		try {
			// Get the controller button associated with the JSON property name.
			const Button button = fields_to_buttons_.left.at(button_field);
			// Add new mapping.
			valid_mapping = changeKeyMapping(key, button);
		}
		catch (const std::out_of_range& e) {
			STDWARN(e.what());
		}

		if (!valid_mapping) {
			STDWARN("Skipped mapping [" << button_field << "] to key " << key);
		}
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

	changeKeyMapping(sf::Keyboard::A,     Button::Left  );
	changeKeyMapping(sf::Keyboard::W,     Button::Up    );
	changeKeyMapping(sf::Keyboard::D,     Button::Right );
	changeKeyMapping(sf::Keyboard::S,     Button::Down  );
	changeKeyMapping(sf::Keyboard::Q,     Button::Cancel);
	changeKeyMapping(sf::Keyboard::P,     Button::Pause );
	changeKeyMapping(sf::Keyboard::Enter, Button::Select);

	if (!isValidController()) {
		STDERR("Default key mapping needs to change");
	}
}

////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

void
Controller::registerKeyPress(const sf::Keyboard::Key key)
{
	if (!isValidKeyCode(key)) {
		return;
	}

	// Avoid adding a key that is already being pressed to the list of pressed 
	// keys.
	if (std::none_of(
		_pressed_keys.cbegin(), _pressed_keys.cend(), 
		[key] (const sf::Keyboard::Key p) { return p == key; }
	)) {
		// Newly pressed key.
		_pressed_keys.push_back(key);
		STDINFO("Key " << key << " pressed");
	}
}

////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

void
Controller::registerKeyRelease(const sf::Keyboard::Key key)
{
	if (!isValidKeyCode(key)) {
		return;
	}

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
	for (const auto k : boost::adaptors::reverse(_pressed_keys)) {
		const auto key_to_button = _key_mappings.left.find(k);
		
		if (key_to_button == _key_mappings.left.end()) {
			// This pressed key isn't mapped to any controller button.
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

bool
Controller::changeKeyMapping(const int keycode, const Button button)
{
	if (!isValidKeyCode(keycode)) {
		STDWARN("Invalid key " << keycode);
		return false;
	}

	const sf::Keyboard::Key key = static_cast< sf::Keyboard::Key>(keycode);

	// Delete whatever the button and key were previously mapped to. A key 
	// cannot be mapped to multiple buttons, and vice versa.
	_key_mappings.left.erase(key);
	_key_mappings.right.erase(button);

	// Add new mapping.
	_key_mappings.push_back(keyboard_to_controller_t::value_type(key, button));
	return true;
}

////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

bool
Controller::saveKeyMappings(const boost::filesystem::path& file)
const
{
	try {
		boost::filesystem::create_directories(file.parent_path());
	}
	catch (const boost::system::error_code& ec) {
		STDWARN("Failed to create " << controller_dir_);
		return false;
	}

	std::ofstream config_ofs(file.string());

	if (!config_ofs) {
		STDWARN("Failed to create " << file << " for controller " << this);
		return false;
	}

	nlohmann::json config;

	for (const auto& [key, button] : _key_mappings.right) {
		assert(
			fields_to_buttons_.right.find(button) !=
			fields_to_buttons_.right.end()
		);

		// Get the button's json property name.
		const std::string button_field = fields_to_buttons_.right.at(button);
		config[button_field] = key;
	}

	// Dump json to file, using an indentation of 4 spaces.
	config_ofs << config.dump(4);
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
	return _key_mappings.size() == fields_to_buttons_.size();
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