#include "command.h"



command::command()
{
}

command::command(SPoint point)
{
	_shapeType = Shapes::SPOINT;
	_definedShape = new SPoint(Point(point.p.x, point.p.y), Colour(point.c.r, point.c.g, point.c.b, point.c.a));
	_commandType = Comm::NONE;
	_initialized = true;
}

command::command(Line line)
{
	_shapeType = Shapes::LINE;
	_definedShape = new Line(
		Point(line.sp.x, line.sp.y),
		Point(line.ep.x, line.ep.y),
		Colour(line.c.r, line.c.g, line.c.b, line.c.a)
	);
	_commandType = Comm::NONE;
	_initialized = true;
}

command::command(Rect rect)
{
	_shapeType = Shapes::RECT;
	_definedShape = new Rect(
		Point(rect.p1.x, rect.p1.y),
		Point(rect.p2.x, rect.p2.y),
		Colour(rect.oc.r, rect.oc.g, rect.oc.b, rect.oc.a),
		Colour(rect.fc.r, rect.fc.g, rect.fc.b, rect.fc.a)
	);
	_commandType = Comm::NONE;
	_initialized = true;
}

command::command(Circle circle)
{
	_shapeType = Shapes::CIRCLE;
	_definedShape = new Circle(
		Point(circle.cx.x, circle.cx.y),
		circle.r,
		Colour(circle.oc.r, circle.oc.g, circle.oc.b, circle.oc.a),
		Colour(circle.fc.r, circle.fc.g, circle.fc.b, circle.fc.a)
	);
	_commandType = Comm::NONE;
	_initialized = true;
}

command::command(Triangle triangle)
{
	_shapeType = Shapes::TRIANGLE;
	_definedShape = new Triangle(
		Point(triangle.p1.x, triangle.p1.y),
		Point(triangle.p2.x, triangle.p2.y),
		Point(triangle.p3.x, triangle.p3.y),
		Colour(triangle.oc.r, triangle.oc.g, triangle.oc.b, triangle.oc.a),
		Colour(triangle.fc.r, triangle.fc.g, triangle.fc.b, triangle.fc.a)
	);
	_commandType = Comm::NONE;
	_initialized = true;
}

command::~command()
{
	// REFACTOR NEEDED: Copy constructor or smart pointer is needed to implment proper memmory managment
	/*delete _definedShape;
	_definedShape = NULL;*/
}

void command::draw(sf::RenderWindow* window)
{

	command::Rect* rect;
	command::SPoint* point;
	command::Triangle* triangle;
	command::Line* line;
	command::Circle* circle;

	switch (_shapeType)
	{
	case command::Shapes::RECT:
		{
			sf::RectangleShape sfmlrect;
			//rect = _definedShape;
			//HOW DO I FORCE IT TO KNOW IT"S A RECT AND NOT A SHAPE
			
			//rect =  (command::RECT*) _definedShape;
		}
		break;
	default:
		break;
	}
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

void command::setShapeData(Shape* _shapedata)
{
	_definedShape = _shapedata;
	_initialized = true;
}

void command::setId(int _id)
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