#ifndef RAKNET_CLIENT_H
#define RAKNET_CLIENT_H

#include <string>
#include "../sharedContent.h"
#include "../command.h"

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

	void ListenServer();
	void Send(Shared::NetworkCommand dataStruct, int messageType);

	void SendPoint(command::Shape* pointStruct);
	void SendLine(command::Shape* lineStruct);
	void SendRect(command::Shape* rectStruct);
	void SendCircle(command::Shape* circleStruct);
	void SendTriangle(command::Shape* triangleStruct);

private:
    RakNet::RakPeerInterface *m_peer;
    RakNet::RakNetGUID *m_serverGUID;
    RakNet::SystemAddress *m_serverAddress;
	RakNet::BitStream *m_stream;
	RakNet::Packet *packet;
	//RakNet::SystemAddress address;
};

#endif