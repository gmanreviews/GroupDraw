#include "RakNetClient.h"

#include <RakPeerInterface.h>
#include <RakSleep.h>
#include <MessageIdentifiers.h>
#include <BitStream.h>

#include <iostream>

RakNetClient::RakNetClient() 
    : m_peer(RakNet::RakPeerInterface::GetInstance()), 
	  m_serverAddress(new RakNet::SystemAddress()), 
	  m_serverGUID(new RakNet::RakNetGUID()), 
	  m_stream(new RakNet::BitStream()),
      window(new sf::RenderWindow())
{
	window->create(sf::VideoMode(800, 600), "Chat");
}


RakNetClient::~RakNetClient()
{
    if(m_peer != NULL) {
        RakNet::RakPeerInterface::DestroyInstance(m_peer);
    }
	if (window != nullptr)
	{
		delete(window);
	}
}

//Returns true if the server is started.
bool RakNetClient::Start() {
    if(m_peer != NULL) {
        RakNet::SocketDescriptor sd;
        RakNet::StartupResult result = m_peer->Startup(1, &sd, 1);
        switch(result) {
            case RakNet::RAKNET_STARTED:
                std::cout << "Client Started" << std::endl;
                return true;
            case RakNet::RAKNET_ALREADY_STARTED:
                std::cout << "Client was already started" << std::endl;
                return true;
            default:
                std::cerr << "Unknown potentially bad StartupResult " << result << " on Startup." << std::endl;
                return false;
        }
    }
    std::cerr << "Server has a null m_peer" << std::endl;
    return false;
}

void RakNetClient::Shutdown(bool sendNotification) {
    if(m_peer != NULL) {
        std::cout << "Client shutting down" << std::endl;
        m_peer->Shutdown(sendNotification ? 0 : 300, 0, LOW_PRIORITY);
    }
}

bool RakNetClient::IsActive() {
    return m_peer != NULL ? m_peer->IsActive() : false;
}

bool RakNetClient::Connect(unsigned int port, std::string const &ip) {
    if(m_peer == NULL) {
        std::cerr << "m_peer is NULL" << std::endl;
        return false;
    } else if(!m_peer->IsActive()) {
        std::cerr << "Client has not been started yet, call Start() before you call Connect()" << std::endl;
        return false;
    }
    //Attemp to connect to the server at the specified port.
    RakNet::ConnectionAttemptResult result = m_peer->Connect(ip.c_str(), port, NULL, 0);
    switch(result) {
        case RakNet::CONNECTION_ATTEMPT_STARTED:
        case RakNet::CONNECTION_ATTEMPT_ALREADY_IN_PROGRESS:
            break;
        case RakNet::ALREADY_CONNECTED_TO_ENDPOINT:
            std::cout << "You have already successfully connected to " << ip << "|" << port << std::endl;
            return true;
        default:
            std::cerr << "Attemp to connect returned code " << result << " which is currently unhandled." << std::endl;
            return false;
    }
    //Wait for a packet from the server indicating we have successfully connected or not.
    bool done = false;
    while(!done) {
        RakNet::Packet *packet = m_peer->Receive();
        if(packet != NULL) {
			RakNet::BitStream bsOut;
            unsigned char pid = packet->data[0];
            switch(pid) {
                case ID_CONNECTION_REQUEST_ACCEPTED:
                    std::cout << "Connection successful to " << ip << "|" << port << std::endl;
                    *m_serverAddress = packet->systemAddress;
                    *m_serverGUID = packet->guid;
                    done = true;
                    break;
                case ID_CONNECTION_ATTEMPT_FAILED:
                    std::cout << "Connection not successful to " << ip << "|" << port << std::endl;
                    done = true;
                    break;
                default:
                    std::cerr << "Unhandled message in Connect() " << ip << "|" << port << " with pid " << pid << std::endl;
                    done = true;
                    break;
            }
            //Clean up the packet.
            m_peer->DeallocatePacket(packet);
        }
        //Keep things responsive.
        RakSleep(50);
    } //while(!done)

    return IsConnected();
}

void RakNetClient::ListenServer() {
	//bool done = false;
	//while (!done) {
		command* cmd = new command();
		RakNet::Packet *packet = m_peer->Receive();
		if (packet != NULL) {
			RakNet::BitStream bsIn(packet->data, packet->length, false);
			//unsigned char pid = packet->data[0];
			unsigned char pid;
			bsIn.Read(pid);
			switch (pid) {

			case command::Comm::UNDO:
				std::cout << "Got UNDO Command" << std::endl;
				//done = true;
				break;

			case command::Comm::DELETE_SHAPE:
				std::cout << "Got DELETE Command" << std::endl;
				//done = true;
				break;
			
			case command::Shapes::SPOINT:
				std::cout << "Got DELETE Command" << std::endl;
				//done = true;
				break;

			case command::Shapes::LINE:
			{
				std::cout << "Got Command to draw LINE" << std::endl;
				//done = true;
			}
				break;

			case command::Shapes::RECT:
			{
				//command::Rect* rect = new command::Shape(command::Shape::RECT);
				command::Rect* rect = (command::Rect*)packet->data;
				bsIn.Read(*rect);
				cmd->setShapeData(rect);
				cmd->draw(window);
				std::cout << "Got Command to draw RECT" << std::endl;
				//done = true;
			}
				break;
		
			case command::Shapes::CIRCLE:
			{
				std::cout << "Got Command to draw CIRCLE" << std::endl;
				//done = true;
			}
				break;

			case command::Shapes::TRIANGLE:
			{
				std::cout << "Got Command to draw TRIANGLE" << std::endl;
				//done = true;
			}
				break;	

			default:
				std::cerr << "Unhandled message from server " << std::endl;
				//done = true;
				break;
			}
			//Clean up the packet.
			m_peer->DeallocatePacket(packet);
		} 


		delete(cmd);
		//Keep things responsive.
		//RakSleep(50);
	//} //while(!done)
}

void RakNetClient::Disconnect(bool sendNotification) {
    if(m_peer != NULL) {
        m_peer->CloseConnection(*m_serverGUID, sendNotification, 0, HIGH_PRIORITY);
    }
}

bool RakNetClient::IsConnected() {
    if(m_peer != NULL ) {
        return m_peer->GetConnectionState(*m_serverGUID) == RakNet::IS_CONNECTED;
    }
    return false;
}

void RakNetClient::SendPoint(command::Shape* pointStruct)
{
	command::Point point = *(command::Point*)pointStruct;
	m_peer->Send((const char*)&point, sizeof(point), HIGH_PRIORITY, RELIABLE_ORDERED, 0, *m_serverAddress, false);
}

void RakNetClient::SendLine(command::Shape* lineStruct)
{
	command::Line line = *(command::Line*)lineStruct;
	m_peer->Send((const char*)&line, sizeof(line), HIGH_PRIORITY, RELIABLE_ORDERED, 0, *m_serverAddress, false);
}

void RakNetClient::SendRect(command::Shape* rectStruct)
{
	command::Rect rect = *(command::Rect*)rectStruct;
	m_peer->Send((const char*)&rect, sizeof(rect), HIGH_PRIORITY, RELIABLE_ORDERED, 0, *m_serverAddress, false);
}

void RakNetClient::SendCircle(command::Shape* circleStruct)
{
	command::Circle circle = *(command::Circle*)circleStruct;
	m_peer->Send((const char*)&circle, sizeof(circle), HIGH_PRIORITY, RELIABLE_ORDERED, 0, *m_serverAddress, false);
}

void RakNetClient::SendTriangle(command::Shape* triangleStruct)
{
	command::Triangle triangle = *(command::Triangle*)triangleStruct;
	m_peer->Send((const char*)&triangle, sizeof(triangle), HIGH_PRIORITY, RELIABLE_ORDERED, 0, *m_serverAddress, false);
}