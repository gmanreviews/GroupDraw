#pragma once
#include "InMemoryDB.h"

InMemoryDB::Register* InMemoryDB::SaveCommandServer(command* cmd, RakNet::RakNetGUID guid) {
	Register* reg = new Register();
	reg->active = true;
	reg->id = InMemoryDB::idCount;
	cmd->setId(InMemoryDB::idCount);
	reg->cmd = cmd;
	reg->guid = guid;
	table.push_back(reg);
	InMemoryDB::idCount++;
	return reg;
}

InMemoryDB::Register* InMemoryDB::SaveCommandClient(command* cmd, RakNet::RakNetGUID guid) {
	Register* reg = new Register();
	reg->active = true;
	reg->id = cmd->getId();
	reg->cmd = cmd;
	table.push_back(reg);
	return reg;
}


int InMemoryDB::idCount = 0;

