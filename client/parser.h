#pragma once
#include <regex>
#include <iostream>
#include <list>
#include <string>
#include <sstream>
//#include <>
#include "command.h"


#pragma region
std::string all_words = "(([a-z]+)|([A-F0-9]{8})|([1-9][0-9]*([.][0-9]*)?))";
std::string just_words = "[a-z ]+";

std::string colourr = "([0-9A-Fa-f]){8}";
std::string floatr = "([0-9]+([.][0-9]+)?)";
std::string intr = "([1-9][0-9]*)";
std::string spacer = "[ ]+";

std::string pointr = "(p(oint)?(" + spacer + floatr + "){2}" + "(" + spacer + colourr + ")?)";
std::string liner = "(l(ine)?(" + spacer + floatr + "){4}" + "(" + spacer + colourr + ")?)";
std::string rectr = "(r(ect)?(" + spacer + floatr + "){4}(" + spacer + colourr + "){0,2})";
std::string circler = "(c(ircle)?(" + spacer + floatr + "){3}("  + spacer + colourr + "){0,2})";
std::string triangler = "(t(riangle)?(" + spacer + floatr + "){6}(" + spacer + colourr + "){0,2})";
std::string undor = "(u(ndo)?)";
std::string deleter = "(d(elete)?" + spacer + intr + ")";
std::string listr = "(l(ist)?" + spacer + "(s(hapes)?|c(lients)?))";
std::string getr = "(g(et)?" + spacer + intr + ")";

std::string commandr = "(" + pointr
					 + "|" + liner
					 + "|" + rectr
					 + "|" + circler
					 + "|" + triangler
					 + "|" + undor
					 + "|" + deleter
					 + "|" + listr
					 + "|" + getr
	+")"
;
				
#pragma endregion defining some regex

//https://codereview.stackexchange.com/questions/11203/most-efficient-way-in-c-to-strip-strings
std::string strip(std::string in) {
	std::string final;
	for (int i = 0; i < in.length(); i++) {
		if (isalpha(in[i])) final += in[i];
	}
	return final;
}

void regex_loop_code_float(std::string& _input, float* points)
{
	std::regex reg_float(floatr);

	//http://en.cppreference.com/w/cpp/regex/regex_iterator
	auto float_iter = std::sregex_iterator(_input.begin(), _input.end(), reg_float);
	auto float_iter_end = std::sregex_iterator();
	for (std::sregex_iterator i = float_iter; i != float_iter_end; ++i)
	{
		std::smatch m = *i;
		*points = std::stof(m.str());
		points++;
	}

}

void regex_loop_code_colour(std::string& _input, command::Colour* colour)
{
	std::regex reg_colour(colourr);
}

command::Colour convert_str_to_colour(std::string _colour_string)
{
	std::istringstream ss(_colour_string);
	int i;
	ss >> std::hex >> i;
	
	/*unsigned char a = (unsigned char)((_colour_string.substr(0, 2)).c_str());
	unsigned char r = (unsigned char)((_colour_string.substr(2, 2)).c_str());
	unsigned char g = (unsigned char)((_colour_string.substr(4, 2)).c_str());
	unsigned char b = (unsigned char)((_colour_string.substr(6, 2)).c_str());*/

	unsigned char a = i & 0xFF000000;
	unsigned char r = i & 0x00FF0000;
	unsigned char g = i & 0x0000FF00;
	unsigned char b = i & 0x000000FF;

	command::Colour c(r, g, b, a);
	return c;
}

#pragma region
void parseLine(std::string & _input, command& _output)
{
	_output.setShapeType(command::Shapes::LINE);

	std::regex reg_colour(colourr);
	std::regex reg_float(floatr);

	float points[4];
	
	int k = 0;
	for (std::sregex_iterator i = std::sregex_iterator(_input.begin(), _input.end(), reg_float); i != std::sregex_iterator(); ++i)
	{
		std::smatch m = *i;
		points[k] = std::stof(m.str());
		k++;
	}

	std::smatch cm;
	std::regex_search(_input, cm, reg_colour);
	std::string colour = cm.str();

	command::Point p1(points[0], points[1]);
	command::Point p2(points[2], points[3]);
	command::Colour c;// = convert_str_to_colour(colour);
	command::Line l(p1, p2, c);
	_output.setShapeData(l);
}

void parsePoint(std::string& _input, command& _output)
{
	_output.setShapeType(command::Shapes::SPOINT);

	std::regex reg_colour(colourr);
	std::regex reg_float(floatr);

	float points[2];

	int k = 0;
	for (std::sregex_iterator i = std::sregex_iterator(_input.begin(), _input.end(), reg_float); i != std::sregex_iterator(); ++i)
	{
		std::smatch m = *i;
		points[k] = std::stof(m.str());
		k++;
	}

	std::smatch cm;
	std::regex_search(_input, cm, reg_colour);
	std::string colour = cm.str();
	command::Colour c;
	if (colour == "")
	{
		// set to white
		c = convert_str_to_colour("00000000");
	}
	else 
	{ 
		c = convert_str_to_colour(colour);
	}

	command::Point p1(points[0], points[1]);
	command::SPoint sp(p1, c);
	_output.setShapeData(sp);
}

void parseRect(std::string& _input, command& _output)
{
	_output.setShapeType(command::Shapes::RECT);

	std::regex reg_colour(colourr);
	std::regex reg_float(floatr);

	float points[4];
	command::Colour colours[2];

	int k = 0;
	for (std::sregex_iterator i = std::sregex_iterator(_input.begin(), _input.end(), reg_float); i != std::sregex_iterator(); ++i)
	{
		std::smatch m = *i;
		points[k] = std::stof(m.str());
		k++;
	}

	int j = 0; 
	for (std::sregex_iterator i = std::sregex_iterator(_input.begin(), _input.end(), reg_colour); i != std::sregex_iterator(); ++i)
	{
		std::smatch m = *i;
		colours[j] = convert_str_to_colour(m.str());
		j++;
	}
	

	command::Point p1(points[0], points[1]);
	command::Point p2(points[2], points[3]);

	command::Rect r(p1, p2, colours[0], colours[1]);
	_output.setShapeData(r);
}

void parseCircle(std::string& _input, command& _output)
{
	_output.setShapeType(command::Shapes::CIRCLE);

	std::regex reg_colour(colourr);
	std::regex reg_float(floatr);

	float points[3];
	command::Colour colours[2];

	int k = 0;
	for (std::sregex_iterator i = std::sregex_iterator(_input.begin(), _input.end(), reg_float); i != std::sregex_iterator(); ++i)
	{
		std::smatch m = *i;
		points[k] = std::stof(m.str());
		k++;
	}

	int j = 0;
	for (std::sregex_iterator i = std::sregex_iterator(_input.begin(), _input.end(), reg_colour); i != std::sregex_iterator(); ++i)
	{
		std::smatch m = *i;
		colours[j] = convert_str_to_colour(m.str());
		j++;
	}


	command::Point p1(points[0], points[1]);
	
	command::Circle c(p1, points[2], colours[0], colours[1]);
	_output.setShapeData(c);
}

void parseTriangle(std::string& _input, command& _output)
{
	_output.setShapeType(command::Shapes::TRIANGLE);

	std::regex reg_colour(colourr);
	std::regex reg_float(floatr);

	float points[4];
	command::Colour colours[6];

	int k = 0;
	for (std::sregex_iterator i = std::sregex_iterator(_input.begin(), _input.end(), reg_float); i != std::sregex_iterator(); ++i)
	{
		std::smatch m = *i;
		points[k] = std::stof(m.str());
		k++;
	}

	int j = 0;
	for (std::sregex_iterator i = std::sregex_iterator(_input.begin(), _input.end(), reg_colour); i != std::sregex_iterator(); ++i)
	{
		std::smatch m = *i;
		colours[j] = convert_str_to_colour(m.str());
		j++;
	}


	command::Point p1(points[0], points[1]);
	command::Point p2(points[2], points[3]);
	command::Point p3(points[4], points[5]);

	command::Triangle t(p1, p2, p3, colours[0], colours[1]);
	_output.setShapeData(t);
}

void parseGet(std::string& _input, command& _output)
{
	_output.setCommandType(command::Comm::GET);

	std::regex reg_int(intr);
	std::smatch cm;
	std::regex_search(_input, cm, reg_int);
	int id  = std::stoi(cm.str());

	_output.setid(id);
}

void parseDelete (std::string& _input, command& _output)
{
	_output.setCommandType(command::Comm::DELETE_SHAPE);

	std::regex reg_int(intr);
	std::smatch cm;
	std::regex_search(_input, cm, reg_int);
	int id = std::stoi(cm.str());

	_output.setid(id);
}

#pragma endregion parsing specific commands

bool isInputValid(std::string _commandInput)
{
	bool _output;
	std::regex command(commandr);
	_output = std::regex_match(_commandInput, command);
	return _output;
}

command parseCommandFromText(std::string _commandInput)
{
	command _output;
	if (isInputValid(_commandInput))
	{
		std::regex reg_jwords(just_words);

		std::smatch m; 
		std::regex_search(_commandInput, m, reg_jwords);
		
		std::string first_word = strip(m.str());

		int i = first_word.compare("rect");
		//int j = first_word.compare("test");

			if (first_word.compare("point") == 0 || first_word.compare("p") == 0)
		{
			parsePoint(_commandInput, _output);
		}
		else if (first_word.compare("line") == 0 || first_word.compare("l") == 0)
		{
			parseLine(_commandInput, _output);
		}
		else if (first_word.compare("rect") == 0 || first_word.compare("r") == 0)
		{
			parseRect(_commandInput, _output);
		}
		else if (first_word.compare("circle") == 0 || first_word.compare("c") == 0)
		{
			parseCircle(_commandInput, _output);
		}
		else if (first_word.compare("triangle") == 0 || first_word.compare("t") == 0)
		{
			parseTriangle(_commandInput, _output);
		}
		else if (first_word.compare("undo") == 0 || first_word.compare("u") == 0)
		{
			_output.setCommandType(command::Comm::UNDO);
		}
		else if (first_word.compare("delete") == 0 || first_word.compare("d") == 0)
		{
			parseDelete(_commandInput, _output);
		}
		else if (first_word.compare("list clients") == 0 || first_word.compare("l c") == 0)
		{
			_output.setCommandType(command::Comm::LIST_CLIENTS);
		}
		else if (first_word.compare("list shapes") == 0 || first_word.compare("l s") == 0)
		{
			_output.setCommandType(command::Comm::LIST_SHAPES);
		}
		else if (first_word.compare("get") == 0 || first_word.compare("g") == 0)
		{
			parseGet(_commandInput, _output);
		}
		else
		{
			//_output.setCommandType(command::INVALID);
		}
	}
	else
	{
		//_output.setCommandType(command::Comm::INVALID);
	}
	return _output;
}



