#pragma once

#include <MessageIdentifiers.h>
#include <string>

int const SERVER_PORT = 60000;
const char* SERVER_IP = "142.55.42.69";
const char* LOCAL_SERVER_IP = "127.0.0.1";

enum UserMessageIDs
{
	MSG_CHAT_PACKET = ID_USER_PACKET_ENUM
};
