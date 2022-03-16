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
		if (cls == nullptr || newCmd == nullptr)
			throw std::exception("Command init : unexpected 'nullptr' from function's params");
		if (args.size() != sizeof...(Args))
			throw std::exception("Command init : Inits uncorrect count of arguments");

		funcCaller = [cls, newCmd](const std::vector<int>& funcArgs) {
			return CallFunc(cls, newCmd, funcArgs, std::make_index_sequence<sizeof...(Args)>{});
		};
	}

	int executeCommand(const std::vector<int>& funcArgs) {
		return funcCaller(funcArgs);
	}
};

class CommandArguments {
	std::map<std::string, int*> arguments;
	std::vector<int> values;

public:
	CommandArguments() = delete;

	CommandArguments(const std::vector<std::pair<std::string, int>> args) {
		for (auto arg : args) {
			values.push_back(arg.second);
			arguments.insert(std::pair<std::string, int*>(arg.first, &values.back()));
		}
	}

	size_t size() const {
		return arguments.size();
	}

	void update(const std::string name, int val) {
		if(arguments.find(name) == arguments.end())
			throw std::exception("Command arguments : unknown argument name");

		*arguments[name] = val;
	}

	std::vector<int> getValues() const {
		return values;
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
		return cmd.executeCommand(cmdArgs.getValues());
	}
};
