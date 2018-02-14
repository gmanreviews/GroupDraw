#pragma once

#include <MessageIdentifiers.h>
#include <string>
//#include "RakPeerInterface.h"
//#include "MessageIdentifiers.h"
//#include "BitStream.h"
//#include "RakNetTypes.h"  // MessageID

// int const SERVER_PORT = 60000;
// const char* SERVER_IP = "142.55.42.69";
// const char* LOCAL_SERVER_IP = "127.0.0.1";

namespace Shared {
	int const SERVER_PORT = 1288;
	int const MAX_SERVER_CONNECTIONS = 10;
	std::string const SERVER_IP = "169.254.80.80"; //fernando
	//std::string const SERVER_IP = "142.55.42.69";
	std::string const LOCAL_SERVER_IP = "127.0.0.1";

#pragma pack(push, 1)
	struct NetworkCommand
	{

	};
	struct DrawCommand : NetworkCommand
	{
		unsigned char drawId; // Id generated by the server, used when modifiying or deliting a particular draw
		unsigned char obj; // c for circle, r for rectangle ...
		std::string position; // string with the format X,Y
		unsigned int size; // scale value
		std::string colour; // Color in HEX value like #aaa090
		bool fill; // Fill the shape with color 
		unsigned char scope; // 'c' for �client�, and 'a' for �all�
	};

	struct ActionCommand : NetworkCommand
	{
		unsigned char typeId; // Your type here
	};
#pragma pack(pop)

}

enum UserMessageIDs
{
	MSG_CHAT_PACKET = ID_USER_PACKET_ENUM,
	//CLIENT_SERVER_DRAW_COMMAND = ID_USER_PACKET_ENUM + 1,
	//CLIENT_SERVER_ACTION_COMMAND = ID_USER_PACKET_ENUM + 2
};

