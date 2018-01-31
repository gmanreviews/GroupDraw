
#include "RakNetServer.h"

#include <RakSleep.h>

#include <Windows.h>

#include <iostream>


int main(int argc, char **argv) {
	RakNetServer server;
	server.Start(1288, 10);
	//Sleep(1000);
	//server.Shutdown(1000);
	//Make sure the server block duration is allowed to run to completion.
	//Sleep(1500);

	while (true) {
		RakNet::Packet *packet = server.Receive();
		if (packet != NULL) {
			server.DeallocatePacket(packet);
		}
		RakSleep(50);
	}

}