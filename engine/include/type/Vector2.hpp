////////////////////////////////////////////////////////////////////////////////
/// \copyright MIT License                                                   ///
/// \author    Caylen Lee                                                    ///
/// \date      2019                                                          ///
////////////////////////////////////////////////////////////////////////////////
#pragma once

#include <type_safe/strong_typedef.hpp>
#include <SFML/System/Vector2.hpp>

namespace nemo::type
{

/**
 * \brief
 * Strong type alias to represent a x-coordinate, width measurement, etc.
 */
struct x_t
	: type_safe::strong_typedef< x_t, int >
	, type_safe::strong_typedef_op::equality_comparison< x_t >
	, type_safe::strong_typedef_op::mixed_equality_comparison< x_t, int >
	, type_safe::strong_typedef_op::relational_comparison< x_t >
	, type_safe::strong_typedef_op::mixed_relational_comparison< x_t, int >
	, type_safe::strong_typedef_op::integer_arithmetic< x_t >
{
	using strong_typedef::strong_typedef;
};

/**
 * \brief
 * Strong type alias to represent a y-coordinate, height measurement, etc.
 */
struct y_t
	: type_safe::strong_typedef< y_t, int >
	, type_safe::strong_typedef_op::equality_comparison< y_t >
	, type_safe::strong_typedef_op::mixed_equality_comparison< y_t, int >
	, type_safe::strong_typedef_op::relational_comparison< y_t >
	, type_safe::strong_typedef_op::mixed_relational_comparison< y_t, int >
	, type_safe::strong_typedef_op::integer_arithmetic< y_t >
{
	using strong_typedef::strong_typedef;
};

using xy_pair_t = std::pair< x_t, y_t >;

/**
 * \brief
 * Represents a xy coordinate or dimensions on a 2D plane.
 */
class Vector2
{
public:
	x_t _x; /// X-coordinate / width.
	y_t _y; /// Y-coordinate / height.

	/**
	 * \brief
	 * Constructs a 2D value of (0, 0).
	 */
	constexpr
	Vector2()
	noexcept;

	/**
	 * \brief     Constructs a 2D value.
	 * 
	 * \param x   X component.
	 * \param y   Y component.
	 */
	Vector2(const x_t x, const y_t y)
	noexcept;
	
	/**
	 * \brief       Constructs a 2D value.
	 * \param xy    (1) X and (2) Y components.
	 */
	Vector2(const xy_pair_t xy)
	noexcept;
	
	/**
	 * \brief        Overloads (+) operator.
	 * 
	 * This operator adds two 2D values together memberwise.

	 * \param rhs    Second operand.
	 * \return       The sum of the two operands.
	 */
	Vector2 
	operator + (const Vector2 rhs)
	const noexcept;

	/**
	 * \brief        Overloads (+=) operator.
	 * 
	 * This operator updates the current 2D value with a compounded, memberwise
	 * sum of itself and another 2D value.
	 * 
	 * \param rhs    2D operand to add to current value.
	 * \return       Current 2D value, updated to the sum.
	 */
	Vector2& 
	operator += (const Vector2 rhs) 
	noexcept;

	/**
	 * \brief        Overloads (-) operator.
	 * 
	 * This operator gets the memberwise difference between two 2D values
	 * 
	 * \param rhs    Second operand.
	 * \return       The difference between the two operands.
	 */
	Vector2 
	operator - (const Vector2 rhs)
	const noexcept;

	/**
	 * \brief        Overloads (-=) operator.
	 * 
	 * This operator subtracts another 2D value from the current one memberwise
	 * and updates the latter with the difference.
	 * 
	 * \param rhs    2D operand to subtract from current value.
	 * \return       Current 2D value, updated to the difference.
	 */
	Vector2&
	operator -= (const Vector2 rhs)
	noexcept;

	/**
	 * \brief  Gets a converted \link sf::Vector2i object.
	 * \return Converted object.
	 */
	sf::Vector2i
	sfVector2i()
	const noexcept;
};

} // namespace nemo::type