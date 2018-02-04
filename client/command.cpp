#include "command.h"



command::command()
{
}


command::~command()
{
}

void command::execute()
{
	switch (_commandType) 
	{
	case (commandType::DRAW):
		//call draw command
		break;
	case (commandType::FETCH):
		//call fetch command
		break;
	case (commandType::LIST):
		//call list command
		break;
	case (commandType::UNDO):
		//call undo command
		break;
	//case (commandType::invalid):
	default:
		break;
	}
}
