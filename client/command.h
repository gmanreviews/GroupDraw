#pragma once
#include <vector>
#include <regex>
#include <iostream>
#include <list>
#include <string>


class command
{
public:
	enum Comm
	{
		//INVALID,
		UNDO,
		DELETE,
		LIST_SHAPES,
		LIST_CLIENTS,
		GET
	};
	enum Shapes
	{
		SPOINT,
		LINE,
		RECT,
		CIRCLE,
		TRIANGLE
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
	struct Shape { };
	struct SPoint : Shape
	{
		Point p;
		Colour c;
		SPoint(Point _p, Colour _c) :
			p(_p), c(_c) {}
	};
	struct Line : Shape
	{
		Point sp, ep;
		Colour c;
		Line(Point _sp, Point _ep, Colour _c) :
			sp(_sp), ep(_ep), c(_c) {}
	};
	struct Rect : Shape
	{
		Point p1, p2;
		Colour oc, fc;
		Rect(Point _p1, Point _p2, Colour _oc, Colour _fc) :
			p1(_p1), p2(_p2), oc(_oc), fc(_fc) {}
	};
	struct Circle : Shape
	{
		Point cx;
		float r;
		Colour oc, fc;
		Circle(Point _cx, float _r, Colour _oc, Colour _fc) :
			cx(_cx), r(_r), oc(_oc), fc(_fc) {}
	};
	struct Triangle : Shape
	{
		Point p1, p2, p3;
		Colour oc, fc;
		Triangle(Point _p1, Point _p2, Point _p3, Colour _oc, Colour _fc) :
			p1(_p1), p2(_p2), p3(_p3), oc(_oc), fc(_fc) {}
	};
	

	command();
	~command();

	void setprops(Shapes _shape, Shape _shapedata, Comm _command);
	void setShapeType(Shapes _shape);
	void setCommandType(Comm _command);
	void setShapeData(Shape _shapedata);
	void setid(int _id);

	//void parseLine(std::string & _input);

	void execute();

private :
	
	//Colour convert_str_to_colour(std::string _colour_string);


	int id;
	Comm _commandType;
	Shapes _shapeType;
	Shape _definedShape;

};

