#pragma once
#include <vector>
#include <RakNetTypes.h>
#include "command.h"

class InMemoryDB
{
public:

	static InMemoryDB& instance()
	{
		static InMemoryDB* instance = new InMemoryDB();
		return *instance;
	}

	struct Register
	{
		command* cmd;
		bool active;
		int id;
		RakNet::RakNetGUID guid;
	};

	InMemoryDB::Register* SaveCommandServer(command* cmd, RakNet::RakNetGUID guid);

	InMemoryDB::Register* SaveCommandClient(command* cmd, RakNet::RakNetGUID guid);

private:

	static int idCount;
	
	std::vector<Register*> table = std::vector<Register*>();
};