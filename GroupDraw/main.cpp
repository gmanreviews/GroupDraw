
#include "RakNetClient.h"


#include <Windows.h>

#include <iostream>


int main(int argc, char **argv) {
    RakNetClient client;
    client.Start();
    client.Connect(1288,"127.0.0.1");
    Sleep(1000);
    client.Disconnect(true);
    client.Shutdown(true);
    //Make sure the server block duration is allowed to run to completion.
    Sleep(1500);

}