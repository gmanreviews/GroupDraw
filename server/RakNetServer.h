#ifndef RAKNET_SERVER_H
#define RAKNET_SERVER_H

#include <string>
namespace RakNet {
    struct Packet;
    struct AddressOrGUID;
    class RakPeerInterface;
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

    RakNet::Packet *Receive();
    void Send(RakNet::Packet &packet, RakNet::AddressOrGUID const &systemIdentifier, bool broadcast);
    void DeallocatePacket(RakNet::Packet *packet);

private:
    RakNet::RakPeerInterface *m_peer;
};

#endif