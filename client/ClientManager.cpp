#include "ClientManager.h"
#include "parser.h"


ClientManager::ClientManager() :
	client(RakNetClient())
{
}


ClientManager::~ClientManager()
{
	client.Disconnect(true);
	client.Shutdown(true);
}

void ClientManager::RenderShapes()
{
	
}

void ClientManager::ListenForInput()
{
	std::string message;
	if (_kbhit()) {
		std::getline(std::cin, message);

		command cmd = parseCommandFromText(message);

		if (cmd.isInitialized()) {

			if (cmd.getCommandType() != command::Comm::NONE) {

			}
			else if (cmd.getShapeType() != command::Shapes::NONE_SHAPE) {
				switch (cmd.getShapeType())
				{
				case command::Shapes::CIRCLE:
					client.SendCircle(*(command::Circle*)cmd.getShapeData());
					break;
				case command::Shapes::LINE:
					client.SendLine(*(command::Line*)cmd.getShapeData());
					break;
				case command::Shapes::RECT:
					client.SendRect(*(command::Rect*)cmd.getShapeData());
					break;
				case command::Shapes::SPOINT:
					client.SendPoint(*(command::Point*)cmd.getShapeData());
					break;
				case command::Shapes::TRIANGLE:
					client.SendTriangle(*(command::Triangle*)cmd.getShapeData());
					break;
				default:
					break;
				}
			}
		}
		else {
			std::cout << "Invalid Command" << std::endl;
		}
	}
}

void ClientManager::ListenServer()
{
	client.ListenServer();
}

void ClientManager::RunClientLoop()
{
	
	while (true)
	{
		RenderShapes();
		ListenForInput();
		ListenServer();
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