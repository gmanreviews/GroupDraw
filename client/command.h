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

	command();
	~command();

private :
	enum objectType
	{
		invalid = -1,
		POINT,
		LINE,
		RECTANGLE,
		CIRCLE,
		TRIANGLE
	};
	
	objectType shapeType;
	float size;
	position position;
	colour colour;
	bool autofill;

};

