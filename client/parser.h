#pragma once
#include <regex>
#include <iostream>
#include <list>
#include <string>
#include "command.h"

command parseCommandFromText(std::string _commandInput)
{
	command _output;
	return _output;
}

std::list<std::string> splitUpStringToList(std::string _commandInput)
{
	std::list<std::string> _output;

	//std::regex command()

	return _output;
}

bool isInputValid(std::string _commandInput)
{
	bool _output;
	std::regex command("");
	_output = std::regex_match(_commandInput, command);
	return _output;
}
