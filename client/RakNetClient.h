#ifndef RAKNET_CLIENT_H
#define RAKNET_CLIENT_H

#include <string>
#include "../sharedContent.h"

namespace RakNet {
    struct Packet;
    struct SystemAddress;
    struct RakNetGUID;
    class RakPeerInterface;
	class BitStream;
}
class RakNetClient
{
public:
    RakNetClient();
    ~RakNetClient();

    bool Start();
    void Shutdown(bool sendNotification);
    bool IsActive();

    bool Connect(unsigned int port, std::string const &ip);
    void Disconnect(bool sendNotification);
    bool IsConnected();

    RakNet::Packet *Receive();
    void Send(RakNet::Packet &packet);
	void Send(Shared::ClientToServer dataStruct);
    void DeallocatePacket(RakNet::Packet *packet);

private:
    RakNet::RakPeerInterface *m_peer;
    RakNet::RakNetGUID *m_serverGUID;
    RakNet::SystemAddress *m_serverAddress;
	RakNet::BitStream *m_stream;
};

#endif