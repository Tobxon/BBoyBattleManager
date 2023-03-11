//--------------------------------------------------------------------------------------------------
/**
 * \brief Module Interface Unit for the Participant class.
 *
 */


//--------------------------------------------------------------------------------------------------
//------ GLOBAL MODULE FRAGMENT                                                               ------
//--------------------------------------------------------------------------------------------------
module;

#include <string> //TODO to modules like import

//--------------------------------------------------------------------------------------------------
//------ MODULE CONTENT                                                                       ------
//--------------------------------------------------------------------------------------------------
export module b3m_common:participant;


//--------------------------------------------------------------------------------------------------
//------ Dependencies                                                                         ------
//--------------------------------------------------------------------------------------------------
//import <string>;


//--------------------------------------------------------------------------------------------------
//------ Declarations                                                                         ------
//--------------------------------------------------------------------------------------------------
namespace b3m
{
namespace common
{



export class Participant
{
public:
	using name_t = std::string;

	virtual ~Participant() = default;
	Participant(const name_t&);

	name_t getName() const { return m_name; }
private:
	name_t m_name;
};



} //namespace common
} //namespace b3m


//END OF FILE --------------------------------------------------------------------------------------