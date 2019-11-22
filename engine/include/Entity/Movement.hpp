////////////////////////////////////////////////////////////////////////////////
/// \copyright MIT License                                                   ///
/// \author    Caylen Lee                                                    ///
/// \date      2019                                                          ///
////////////////////////////////////////////////////////////////////////////////
#pragma once

namespace nemo {
	class Entity; // Forward declaration.
}

namespace nemo::attr
{

/**
 * \brief
 * Handles an entity's movements.
 */
class Movement
{
public:
	virtual
	~Movement() = default;

	/**
	 * \brief           Pure virtual method to move a game entity left.
	 * 
	 * \param entity    Game entity to move.
	 * \param speed     Amoung of distance to move \a entity by.
	 */
	virtual void
	moveLeft(Entity& entity, const int speed)
	const noexcept = 0;

	/**
	 * \brief           Pure virtual method to move a game entity up.
	 * 
	 * \param entity    Game entity to move.
	 * \param speed     Amoung of distance to move \a entity by.
	 */
	virtual void
	moveUp(Entity& entity, const int speed)
	const noexcept = 0;

	/**
	 * \brief           Pure virtual method to move a game entity right.
	 * 
	 * \param entity    Game entity to move.
	 * \param speed     Amoung of distance to move \a entity by.
	 */
	virtual void
	moveRight(Entity& entity, const int speed)
	const noexcept = 0;

	/**
	 * \brief           Pure virtual method to move a game entity down.
	 * 
	 * \param entity    Game entity to move.
	 * \param speed     Amoung of distance to move \a entity by.
	 */
	virtual void
	moveDown(Entity& entity, const int speed)
	const noexcept = 0;
};

/**
 * \brief
 * Allows an entity to move.
 */
class Movable : public Movement
{
public:
	/**
	 * \brief           Moves a game entity left.
	 * 
	 * \param entity    Game entity to move.
	 * \param speed     Amoung of distance to move \a entity by.
	 */
	virtual void
	moveLeft(Entity& entity, const int speed)
	const noexcept override;

	/**
	 * \brief           Moves a game entity up.
	 * 
	 * \param entity    Game entity to move.
	 * \param speed     Amoung of distance to move \a entity by.
	 */
	virtual void
	moveUp(Entity& entity, const int speed)
	const noexcept override;

	/**
	 * \brief           Moves a game entity right.
	 * 
	 * \param entity    Game entity to move.
	 * \param speed     Amoung of distance to move \a entity by.
	 */
	virtual void
	moveRight(Entity& entity, const int speed)
	const noexcept override;

	/**
	 * \brief           Moves a game entity down.
	 * 
	 * \param entity    Game entity to move.
	 * \param speed     Amoung of distance to move \a entity by.
	 */
	virtual void
	moveDown(Entity& entity, const int speed)
	const noexcept override;
};

/**
 * \brief
 * Prevents an entity from moving no matter the velocity.
 */
class Immovable : public Movement
{
	/**
	 * \brief
	 * Doesn't do anything. Empty method.
	 */
	virtual void
	moveLeft(
		[[maybe_unused]] Entity&   entity,
		[[maybe_unused]] const int speed
	) const noexcept override;

	/**
	 * \brief
	 * Doesn't do anything. Empty method.
	 */
	virtual void
	moveUp(
		[[maybe_unused]] Entity&   entity,
		[[maybe_unused]] const int speed
	) const noexcept override;

	/**
	 * \brief
	 * Doesn't do anything. Empty method.
	 */
	virtual void
	moveRight(
		[[maybe_unused]] Entity&   entity,
		[[maybe_unused]] const int speed
	) const noexcept override;

	/**
	 * \brief
	 * Doesn't do anything. Empty method.
	 */
	virtual void
	moveDown(
		[[maybe_unused]] Entity&   entity,
		[[maybe_unused]] const int speed
	) const noexcept override;
};

}