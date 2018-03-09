#include "ServerManager.h"
#include "../InMemoryDB.h"

ServerManager::ServerManager() :
	server(RakNetServer())
{
}


ServerManager::~ServerManager()
{
	server.Shutdown(10);
}

void ServerManager::BroadcastDataToClients(InMemoryDB::Register* reg)
{
	switch (reg->cmd->getShapeType())
	{
	case command::Shapes::CIRCLE:
		server.BroadcastCircle(*(command::Circle*)reg->cmd->getShapeData());
		break;
	case command::Shapes::LINE:
		server.BroadcastLine(*(command::Line*)reg->cmd->getShapeData());
		break;
	case command::Shapes::RECT:
		server.BroadcastRect(*(command::Rect*)reg->cmd->getShapeData(), reg->guid);
		break;
	case command::Shapes::SPOINT:
		server.BroadcastPoint(*(command::Point*)reg->cmd->getShapeData());
		break;
	case command::Shapes::TRIANGLE:
		server.BroadcastTriangle(*(command::Triangle*)reg->cmd->getShapeData());
		break;

	default:
		break;
	}
}

void ServerManager::ListenClients()
{
	command *cmd;
	RakNet::RakNetGUID guid;
	InMemoryDB::Register* reg;

	bool clientEvent = server.ListenClients(cmd, guid);

	if (clientEvent) {
		if (cmd != NULL) {
			if (cmd->getShapeType() != command::Shapes::NONE_SHAPE) {
				reg = InMemoryDB::instance().SaveCommandServer(cmd, guid);
				ServerManager::BroadcastDataToClients(reg);
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