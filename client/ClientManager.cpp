#include "ClientManager.h"



ClientManager::ClientManager() :
	client(RakNetClient())
{
}


ClientManager::~ClientManager()
{
	client.Disconnect(true);
	client.Shutdown(true);
}

void ClientManager::SendCommandToServer()
{

	client.Send(commandBucket);
}


void ClientManager::RunClientLoop()
{
	// TO-DO create threats to hande command and comunication

	std::string message;
	while (true)
	{
		if (_kbhit()) {
			std::getline(std::cin, message);
			std::cout << "Wii new command " << message << std::endl;

			//	 Command line Parser could go here :D

			SendCommandToServer();
		}

		// To-Do Call render 
	}
}

bool ClientManager::InitClient()
{
	bool flagStart = client.Start();
	if (flagStart) {
		return client.Connect(Shared::SERVER_PORT, Shared::LOCAL_SERVER_IP.c_str());
	}
	return flagStart;
}