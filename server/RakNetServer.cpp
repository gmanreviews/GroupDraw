#include "RakNetServer.h"
#include "../GroupDraw/GroupDrawMessageIdentifiers.h"

#include <RakPeerInterface.h>
#include <MessageIdentifiers.h>

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

RakNet::Packet *RakNetServer::Receive() {
    RakNet::Packet *packet = m_peer->Receive();
    while(packet != NULL) {
        unsigned char pid = packet->data[0];
        switch(pid) {
            case ID_NEW_INCOMING_CONNECTION:
                std::cout << "Incoming connection from " << packet->systemAddress.ToString() << std::endl;
                break;
            case ID_DISCONNECTION_NOTIFICATION:
                std::cout << "Disconnection notification from " << packet->systemAddress.ToString() << std::endl;
                break;
            case ID_CONNECTION_LOST:
                std::cout << "Lost connection with " << packet->systemAddress.ToString() << std::endl;
                break;

            case ID_GRP_JOIN_REQUEST: //This is a reminder that user defined packets should be returned.
                return packet;

            default:
                std::cout << "Unhandled packet in Receive with pid " << pid << " from " << packet->systemAddress.ToString() << std::endl;
                break;
        }
        m_peer->DeallocatePacket(packet);
        packet = m_peer->Receive();
    }

    return NULL;
}

//void Send(RakNet::Packet &packet, RakNet::AddressOrGUID const &systemIdentifier, bool broadcast);
void RakNetServer::DeallocatePacket(RakNet::Packet *packet) {
    m_peer->DeallocatePacket(packet);
}