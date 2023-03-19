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
#include <map>
#include <vector>
#include <optional>

//--------------------------------------------------------------------------------------------------
//------ MODULE CONTENT                                                                       ------
//--------------------------------------------------------------------------------------------------
export module b3m.common:participant;


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



export class IParticipant
{
public:
	using name_t = std::string;

	using data_header_t = std::string;
	using data_element_t = std::string;
	using data_entry_t = std::vector< data_element_t >;

	virtual ~IParticipant() = default;

	virtual name_t getName() const = 0;
	virtual std::optional< data_entry_t > getData(const data_header_t&) const = 0;
	virtual bool setData(const data_header_t&, const data_element_t&, bool append = false) = 0;
	virtual bool setData(const data_header_t&, const data_entry_t&, bool append = false) = 0;
};


export class Participant : public IParticipant
{
public:
	Participant(const name_t&);

	name_t getName() const override { return m_name; }
	std::optional< data_entry_t > getData(const data_header_t&) const override;
	bool setData(const data_header_t&, const data_element_t&, bool append = false) override;
	bool setData(const data_header_t&, const data_entry_t&, bool append = false) override;

private:
	name_t m_name;
	std::map< data_header_t, data_entry_t > m_data;
};



} //namespace common
} //namespace b3m


//END OF FILE --------------------------------------------------------------------------------------