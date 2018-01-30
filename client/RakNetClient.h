#ifndef RAKNET_CLIENT_H
#define RAKNET_CLIENT_H

#include <string>
namespace RakNet {
    struct Packet;
    struct SystemAddress;
    struct RakNetGUID;
    class RakPeerInterface;
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
    void DeallocatePacket(RakNet::Packet *packet);

private:
    RakNet::RakPeerInterface *m_peer;
    RakNet::RakNetGUID *m_serverGUID;
    RakNet::SystemAddress *m_serverAddress;
};

#endif