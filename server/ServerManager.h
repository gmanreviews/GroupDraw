#pragma once
#include "../sharedContent.h"
#include "../InMemoryDB.h"
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

	void BroadcastDataToClients(InMemoryDB::Register* reg);
	void SendDataToClient();
	void ListenClients();

	ServerManager();
};
