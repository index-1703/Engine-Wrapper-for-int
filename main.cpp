#include <cstdlib>
#include <iostream>

#include "wrapper.h"
#include "engine.h"

class Subject {

public:
	int foo(int a, int b) {
		return a < b;
	}
};

class Factorial {
public:
	int fact(int num) {
		int res = 1;

		for (int i = 1; i <= num; i++) {
			res = res * i;
		}

		return res;
	}
};


int main(void) {
	Subject subj;
	Factorial fact;

	Wrapper wrapperSubj(&subj, &Subject::foo, { {"arg1", 0}, {"arg2", 0} });
	Wrapper wrapperFact(&fact, &Factorial::fact, { {"num", 0} });

	Engine engine;
	engine.register_command(&wrapperSubj, "command1");
	engine.register_command(&wrapperFact, "factorial");

	std::cout << engine.execute("command1", { {"arg1", 0}, {"arg2", -1} }) << " " << engine.execute("command1", { {"arg1", -1}, {"arg2", 1}}) << std::endl;
	std::cout << engine.execute("factorial", { {"num", 2} }) << " " << engine.execute("factorial", {{"num", 5}}) << std::endl;

	return 0;
}