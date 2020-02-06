scheduler: event.cpp event.hpp main.cpp GlobalVariable.cpp GlobalVariable.hpp scheduler.cpp scheduler.hpp 
	g++ -std=c++0x scheduler.cpp scheduler.hpp main.cpp GlobalVariable.cpp GlobalVariable.hpp event.cpp event.hpp -o sched

clean:
	rm -f scheduler*~ GlobalVariable*~ event*~ main*~ makefile*~
