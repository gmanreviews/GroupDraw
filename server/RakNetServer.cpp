#include "RakNetServer.h"
#include "../GroupDraw/GroupDrawMessageIdentifiers.h"

#include <RakPeerInterface.h>
#include <MessageIdentifiers.h>
#include <BitStream.h>

#include <iostream>

RakNetServer::RakNetServer() : m_peer(RakNet::RakPeerInterface::GetInstance())
{
}

RakNetServer::~RakNetServer()
{
    if(m_peer != NULL) {
        RakNet::RakPeerInterface::DestroyInstance(m_peer);
    }
}

//Returns true if the server is started.
bool RakNetServer::Start(unsigned short port, unsigned int maxConnections) {
    if(m_peer != NULL) {
        RakNet::SocketDescriptor sd(port, NULL);
        RakNet::StartupResult result = m_peer->Startup(maxConnections, &sd, 1);
        switch(result) {
            case RakNet::RAKNET_STARTED:
                std::cout << "Server Started" << std::endl;
                //Don't forget to set maximum inbound connections.
                m_peer->SetMaximumIncomingConnections(maxConnections);
                return true;
            case RakNet::RAKNET_ALREADY_STARTED:
                std::cout << "Server was already started" << std::endl;
                return true;
            case RakNet::SOCKET_PORT_ALREADY_IN_USE:
                std::cerr << "Server could not bind to port " << port << " because it is already in use." << std::endl;
                return false;
            default:
                std::cerr << "Unknown potentially bad StartupResult " << result << " on Startup." << std::endl;
                return false;
        }
    }
    std::cerr << "Server has a null m_peer" << std::endl;
    return false;
}

void RakNetServer::Shutdown(unsigned int blockDuration) {
    if(m_peer != NULL) {
        std::cout << "Server shutting down with blockduration of " << blockDuration << std::endl;
        m_peer->Shutdown(blockDuration, 0, HIGH_PRIORITY);
    }
}

bool RakNetServer::IsActive() {
    return m_peer != NULL ? m_peer->IsActive() : false;
}

bool RakNetServer::ListenClients(command* &cmd, RakNet::RakNetGUID &clientId) {
	
	command::Rect* rect;
	command::SPoint* point;
	command::Triangle* triangle;
	command::Line* line;
	command::Circle* circle;

	packet = m_peer->Receive();
    if(packet != NULL) {
        unsigned char pid = packet->data[0];
		clientId = packet->guid;
        switch(pid) {
            case ID_NEW_INCOMING_CONNECTION:
                std::cout << "Incoming connection from " << packet->systemAddress.ToString() << std::endl;
				cmd = NULL;
                break;

            case ID_DISCONNECTION_NOTIFICATION:
                std::cout << "Disconnection notification from " << packet->systemAddress.ToString() << std::endl;
				cmd = NULL;
                break;

            case ID_CONNECTION_LOST:
                std::cout << "Lost connection with " << packet->systemAddress.ToString() << std::endl;
				cmd = NULL;
                break;

            case ID_GRP_JOIN_REQUEST: //This is a reminder that user defined packets should be returned.
				cmd = NULL;
				break;
                //return packet;

			case command::Comm::DELETE_SHAPE:
				std::cout << "DELETE_SHAPE command" << std::endl;
				cmd = new command();
				break;

			case command::Comm::GET:
				std::cout << "GET command" << std::endl;
				cmd = new command();
				break;

			case command::Comm::LIST_CLIENTS:
				std::cout << "LIST_CLIENTS command" << std::endl;
				cmd = new command();
				break;

			case command::Comm::LIST_SHAPES:
				std::cout << "LIST_SHAPES command" << std::endl;
				cmd = new command();
				break;

			case command::Comm::UNDO:
				std::cout << "UNDO command" << std::endl;
				cmd = new command();
				break;

			case command::Shapes::CIRCLE:
				std::cout << "command to draw CIRCLE" << std::endl;
				circle = (command::Circle*) packet->data;
				cmd = new command(*circle);
				break;

			case command::Shapes::LINE:
				std::cout << "command to draw LINE" << std::endl;
				line = (command::Line*) packet->data;
				cmd = new command(*line);
				break;

			case command::Shapes::RECT:
				std::cout << "command to draw RECT" << std::endl;
				rect = (command::Rect*) packet->data;
				cmd = new command(*rect);
				break;

			case command::Shapes::SPOINT:
				std::cout << "command to draw POINT" << std::endl;
				point = (command::SPoint*) packet->data;
				cmd = new command(*point);
				break;

			case command::Shapes::TRIANGLE:
				std::cout << "command to draw TRIANGLE" << std::endl;
				triangle = (command::Triangle*) packet->data;
				cmd = new command(*triangle);
				break;

            default:
                std::cout << "Unhandled packet in Receive with pid " << pid << " from " << packet->systemAddress.ToString() << std::endl;
                break;
        }
        m_peer->DeallocatePacket(packet);
		return true;
    }

    return false;
}


//void Send(RakNet::Packet &packet, RakNet::AddressOrGUID const &systemIdentifier, bool broadcast);
void RakNetServer::DeallocatePacket(RakNet::Packet *packet) {
    m_peer->DeallocatePacket(packet);
}

void RakNetServer::BroadcastPoint(command::Point pointStruct)
{
	RakNet::BitStream bsOut;
	bsOut.Write((RakNet::MessageID)command::Shapes::SPOINT);
	bsOut.Write(pointStruct);
	m_peer->Send(&bsOut, HIGH_PRIORITY, RELIABLE_ORDERED, 0, RakNet::UNASSIGNED_SYSTEM_ADDRESS, true);
}

void RakNetServer::BroadcastLine(command::Line lineStruct)
{
	RakNet::BitStream bsOut;
	bsOut.Write((RakNet::MessageID)command::Shapes::LINE);
	bsOut.Write(lineStruct);
	m_peer->Send(&bsOut, HIGH_PRIORITY, RELIABLE_ORDERED, 0, RakNet::UNASSIGNED_SYSTEM_ADDRESS, true);
}

void RakNetServer::BroadcastRect(command::Rect rectStruct, RakNet::RakNetGUID guid)
{
	RakNet::BitStream bsOut;
	bsOut.Write((RakNet::MessageID)command::Shapes::RECT);
	bsOut.Write(rectStruct);
	bsOut.Write(guid);
	m_peer->Send(&bsOut, HIGH_PRIORITY, RELIABLE_ORDERED, 0, RakNet::UNASSIGNED_SYSTEM_ADDRESS, true);
}

void RakNetServer::BroadcastCircle(command::Circle circleStruct)
{
	RakNet::BitStream bsOut;
	bsOut.Write((RakNet::MessageID)command::Shapes::CIRCLE);
	bsOut.Write(circleStruct);
	m_peer->Send(&bsOut, HIGH_PRIORITY, RELIABLE_ORDERED, 0, RakNet::UNASSIGNED_SYSTEM_ADDRESS, true);
}

void RakNetServer::BroadcastTriangle(command::Triangle triangleStruct)
{
	RakNet::BitStream bsOut;
	bsOut.Write((RakNet::MessageID)command::Shapes::TRIANGLE);
	bsOut.Write(triangleStruct);
	m_peer->Send(&bsOut, HIGH_PRIORITY, RELIABLE_ORDERED, 0, RakNet::UNASSIGNED_SYSTEM_ADDRESS, true);
}