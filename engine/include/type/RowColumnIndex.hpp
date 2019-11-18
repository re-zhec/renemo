////////////////////////////////////////////////////////////////////////////////
/// \copyright MIT License                                                   ///
/// \author    Caylen Lee                                                    ///
/// \date      2019                                                          ///
////////////////////////////////////////////////////////////////////////////////
#pragma once

#include <type_safe/strong_typedef.hpp>
#include <SFML/System/Vector2.hpp>

#include <utility>
#include <array>

namespace nemo::type
{

/**
 * \brief
 * Strong type alias to represent row number.
 */
struct row_t
	: type_safe::strong_typedef< row_t, unsigned >
	, type_safe::strong_typedef_op::equality_comparison< row_t >
	, type_safe::strong_typedef_op::mixed_equality_comparison< row_t, unsigned >
	, type_safe::strong_typedef_op::relational_comparison< row_t >
	, type_safe::strong_typedef_op::mixed_relational_comparison< row_t, unsigned >
	, type_safe::strong_typedef_op::integer_arithmetic< row_t >
{
	using strong_typedef::strong_typedef;
};

/**
 * \brief
 * Strong type alias to represent column number.
 */
struct column_t
	: type_safe::strong_typedef< column_t, unsigned >
	, type_safe::strong_typedef_op::equality_comparison< column_t >
	, type_safe::strong_typedef_op::mixed_equality_comparison< column_t, unsigned >
	, type_safe::strong_typedef_op::relational_comparison< column_t >
	, type_safe::strong_typedef_op::mixed_relational_comparison< column_t, unsigned >
	, type_safe::strong_typedef_op::integer_arithmetic< column_t >
{
	using strong_typedef::strong_typedef;
};

using row_column_pair_t = std::pair< row_t, column_t >;

/**
 * \brief
 * Represents a row-column index.
 */
class RowColumnIndex
{
public:
	unsigned _r; /// Row number.
	unsigned _c; /// Column number.

	/**
	 * \brief
	 * Constructs a index whose row and column numbers are 0.
	 */
	constexpr
	RowColumnIndex()
	noexcept;

	/**
	 * \brief     Constructs a row-column index.
	 * 
	 * \param r   Row number.
	 * \param c   Column number.
	 */
	RowColumnIndex(const row_t r, const column_t c)
	noexcept;

	/**
	 * \brief       Constructs a row-column index.
	 * \param rc    (1) Row and (2) column numbers.
	 */
	RowColumnIndex(const row_column_pair_t rc)
	noexcept;

	/**
	 * \brief
	 * \param rc    (1) Row and (2) column numbers.
	 */
	RowColumnIndex(const std::array< unsigned, 2 > rc)
	noexcept;

	/**
	 * \brief        Overloads (==) operator.
	 * 
	 * This operator checks whether two row-column indices are the same.
	 * 
	 * \param rhs    Row-column index to compare this one to.
	 * \return       True if same, false if different.
	 */
	bool 
	operator == (const RowColumnIndex rhs) 
	const noexcept;

	/**
	 * \brief        Overloads (!=) operator.
	 * 
	 * This operator checks whether two row-column indices are different.
	 * 
	 * \param rhs    Row-column index to compare this one to.
	 * \return       True if different, false if same.
	 */
	bool 
	operator != (const RowColumnIndex rhs) 
	const noexcept;

	/**
	 * \brief  Gets a converted \link sf::Vector2i object.
	 * \return Converted object.
	 */
	sf::Vector2i
	sfVector2i()
	const noexcept;
};

} // namespace nemo::type