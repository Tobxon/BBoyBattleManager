#pragma once


template <class IntegerType>
constexpr IntegerType divideUintRoundUp(const IntegerType& dividend, const IntegerType& divisor)
{
    return (divisor == 0) ? 0 : (dividend / divisor) + (dividend % divisor != 0);
}