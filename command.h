#pragma once
#include <MessageIdentifiers.h>
#include <vector>
#include <regex>
#include <iostream>
#include <list>
#include <string>
#include <MessageIdentifiers.h>
//#include <memory>


//namespace RakNet {
//	unsigned char MessageID;
//}

class command
{
public:
	enum Comm
	{
		//INVALID,
		NONE = ID_USER_PACKET_ENUM + 1,
		UNDO = ID_USER_PACKET_ENUM + 2,
		DELETE_SHAPE = ID_USER_PACKET_ENUM + 3,
		LIST_SHAPES = ID_USER_PACKET_ENUM + 4,
		LIST_CLIENTS = ID_USER_PACKET_ENUM + 5,
		GET = ID_USER_PACKET_ENUM + 6
	};
	enum Shapes
	{
		NONE_SHAPE = ID_USER_PACKET_ENUM + 7,
		SPOINT = ID_USER_PACKET_ENUM + 8,
		LINE = ID_USER_PACKET_ENUM + 9,
		RECT = ID_USER_PACKET_ENUM + 10,
		CIRCLE = ID_USER_PACKET_ENUM + 11,
		TRIANGLE = ID_USER_PACKET_ENUM + 12
	};
	struct Colour
	{
		unsigned char r, g, b, a;
		Colour() {}
		Colour(unsigned char _r, unsigned char _g, unsigned char _b, unsigned char _a) :
			r(_r), g(_g), b(_b), a(_a) {}
	};
	struct Point
	{
		float x, y;
		//http://www.cplusplus.com/forum/general/24738/
		Point(float _x, float _y) :
			x(_x), y(_y) {}
	};

#pragma pack(push, 1)
	struct Shape 
	{
		Shapes typeId;
		Shape(Shapes type) : typeId(type) {}
	};

	struct SPoint : Shape
	{

		Point p;
		Colour c;
		SPoint(Point _p, Colour _c) :
			Shape(command::Shapes::SPOINT), p(_p), c(_c) {}
	};
	struct Line : Shape
	{
		Point sp, ep;
		Colour c;
		Line(Point _sp, Point _ep, Colour _c) :
			Shape(command::Shapes::LINE), sp(_sp), ep(_ep), c(_c) {}
	};
	struct Rect : Shape
	{
		Point p1, p2;
		Colour oc, fc;
		Rect(Point _p1, Point _p2, Colour _oc, Colour _fc) :
			Shape(command::Shapes::RECT), p1(_p1), p2(_p2), oc(_oc), fc(_fc) {}
	};
	struct Circle : Shape
	{
		Point cx;
		float r;
		Colour oc, fc;
		Circle(Point _cx, float _r, Colour _oc, Colour _fc) :
			Shape(command::Shapes::CIRCLE), cx(_cx), r(_r), oc(_oc), fc(_fc) {}
	};
	struct Triangle : Shape
	{
		Point p1, p2, p3;
		Colour oc, fc;
		Triangle(Point _p1, Point _p2, Point _p3, Colour _oc, Colour _fc) :
			Shape(command::Shapes::TRIANGLE), p1(_p1), p2(_p2), p3(_p3), oc(_oc), fc(_fc) {}
	};
#pragma pack(pop)

	command();
	~command();

	void setprops(Shapes _shape, Shape _shapedata, Comm _command);
	void setShapeType(Shapes _shape);
	Shapes getShapeType();
	void setCommandType(Comm _command);
	Comm getCommandType();
	void setShapeData(Shape* _shapedata);
	Shape *getShapeData();
	void setid(int _id);
	bool isInitialized() { return _initialized; }

	//void parseLine(std::string & _input);

	void execute();

private :
	
	//Colour convert_str_to_colour(std::string _colour_string);

	bool _initialized = false;
	int id;
	Comm _commandType = command::Comm::NONE;
	Shapes _shapeType = command::Shapes::NONE_SHAPE;
	Shape *_definedShape;

};

