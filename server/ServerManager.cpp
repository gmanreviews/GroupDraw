#include "ServerManager.h"


ServerManager::ServerManager() :
	server(RakNetServer())
{
}


ServerManager::~ServerManager()
{
	server.Shutdown(10);
}

void ServerManager::BroadcastDataToClients(command cmd, int messageType)
{
	switch (messageType)
	{
	case command::Shapes::CIRCLE:
		server.BroadcastCircle(*(command::Circle*)cmd.getShapeData());
		break;
	case command::Shapes::LINE:
		server.BroadcastLine(*(command::Line*)cmd.getShapeData());
		break;
	case command::Shapes::RECT:
		server.BroadcastRect(*(command::Rect*)cmd.getShapeData());
		break;
	case command::Shapes::SPOINT:
		server.BroadcastPoint(*(command::Point*)cmd.getShapeData());
		break;
	case command::Shapes::TRIANGLE:
		server.BroadcastTriangle(*(command::Triangle*)cmd.getShapeData());
		break;

	default:
		break;
	}
}

void ServerManager::ListenClients()
{
	command *cmd;

	bool clientEvent = server.ListenClients(cmd);

	if (clientEvent) {
		if (cmd != NULL) {
			if (cmd->getShapeType() != command::Shapes::NONE_SHAPE) {
				// Store command on in memmory DB
				ServerManager::BroadcastDataToClients(*cmd, cmd->getShapeType());
			}
		}
	}
}

void ServerManager::RunServerLoop()
{

	while (true)
	{
		ListenClients();
	}
}

bool ServerManager::InitServer()
{
	return server.Start(Shared::SERVER_PORT, Shared::MAX_SERVER_CONNECTIONS);
}