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
#include <vector>
#include <optional>
#include <ranges>
#include <concepts>
#include <any>


//--------------------------------------------------------------------------------------------------
//------ MODULE CONTENT                                                                       ------
//--------------------------------------------------------------------------------------------------
export module b3m.common:participant;


//--------------------------------------------------------------------------------------------------
//------ Dependencies                                                                         ------
//--------------------------------------------------------------------------------------------------
//import <string>;

//b3m
import :attributemap;


//--------------------------------------------------------------------------------------------------
//------ Declarations                                                                         ------
//--------------------------------------------------------------------------------------------------
namespace b3m
{
namespace common
{



// IParticipant - interface class for polymorphic use ----------------------------------------------
export class IParticipant
{
public:
	using name_t = std::string;
	static inline const name_t nameAttribute{ "name" }; //TODO to constexpr
	using attribute_name_t = std::string;
	using attribute_data_t = std::vector< std::string >;
	using attribute_element_t = attribute_data_t::value_type;

	virtual ~IParticipant() = default;

	virtual std::optional< name_t > getName() const = 0;
	virtual std::vector< attribute_name_t > getAttributes() const = 0; //TODO unit tests, implementation

	virtual std::optional< attribute_data_t > getAttributeData(const attribute_name_t&) = 0;


	template< typename input_data_t >
		requires std::convertible_to< input_data_t, attribute_element_t >
	bool setAttribute(const attribute_name_t& i_attribute, const input_data_t& i_data,
		bool i_append = false)
	{
		return setAttributeSingle(i_attribute, i_data, i_append);
		//return false;
	}

	template< typename input_data_t = std::initializer_list< attribute_element_t >>
		requires is_range_with_elements_of_type< input_data_t, attribute_element_t >
	bool setAttribute(const attribute_name_t& i_attribute, const input_data_t& i_data, 
		bool i_append = false)
	{
		if constexpr (std::convertible_to< std::ranges::range_value_t< input_data_t >, 
			attribute_data_t::value_type >)
		{
			return setAttributeMulti(i_attribute, i_data, i_append);
		}
		else if constexpr (std::constructible_from< std::ranges::range_value_t< input_data_t >, 
			attribute_data_t::value_type >)
		{
			return setAttributeMulti(i_attribute, 
				attribute_data_t{ std::begin(i_data), std::end(i_data) }, i_append);
		}

		return false;
	}

private:
	virtual bool setAttributeSingle(const attribute_name_t& i_attribute, 
		const attribute_data_t::value_type&, bool i_append = false) = 0;
	virtual bool setAttributeMulti(const attribute_name_t& i_attribute, const attribute_data_t&, 
		bool i_append = false) = 0;
};


// Participant - basic implementation for IParticipant interface -----------------------------------
export class Participant : public IParticipant
{
public:
	Participant(const name_t&);

	std::optional< name_t > getName() const override;
	std::vector< attribute_name_t > getAttributes() const override;

	std::optional< attribute_data_t > getAttributeData(const attribute_name_t&) override;

private:
	b3m::common::AttributeMap<attribute_name_t, attribute_data_t> m_attributes;

	bool setAttributeSingle(const attribute_name_t& i_attribute,
		const attribute_data_t::value_type&, bool i_append = false) override;
	bool setAttributeMulti(const attribute_name_t& i_attribute, const attribute_data_t&,
		bool i_append = false) override;
};



} //namespace common
} //namespace b3m


//END OF FILE --------------------------------------------------------------------------------------