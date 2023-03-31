//--------------------------------------------------------------------------------------------------
/**
 * \brief Module Interface Unit for the AttributeMap class used to store and polymorphly set
 *        attributes with a name and a container of data.
 *
 */


 //--------------------------------------------------------------------------------------------------
 //------ GLOBAL MODULE FRAGMENT                                                               ------
 //--------------------------------------------------------------------------------------------------
module;


//--------------------------------------------------------------------------------------------------
//------ Dependencies                                                                         ------
//--------------------------------------------------------------------------------------------------

#include <map>
#include <string>
#include <vector>
#include <optional>
#include <initializer_list>
#include <ranges>


//--------------------------------------------------------------------------------------------------
//------ MODULE CONTENT                                                                       ------
//--------------------------------------------------------------------------------------------------
export module b3m.common:attributemap;


//--------------------------------------------------------------------------------------------------
//------ Declarations                                                                         ------
//--------------------------------------------------------------------------------------------------
namespace b3m
{
namespace common
{



template< typename input_data_t, typename compare_data_t >
concept is_compatible = std::convertible_to< input_data_t, compare_data_t > || std::constructible_from< input_data_t, compare_data_t >;

template< typename input_data_t, typename range_element_t >
concept is_range_with_elements_of_type = std::ranges::input_range< input_data_t > && is_compatible< std::ranges::range_value_t< input_data_t >, range_element_t >;


export template< 
	typename attribute_name_t = std::string, 
	typename attribute_data_t = std::vector< std::string >>
class AttributeMap
{
public:
	using attribute_element_t = attribute_data_t::value_type;

	std::vector< attribute_name_t > getAttributes() const
	{
		auto keyView = std::views::keys(m_data);
		return std::vector< attribute_name_t >{ keyView.begin(), keyView.end() };
	}

	std::optional< attribute_data_t > getAttributeData(const attribute_name_t& i_attribute) const
	{
		if (m_data.contains(i_attribute))
		{
			//return m_data[i_attribute];
			return m_data.at(i_attribute);
		}

		return std::nullopt;
	}

	//set attribute with single value
	template< typename input_data_t >
		requires std::convertible_to< input_data_t, attribute_element_t >
	bool setAttribute(const attribute_name_t& i_attribute, const input_data_t& i_data, bool i_append = false)
	{
		if(i_append && m_data.contains(i_attribute))
		{
			auto& dataEntry = m_data.at(i_attribute);
			dataEntry.emplace_back(i_data);
		}
		else
		{
			m_data.insert_or_assign(i_attribute, attribute_data_t{ i_data });
		}

		return true;
	}

	//set attribute with multiple values
	template< typename input_data_t = std::initializer_list< attribute_element_t >>
		requires is_range_with_elements_of_type< input_data_t, attribute_element_t >
	bool setAttribute(const attribute_name_t& i_attribute, const input_data_t& i_data, bool i_append = false)
	{
		if (i_append && m_data.contains(i_attribute))
		{
			auto& dataEntry = m_data.at(i_attribute);
			dataEntry.insert(std::end(dataEntry), std::begin(i_data), std::end(i_data));
		}
		else
		{
			attribute_data_t data{ std::begin(i_data), std::end(i_data) };

			m_data.insert_or_assign(i_attribute, data);
		}

		return true;
	}

private:
	std::map< attribute_name_t, attribute_data_t > m_data;
};



} //namespace common
} //namespace b3m


//END OF FILE --------------------------------------------------------------------------------------