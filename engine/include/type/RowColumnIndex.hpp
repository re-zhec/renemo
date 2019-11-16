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
 * Strong type alias to represent row number.
 */
struct row_t
	: type_safe::strong_typedef< row_t, int >
	, type_safe::strong_typedef_op::equality_comparison< row_t >
	, type_safe::strong_typedef_op::mixed_equality_comparison< row_t, int >
	, type_safe::strong_typedef_op::relational_comparison< row_t >
	, type_safe::strong_typedef_op::mixed_relational_comparison< row_t, int >
	, type_safe::strong_typedef_op::integer_arithmetic< row_t >
{
	using strong_typedef::strong_typedef;
};

/**
 * \brief
 * Strong type alias to represent column number.
 */
struct column_t
	: type_safe::strong_typedef< column_t, int >
	, type_safe::strong_typedef_op::equality_comparison< column_t >
	, type_safe::strong_typedef_op::mixed_equality_comparison< column_t, int >
	, type_safe::strong_typedef_op::relational_comparison< column_t >
	, type_safe::strong_typedef_op::mixed_relational_comparison< column_t, int >
	, type_safe::strong_typedef_op::integer_arithmetic< column_t >
{
	using strong_typedef::strong_typedef;
};

/**
 * \brief
 * Represents a row-column index.
 */
class RowColumnIndex
{
public:
	row_t    _r; /// Row number.
	column_t _c; /// Column number.

	/**
	 * \brief     Constructs a row-column index.
	 * 
	 * \param r   Row number.
	 * \param c   Column number.
	 */
	RowColumnIndex(row_t r, column_t c)
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