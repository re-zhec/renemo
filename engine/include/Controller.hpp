////////////////////////////////////////////////////////////////////////////////
/// \copyright MIT License                                                   ///
/// \author    Caylen Lee                                                    ///
/// \date      2019                                                          ///
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
 * \brief
 * Enumeration for controller buttons.
 */
enum class Button {
	Left, 
	Up,
	Right,
	Down,
	Cancel,
	Select,
	Pause
};

////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

/**
 * \class
 * Controller
 * 
 * \brief
 * Keyboard controller.
 * 
 * This class maps keyboard input to controls in the game. Instead of reading 
 * what key is pressed or released, the client code would read the "controller 
 * button" that is being pressed or released. This class also allows the player 
 * to change what keyboard key translates to which input command if, say, the 
 * default mapping doesn't work out for any reason.
 * 
 * Usage example:
 * \code
 * 	sf::RenderWindow window(sf::VideoMode(1280, 720), "Nemo");
 * 	window.setKeyRepeatEnabled(false);
 *  
 * 	nemo::Controller controller;
 * 	controller.changeKeyMapping(sf::Keyboard::O, Button::Cancel);
 * 	
 * 	while (window.isOpen()) {
 *		sf::Event event;
 * 
 * 		if (!window.pollEvent(event)) {
 * 			continue;
 * 		}
 *     	
 * 		switch (event.type) {
 * 			case sf::Event::KeyPressed:
 * 			nemo::Controller::registerKeyPress(event.key.code);
 * 			break;
 * 
 * 			case sf::Event::KeyReleased:
 * 			nemo::Controller::registerKeyRelease(event.key.code);
 * 			break;
 * 		}
 *    	
 * 		if (!controller->getPressedButton()) {
 * 			continue;
 * 		}
 * 
 * 		switch (*controller->getPressedButton()) {
 * 			case Button::left:
 * 			// move left
 * 			break;
 * 
 * 			case Button::Right:
 * 			// move right
 * 			break;
 * 		}
 *	}
 * \endcode
 */
class Controller
{
public:
	/**
	 * \brief
	 * Constructs a controller that has default key mappings.
	 */
	Controller();

	/**
	 * \brief
	 * Constructs a controller using keyboard mappings from a file.
	 * 
	 * \param file
	 * Path to the keyboard mapping file.
	 * 
	 * The keyboard mapping file is a json, where each property is a controller 
	 * button and its value is an integer that identifies a keyboard key. This 
	 * is an example of a valid key mapping json:
	 * 
	 * \code
	 * {
	 *     "down":   18, // S key
	 *     "left":   0,  // A key
	 *     "right":  3,  // D key
	 *     "up":     22, // W key
	 *     "cancel": 16, // Q key
	 *     "pause":  15, // P key
	 *     "select": 58  // Enter key
	 * }
	 * \endcode
	 * 
	 * All of the above properties must be used and have proper key code values. 
	 * Otherwise, if any of them are missing, or if a value references a 
	 * nonexistent key, or any parse or other file-reading errors occurred, then 
	 * the controller will use the default keyboard mapping.
	 */
	Controller(const boost::filesystem::path& file);

	/**
	 * \brief
	 * Destructor that optionally saves the controller's current key mappings to
	 * a file.
	 * 
	 * When a controller that was constructed with a key mapping file is 
	 * destructed, regardless whether the original configurations were 
	 * successfully loaded or the default keyboard mapping had to be used, the 
	 * destructor will overwrite or create the file with the controller's 
	 * current keyboard mapping.
	 */
	virtual 
	~Controller();

	/**
	 * \brief
	 * Adds a keyboard key to a queue of currently pressed keys.
	 * 
	 * \param key
	 * Pressed keyboard key.
	 * 
	 * All controller objects shared access to a single queue of currently 
	 * pressed keys, which they will translate to controller buttons based on 
	 * their individual keyboard mapping. A key added to this queue stays in it
	 * until \link registerKeyRelease is called with the same key as the 
	 * argument.
	 * 
	 * Usage-wise, this means that when a player presses a key, call \link 
	 * registerKeyPress for that key, and once the player releases the key, call 
	 * \link registerKeyRelease.
	 */
	static void
	registerKeyPress(const sf::Keyboard::Key key);

	/**
	 * \brief
	 * Removes a keyboard key from a queue of currently pressed keys.
	 * 
	 * \param key
	 * Released key.
	 * 
	 * All controller objects shared access to a single queue of currently 
	 * pressed keys, which they will translate to controller buttons based on 
	 * their individual keyboard mapping. The only way to remove a keyboard key 
	 * that has been added to the queue, particularly after the player releases 
	 * the key, is to call this method. Otherwise, all controller objects will 
	 * still think the released key is still being pressed.
	 */
	static void
	registerKeyRelease(const sf::Keyboard::Key key);

	/**
	 * \brief
	 * Gets a currently pressed directional button.
	 * 
	 * Directional buttons consist of the left, up, right, and down button. This 
	 * method will return one of them if its mapped keyboard key is pressed. 
	 * If more than one of these buttons are currently pressed, then this method 
	 * will return the most recently pressed one.
	 * 
	 * If no directional buttons are currently pressed, this method will return
	 * a \link std::nullopt.
	 * 
	 * \return 
	 * Currently pressed directional button, if any.
	 */
	std::optional< Button >
	getPressedDirection()
	const;

	/**
	 * \brief
	 * Gets a currently pressed selection button.
	 * 
	 * Selection buttons consist of the select, cancel, and pause button. This 
	 * method will return one of them if its mapped keyboard key is pressed. 
	 * If more than one of these buttons are currently pressed, then this method 
	 * will return the most recently pressed one.
	 * 
	 * If no selection buttons are currently pressed, this method will return a 
	 * \link std::nullopt.
	 * 
	 * \return 
	 * Currently pressed selection button, if any.
	 */
	std::optional< Button >
	getPressedSelection()
	const;

	/**
	 * \brief 
	 * Gets a currently pressed button.
	 * 
	 * \param button_filters
	 * Buttons to limit the returned result to.
	 * 
	 * If \a button_filters is empty or not used, then this method will any 
	 * controller button that is currently pressed. Otherwise, it will return 
	 * one of the buttons in the filter list. This is a more customized button 
	 * query than \link getPressedDirection and \link getPressedSelection.
	 * 
	 * If more than one of the requested buttons are currently pressed, then 
	 * this method will return the most recently pressed one. If none of the 
	 * requested buttons are currently pressed, this method will return a \link
	 * std::nullopt.
	 * 
	 * \return
	 * Currently pressed button among \a button_filters, if any.
	 */
	std::optional< Button >
	getPressedButton(const std::vector< Button > button_filters = {})
	const;
	
	/**
	 * \brief
	 * Changes the key that a controller button is mapped to.
	 * 
	 * \param keycode    Code number of the key to map.
	 * \param button     Button that key will be mapped to.
	 * 
	 * Each controller button is to be mapped to one unique keyboard key only. 
	 * Likewise, one keyboard key cannot be mapped to multiple controller 
	 * buttons. If \a keycode and \a button haven't been mapped before, then 
	 * this method will simply create the new mapping. On the other hand, if \a
	 * keycode OR \a button are each already mapped to something else, those 
	 * mapping will be removed to allow the new mapping between \a keycode and 
	 * \a button.
	 * 
	 * Because of this behavior, it is possible to have a controller with 
	 * unmapped buttons. \link isValidController should be called after 
	 * changing the keyboard mapping to check whether any buttons are left 
	 * unmapped.
	 * 
	 * \warning
	 * It is possible for this method to fail and return a false. In this case, 
	 * the previous mapping is kept. Key codes are represented as integers in 
	 * a json, and to protect against users entering any integer for a key, 
	 * the method checks that \a keycode is a valid \link sf::Keyboard::Key enum
	 * value.
	 * 
	 * \return
	 * False if \a keycode is not within \link sf::Keyboard::Key's enum range.
	 * True if otherwise.
	 */
	bool
	changeKeyMapping(const int keycode, const Button button);

	/**
	 * \brief
	 * Check whether the current keyboard mapping is valid.
	 * 
	 * The keyboard mapping is valid if and only if each controller button is 
	 * mapped to a unique keyboard key. It is not possible to have multiple 
	 * keys mapped to one button and vice versa. This should be called after all
	 * \link changeKeyMapping.
	 * 
	 * \return
	 * True if the keyboard mapping is valid, false otherwise.
	 */
	bool
	isValidController()
	const noexcept;

	/**
	 * \brief 
	 * Saves current keyboard mappings to a file.
	 * 
	 * \param file
	 * Filepath to save current mappings to.
	 * 
	 * This method will create, or overwrite the existing file with, a json 
	 * file. If the file's parent path does not exist, the method will 
	 * recursively create the directories that don't exist. If any of the 
	 * nonexistent directories failed to be created, or if the method failed to 
	 * create or overwrite the file, the returned value will be false.
	 * 
	 * \return
	 * True if save is successful, false otherwise.
	 * 
	 * \see
	 * Controller for the json contents.
	 */
	bool
	saveKeyMappings(const boost::filesystem::path& file)
	const;

private:
	/**
	 * \brief
	 * Change current keyboard mappings to the default.
	 * 
	 * The default key => button mapping is the following:
	 *     A     => Left
	 *     W     => Up
	 *     D     => Right
	 *     S     => Down
	 *     Q     => Cancel
	 *     P     => Pause
	 *     Enter => Select
	 */
	void
	useDefaultKeyMappings();

	// Type alias
	using keyboard_to_controller_t = boost::bimap< 
		boost::bimaps::unordered_set_of< sf::Keyboard::Key >,
		boost::bimaps::unordered_set_of< Button >,
		boost::bimaps::list_of_relation
	>;

	/// Path to controller's keyboard mapping file.
	boost::filesystem::path                 _config_file;

	/// Bidrectional key-to-button mappings.
	keyboard_to_controller_t                _key_mappings;

	/// Keyboard keys the player is currently pressing.
	static std::vector< sf::Keyboard::Key > _pressed_keys;
};

////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

/**
 * \brief
 * Player controller.
 */
class PlayerController : public Controller
{
public:
	/**
	 * \brief 
	 * Constructs a controller using keyboard mappings found in
	 * asset/controller/player.json.
	 * 
	 * \remark
	 * If the file doesn't exist, the default keyboard mapping will be used. 
	 * Either way, upon destruction, this object will save its mappings to the 
	 * file.
	 */
	PlayerController();
};

////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

/**
 * \brief
 * Enemy character controller
 */
class EnemyController : public Controller
{
public:
	/**
	 * \brief
	 * Constructs a controller using keyboard mappings found in
	 * asset/controller/enemy.json.
	 * 
	 * \remark
	 * If the file doesn't exist, the default keyboard mapping will be used. 
	 * Either way, upon destruction, this object will save its mappings to the 
	 * file. This class is intended to test enemy actions.
	 */
	EnemyController();
};

////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

} // namespace nemo