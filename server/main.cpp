
#include "ServerManager.h"

#include <iostream>


int main(int argc, char **argv) {
	bool flagConnection;

	flagConnection = ServerManager::instance().InitServer();

	if (flagConnection) {
		ServerManager::instance().RunServerLoop();
		return 0;
	}
	else {
		std::cout << "Server failed" << std::endl;
		std::getchar();
		return -1;
	}
}