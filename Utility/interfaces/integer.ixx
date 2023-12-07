//--------------------------------------------------------------------------------------------------
/**
 * \brief Module Interface Unit for utility functions for the use of integers.
 *
 */


//--------------------------------------------------------------------------------------------------
//------ GLOBAL MODULE FRAGMENT                                                               ------
//--------------------------------------------------------------------------------------------------
module;


//--------------------------------------------------------------------------------------------------
//------ MODULE CONTENT                                                                       ------
//--------------------------------------------------------------------------------------------------
export module utility:integer;


//--------------------------------------------------------------------------------------------------
//------ Dependencies                                                                         ------
//--------------------------------------------------------------------------------------------------

import <type_traits>;
import <stdexcept>;


//--------------------------------------------------------------------------------------------------
//------ Declarations                                                                         ------
//--------------------------------------------------------------------------------------------------
export namespace utility::type_traits
{



template <typename T>
concept IsUnsignedint = std::is_integral_v<T> && std::is_unsigned_v<T>;



}

export namespace utility::integer
{



template< utility::type_traits::IsUnsignedint posUintType >
constexpr posUintType ceil_pos_uint_division(posUintType i_dividend, posUintType i_divisor) noexcept(false);



} //namespace utility


//--------------------------------------------------------------------------------------------------
//------ Implementations                                                                      ------
//--------------------------------------------------------------------------------------------------

template< utility::type_traits::IsUnsignedint posUintType >
constexpr posUintType utility::integer::ceil_pos_uint_division(posUintType i_dividend, posUintType i_divisor)
{
	if (i_divisor == 0)
	{
		throw std::invalid_argument("Division by zero is undefined");
	}
	return i_dividend/i_divisor + (i_dividend % i_divisor != 0);
}


//END OF FILE --------------------------------------------------------------------------------------