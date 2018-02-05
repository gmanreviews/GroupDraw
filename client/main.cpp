#include <Windows.h>
#include "ClientManager.h"


int main(int argc, char **argv) {
	bool flagConnection;

	flagConnection = ClientManager::instance().InitClient();

	if (flagConnection) {
		ClientManager::instance().RunClientLoop();
		return 0;
	}
	else {
		std::cout << "Connection with server failed" << std::endl;
		std::getchar();
		return -1;
	}
}