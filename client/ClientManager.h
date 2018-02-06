#pragma once
#include "../sharedContent.h"
#include "RakNetClient.h"
#include <RakSleep.h>
#include <Kbhit.h>
#include <iostream>
#include <string>
#include <thread>   



class ClientManager
{
public:
	static ClientManager& instance()
	{
		static ClientManager *instance = new ClientManager();
		return *instance;
	}

	bool InitClient();
	void RunClientLoop();
	~ClientManager();


private:
	RakNetClient client;
	Shared::ClientToServer commandBucket;
	std::thread commandLineThread;
	std::thread communicationThread;

	void SendCommandToServer();

	ClientManager();
};
