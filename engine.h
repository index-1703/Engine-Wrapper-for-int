#pragma once

#include <map>
#include <vector>
#include <string>

#include "wrapper.h"

class Engine {
private:
	std::map<std::string, Wrapper*> cmds;
public:

	Engine() = default;

	Engine(Wrapper* cmd, const std::string& cmdName) {
		register_command(cmd, cmdName);
	}

	void register_command(Wrapper* cmd, const std::string& cmdName) {
		if (cmd == nullptr)
			throw std::exception("Engine register command : unexpected 'nullptr' from 'Wrapper *command' pointer");

		cmds[cmdName] = cmd;
	}

	int execute(const std::string& cmdName, std::vector<std::pair<std::string, int>> args = {}) {
		if (cmds.find(cmdName) == cmds.end())
			throw std::exception("Engine error : unknown command name");

		return cmds[cmdName]->executeCommand(args);
	}
};