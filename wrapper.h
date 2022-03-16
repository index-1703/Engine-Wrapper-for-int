#pragma once

#include <functional>
#include <string>
#include <vector>
#include <map>

class Command {
private:
	std::function<int(const std::vector<int>& args)> funcCaller;

	template<typename Class, typename Function, size_t ...indexies>
	static int CallFunc(Class* cls, Function method, const std::vector<int>& args, std::index_sequence<indexies...>) {
		return (cls->*method)(args[indexies]...);
	}
public:
	Command() = delete;

	template<class Class, typename ...Args>
	Command(Class* cls, int(Class::* newCmd)(Args...)) {
		funcCaller = [cls, newCmd](const std::vector<int>& funcArgs) {
			return CallFunc(cls, newCmd, funcArgs, std::make_index_sequence<sizeof...(Args)>{});
		};
	}

	int executeCommand(const std::vector<int>& funcArgs) {
		return funcCaller(funcArgs);
	}
};

class CommandArguments {
	std::map<std::string, int> arguments;
	std::vector<int*> pValues;

public:
	CommandArguments() = delete;

	CommandArguments(const std::vector<std::pair<std::string, int>> args) {
		for (auto arg : args) {
			pValues.push_back(&(arguments.insert(arg).first->second));
		}
	}

	size_t size() const {
		return arguments.size();
	}

	int& value(const std::string name) {
		return arguments[name];
	}

	void update(const std::string name, int val) {
		value(name) = val;
	}

	std::vector<int> values() {
		std::vector<int> resultVec;

		for (auto val : pValues) {
			resultVec.push_back(*val);
		}

		return resultVec;
	}
};

class Wrapper {
private:
	Command cmd;
	CommandArguments cmdArgs;

public:
	Wrapper() = delete;

	template<typename Class, typename ...Args>
	Wrapper(Class* cls, int(Class::* newCmd)(Args...), const std::vector<std::pair<std::string, int>> args) 
	: cmd(cls, newCmd) ,cmdArgs(args) {	}

	void correctArguments(std::vector<std::pair<std::string, int>> args) {
		for (auto arg : args) {
			cmdArgs.update(arg.first, arg.second);
		}
	}

	int executeCommand(std::vector<std::pair<std::string, int>> args = {}) {
		correctArguments(args);
		return cmd.executeCommand(cmdArgs.values());
	}
};
