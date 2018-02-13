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
	case (Comm::DELETE_SHAPE):
		//call delete command
		break;
	case (Comm::UNDO):
		//call undo command
		break;
	case (Comm::LIST_SHAPES):
		//call list shapes command
		break;
	case (Comm::LIST_CLIENTS):
		//call list clients command
		break;
	//case (commandType::invalid):
	default:
		//its probably a draw command; 
		//there's a shape isn't there
		break;
	}
}

void command::setprops(Shapes _shape, Shape _shapedata, Comm _command)
{
	_shapeType = _shape;
	_definedShape = &_shapedata;
	_commandType = _command;
	_initialized = true;
}

void command::setShapeType(Shapes _shape)
{
	_shapeType = _shape;
	_initialized = true;
}

void command::setCommandType(Comm _command)
{
	_commandType = _command;
	_initialized = true;
}

void command::setShapeData(Shape _shapedata)
{
	_definedShape = &_shapedata;
	_initialized = true;
}

void command::setid(int _id)
{
	id = _id;
	_initialized = true;
}

command::Shapes command::getShapeType()
{
	return _shapeType;
}

command::Comm command::getCommandType()
{
	return _commandType;
}

command::Shape* command::getShapeData()
{
	return _definedShape;
}