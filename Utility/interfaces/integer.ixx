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

//std
import <stdexcept>;

//b3m
import :type_traits;


//--------------------------------------------------------------------------------------------------
//------ Declarations                                                                         ------
//--------------------------------------------------------------------------------------------------
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