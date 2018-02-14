#pragma once
#include "../sharedContent.h"
#include "RakNetServer.h"
#include <RakSleep.h>
#include <iostream>
#include <string>

class command;


class ServerManager
{
public:
	static ServerManager& instance()
	{
		static ServerManager*instance = new ServerManager();
		return *instance;
	}

	bool InitServer();
	void RunServerLoop();
	~ServerManager();

private:
	RakNetServer server;

	void BroadcastDataToClients(command cmd, int messageType);
	void SendDataToClient();
	void ListenClients();

	ServerManager();
};
