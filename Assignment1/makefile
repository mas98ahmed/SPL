# Tool invocations
make: bin/main.o bin/Session.o bin/Agent.o bin/Tree.o bin/Graph.o
	@echo 'Invoking: C++ Linker'
	g++ -o bin/cTrace bin/main.o bin/Session.o bin/Agent.o bin/Tree.o bin/Graph.o
	@echo 'Finished building target: Success'
	@echo ' '

# Depends on the source and header files 
bin/main.o: src/main.cpp
	g++ -g -Wall -Weffc++ -std=c++11 -c -IInclude -o bin/main.o src/main.cpp

# Depends on the source and header files
bin/Session.o: src/Session.cpp
	g++ -g -Wall -Weffc++ -std=c++11 -c -IInclude -o bin/Session.o src/Session.cpp
	
bin/Agent.o: src/Agent.cpp
	g++ -g -Wall -Weffc++ -std=c++11 -c -IInclude -o bin/Agent.o src/Agent.cpp

bin/Tree.o: src/Tree.cpp
	g++ -g -Wall -Weffc++ -std=c++11 -c -IInclude -o bin/Tree.o src/Tree.cpp
	 
bin/Graph.o: src/Graph.cpp
	g++ -g -Wall -Weffc++ -std=c++11 -c -IInclude -o bin/Graph.o src/Graph.cpp
	

# Clean the build directory
clean: 
	rm -f bin/*