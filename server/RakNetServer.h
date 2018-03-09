#ifndef RAKNET_SERVER_H
#define RAKNET_SERVER_H

#include <string>
#include <RakNetTypes.h>
#include "../command.h"

namespace RakNet {
    struct Packet;
    struct AddressOrGUID;
    class RakPeerInterface;
	class BitStream;
}

class RakNetServer
{
public:
    RakNetServer();
    ~RakNetServer();

    bool Start(unsigned short port, unsigned int maxConnections);
    void Shutdown(unsigned int blockDuration);
    bool IsActive();

    unsigned short GetMaxConnections();
    unsigned short GetMaxIncomingConnections();
    unsigned short GetCurrentConnections();

    unsigned short GetCurrentPort();

    bool ListenClients(command* &cmd, RakNet::RakNetGUID &clientId);
    void Send(RakNet::Packet &packet, RakNet::AddressOrGUID const &systemIdentifier, bool broadcast);

	void BroadcastPoint(command::Point pointStruct);
	void BroadcastLine(command::Line lineStruct);
	void BroadcastRect(command::Rect rectStruct, RakNet::RakNetGUID guid);
	void BroadcastCircle(command::Circle circleStruct);
	void BroadcastTriangle(command::Triangle triangleStruct);

    void DeallocatePacket(RakNet::Packet *packet);

private:
	RakNet::Packet *packet;
    RakNet::RakPeerInterface *m_peer;
};

#endif