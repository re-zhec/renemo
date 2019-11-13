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
 * Enumeration for controller inputs.
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
 * This class translates keyboard input to controls in the game. Instead of 
 * reading what key is pressed or released, the client code can read the control 
 * that is being executed and react accordingly. This class also allows the 
 * player to change what keyboard key translates to which controller input if, 
 * for example, the default mapping doesn't work out for any reason.
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
	// Type alias.
	using key_t = sf::Keyboard::Key;
	using keyboard_to_controller_t = boost::bimap< 
		boost::bimaps::unordered_set_of< key_t >,
		boost::bimaps::unordered_set_of< Button >,
		boost::bimaps::list_of_relation
	>;

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
	 * The keyboard mapping file is a json, where each property is a control and
	 * its value is an integer that identifies a keyboard key. This is an 
	 * example of a valid keyboard mapping json:
	 * 
	 * \code
	 * {
	 *     "Down":   18, // S key
	 *     "Left":   0,  // A key
	 *     "Right":  3,  // D key
	 *     "Up":     22, // W key
	 *     "Cancel": 16, // Q key
	 *     "Pause":  15, // P key
	 *     "Select": 58  // Enter key
	 * }
	 * \endcode
	 * 
	 * All of the above properties must be used and have proper key code values. 
	 * Otherwise, if any of them are missing, if a value references a 
	 * nonexistent key, or if any parse or other file-reading errors occurred, 
	 * then the controller will use the default keyboard mapping.
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
	 * Pushes a keyboard key into a queue of currently pressed keys.
	 * 
	 * \param key
	 * Pressed keyboard key.
	 * 
	 * All controller objects shared access to a single queue of currently 
	 * pressed keys, which they will translate to executed controls based on 
	 * their individual keyboard mappings. A key pushed into this queue stays in 
	 * it until \link registerKeyRelease is called with the same key as the 
	 * argument.
	 * 
	 * Usage-wise, when a player presses a key, call \link registerKeyPress for 
	 * that key, and once the player releases that key, call \link 
	 * registerKeyRelease.
	 */
	static void
	registerKeyPress(const key_t key);

	template< typename T >
	static void
	registerKeyPress(const T key) = delete;

	/**
	 * \brief
	 * Removes a keyboard key from a queue of currently pressed keys.
	 * 
	 * \param key
	 * Released key.
	 * 
	 * All controller objects shared access to a single queue of currently 
	 * pressed keys, which they will translate to executed controls based on 
	 * their individual keyboard mappings. The only way to remove a key that 
	 * has been added to the queue, particularly after the player releases the
	 * key, is to call this method. Otherwise, all controller objects will still
	 * think the released key is still being pressed.
	 */
	static void
	registerKeyRelease(const key_t key);

	template< typename T >
	static void
	registerKeyRelease(const T key) = delete;

	/**
	 * \brief
	 * Gets a directional input based on keys currently pressed.
	 * 
	 * Directional inputs consist of the left, up, right, and down controls.
	 * This method will return one of them if its mapped keyboard key is 
	 * pressed. If more than one of the keys mapped to these controls are
	 * currently pressed, then this method will return the directional input 
	 * corresponding to the latest pressed one.
	 * 
	 * If no keys corresponding to directional inputs are currently pressed, 
	 * this method will return a nullopt.
	 * 
	 * \return 
	 * Directional input, if any.
	 */
	std::optional< Button >
	getPressedDirection()
	const;

	/**
	 * \brief
	 * Gets a selection input based on keys currently pressed.
	 * 
	 * Selection inputs consist of the select, cancel, and pause controls. This 
	 * method will return one of them if its mapped keyboard key is pressed. 
	 * If more than one of the keys mapped to these controls are currently 
	 * currently pressed, then this method will return the selection input 
	 * corresponding to the latest pressed one.
	 * 
	 * If no keys corresponding to selection inputs are currently pressed, this 
	 * method will return a nullopt.
	 * 
	 * \return 
	 * Selection input, if any.
	 */
	std::optional< Button >
	getPressedSelection()
	const;

	/**
	 * \brief 
	 * Gets a controller input based on keys currently pressed.
	 * 
	 * \param button_filters
	 * Controls to limit the returned result to.
	 * 
	 * If \a button_filters is empty or not used, then this method will return 
	 * any control that is mapped to the keys currently pressed. Otherwise, it 
	 * will return one of the controls in the filter list. This is a more 
	 * customized query than \link getPressedDirection and \link 
	 * getPressedSelection.
	 * 
	 * If more than one of the keys mapped to the requested controls are 
	 * currently pressed, then this method will return the control corresponding
	 * to the latest pressed one. If no keys corresponding to any controller 
	 * input are currently pressed, this method will return a nullopt.
	 * 
	 * \return
	 * Controller input among \a button_filters, if any.
	 */
	std::optional< Button >
	getPressedButton(const std::vector< Button > button_filters = {})
	const;
	
	/**
	 * \brief
	 * Changes the key that a control is mapped to.
	 * 
	 * \param key       Key to map.
	 * \param button    Control that key will be mapped to.
	 * 
	 * Each control is to be mapped to one unique keyboard key only. Likewise, 
	 * one key cannot be mapped to multiple controls. If \a key and \a button 
	 * haven't been mapped before, then this method will simply create the new 
	 * mapping. On the other hand, if \a key or \a button is individually 
	 * already mapped to something else, those mappings will be removed to allow
	 * the new mapping between \a key and \a button.
	 * 
	 * Because of this behavior, it is possible to have a controller with 
	 * unmapped controls. The client should call \link isValidController after 
	 * changing the keyboard mapping to ensure no controls are left unmapped.
	 */
	void
	changeKeyMapping(const key_t key, const Button button);

	template< typename T >
	void
	changeKeyMapping(const T key, const Button button) = delete;

	/**
	 * \brief
	 * Check whether the current keyboard mapping is valid.
	 * 
	 * The keyboard mapping is valid if and only if each control is mapped to a
	 * unique keyboard key. It is not possible to have multiple keys mapped to 
	 * one controller input and vice versa. This should be called after \link 
	 * changeKeyMapping.
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

	/// Path to controller's keyboard mapping file.
	boost::filesystem::path     _config_file;

	/// Bidrectional key-to-control mappings.
	keyboard_to_controller_t    _key_mappings;

	/// Keyboard keys the player is currently pressing.
	static std::vector< key_t > _pressed_keys;
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