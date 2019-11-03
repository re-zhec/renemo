////////////////////////////////////////////////////////////////////////////////
/// \copyright MIT License                                                   ///
/// \author    Caylen Lee                                                    ///
/// \date      2019                                                          ///
/// \file      Controller.hpp                                                ///
////////////////////////////////////////////////////////////////////////////////
#pragma once

#include <optional>
#include <vector>

#include <boost/bimap.hpp>
#include <boost/bimap/unordered_set_of.hpp>
#include <boost/bimap/list_of.hpp>
#include <boost/filesystem/path.hpp>
#include <SFML/Window/Keyboard.hpp>

namespace nemo
{

/**
 * \brief Enumeration for controller buttons.
 */
enum class Button
{
	Left = 0, 
	Up,
	Right,
	Down,
	Cancel,
	Select,
	Pause
};

/**
 * \brief Keyboard controller.
 */
class Controller
{
public:
	/**
	 * \brief Controller with default key mappings.
	 */
	Controller();

	/**
	 * \brief Controller with key mappings configured from a file.
	 * 
	 * \param file Path to file containing custom key mappings.
	 */
	Controller(const boost::filesystem::path& file);

	/**
	 * \brief Save controller's current key mappings to the optional file the 
	 * controller was constructed with.
	 */
	virtual 
	~Controller();

	/**
	 * \brief Signals to all controllers that a key is pressed.
	 * 
	 * \param key Pressed key.
	 */
	static void
	registerKeyPress(const sf::Keyboard::Key key);

	/**
	 * \brief Signals to all controllers that a key is released.
	 * 
	 * \param key Released key.
	 */
	static void
	registerKeyRelease(const sf::Keyboard::Key key);

	/**
	 * \brief Gets any directional button that is currently pressed.
	 * 
	 * \return Currently pressed directional button, if any.
	 */
	std::optional< Button >
	getPressedDirection()
	const;

	/**
	 * \brief Gets any selectional button that is currently pressed.
	 * 
	 * \return Currently pressed selectional button, if any.
	 */
	std::optional< Button >
	getPressedSelection()
	const;
	
	/**
	 * \brief Change the key that a controller button is be mapped to.
	 * 
	 * \param key    Key to map.
	 * \param button Button that key will be mapped to.
	 * 
	 * \return False if any controller button is unmapped after this change, true 
	 * otherwise.
	 * 
	 * \throw std::out_of_range if \a key is not within \ref sf::Keyboard::Key 
	 * enum range. No mapping change happens in this case.
	 */
	bool
	changeKeyMapping(const sf::Keyboard::Key key, const Button button);

	/**
	 * \brief Saves current key mappings for use on future game sessions.
	 * 
	 * \param file Filepath to save current mappings to.
	 * 
	 * \return True if save is successful, false otherwise.
	 */
	bool
	saveKeyMappings(const boost::filesystem::path& file)
	const;

private:
	/**
	 * \brief Gets a button that is currently pressed among a list of allowed 
	 * buttons.
	 * 
	 * \param allowed_buttons List of buttons to check whether one is currently 
	 * pressed.
	 * 
	 * \return Currently pressed button among that list, if any.
	 */
	std::optional< Button >
	getPressedButton(const std::vector< Button > allowed_buttons)
	const;

	/**
	 * \brief Change current key mappings to the default.
	 */
	void
	useDefaultKeyMappings();

	/**
	 * \brief Checks if this key code is an acceptable \ref sf::Keyboard::Key 
	 * value.
	 * 
	 * \param key Key code in question.
	 * 
	 * \return True if yes, false otherwise.
	 */
	static bool
	isKeyValid(const sf::Keyboard::Key key)
	noexcept;

	// Type alias
	using keyboard_to_controller_t = boost::bimap< 
		boost::bimaps::unordered_set_of< sf::Keyboard::Key >,
		boost::bimaps::unordered_set_of< Button >,
		boost::bimaps::list_of_relation
	>;

	/// Path to controller's configuration file.
	boost::filesystem::path               _config_file;

	/// Keys the player is currently pressing.
	static std::vector<sf::Keyboard::Key> _pressed_keys;

	/// Bidrectional key-to-button mappings.
	keyboard_to_controller_t              _key_mappings;
};

/**
 * \brief Player character controller.
 */
class PlayerController : public Controller
{
public:
	/**
	 * \brief Configure controller using settings from controller/player.json.
	 */
	PlayerController();
};

/**
 * \brief Enemy character controller using settings found in 
 * 
 * \remark This class allows testing for enemy action.
 */
class EnemyController : public Controller
{
public:
	/**
	 * \brief Configure controller using settings from controller/enemy.json.
	 */
	EnemyController();
};

} // namespace nemo