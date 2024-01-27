//--------------------------------------------------------------------------------------------------
/**
 * \brief Application Entry for the console version of BBoyBattleManager - initially used for tests
 *
 */


//--------------------------------------------------------------------------------------------------
//------ Dependencies                                                                         ------
//--------------------------------------------------------------------------------------------------

import b3m.common;

import <iostream>;
import <string>;
import <vector>;


//--------------------------------------------------------------------------------------------------
//------ Declarations                                                                         ------
//--------------------------------------------------------------------------------------------------

void printLineSeperator(std::ostream&);


//--------------------------------------------------------------------------------------------------
//------ Main                                                                                 ------
//--------------------------------------------------------------------------------------------------

int main(int argc, char** argv)
{
	std::cout << "----- " << "Welcome to B-Boy Battle Manager " << "-----" << std::endl;

	//entering participants
	std::vector< b3m::common::Participant > participants;
	std::cout << "Enter Names for B-Boys and B-Girls applying in the Battle" << std::endl;
	while (true)
	{
		std::string userInput;
		std::getline(std::cin, userInput);
		if (userInput.empty())
		{
			break;
		}

		//TODO clear entry for actual name

		participants.emplace_back(userInput);
	}

	printLineSeperator(std::cout);

	//print Names of participants
	std::cout << "Listing all currently registered B-Girls and B-Boys:" << std::endl;
	for (const auto& participant : participants)
	{
		std::cout << participant << ", ";
	}
	std::cout << std::endl;

	printLineSeperator(std::cout);


}


//--------------------------------------------------------------------------------------------------
//------ Implementations                                                                      ------
//--------------------------------------------------------------------------------------------------

void printLineSeperator(std::ostream& i_printSink)
{
	i_printSink << std::endl << "-----" << std::endl << std::endl;
}


//END OF FILE --------------------------------------------------------------------------------------