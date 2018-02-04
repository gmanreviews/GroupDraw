#pragma once
#include <vector>

class command
{
public:
	struct position
	{
		float x, y;
	};
	struct colour
	{
		float r, g, b, a;
	};
	enum objectType
	{
		// invalid = -1, //gives a build error for some reason
		POINT,

		LINE,
		RECTANGLE,
		CIRCLE,
		TRIANGLE
	};
	enum commandType
	{
		// invalid = -1, //gives a build error for some reason
		DRAW,
		LIST,
		UNDO,
		FETCH
	};

	command();
	~command();

	void execute();

private :
	
	
	commandType _commandType;
	objectType _shapeType;
	float size;
	position position;
	colour colour;
	bool autofill;

};

