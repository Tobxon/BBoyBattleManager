#include "pch.h"
#include "Score.hpp"

//bool operator<(const Score& i_a, const Score& i_b)
	//{
	//	if (i_a.m_wins + i_a.m_freeTickets == i_b.m_wins + i_b.m_freeTickets)
	//	{
	//		return i_a.m_points < i_b.m_points;
	//	}

	//	return i_a.m_wins + i_a.m_freeTickets < i_b.m_wins + i_b.m_freeTickets;
	//}

	//only valid for the draft //TODO - better definition
bool b3m::sst::operator==(const Score& i_a, const Score& i_b)
{
	return i_a.m_wins + i_a.m_freeTickets == i_b.m_wins + i_b.m_freeTickets;
}
//
//bool b3m::sst::operator>(const Score& i_a, const Score& i_b)
//{
//	return i_a.m_wins + i_a.m_freeTickets > i_b.m_wins + i_b.m_freeTickets;
//}