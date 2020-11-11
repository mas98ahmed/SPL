# Tool invocations
run: bin/Main.o bin/Session.o bin/User.o bin/Action.o bin/Watchable.o
	@echo 'Invoking: C++ Linker'
	g++ -o bin/test bin/Main.o bin/Session.o bin/User.o bin/Action.o bin/Watchable.o
	@echo 'Finished building target: Proj'
	@echo ' '

# Depends on the source and header files
bin/Main.o: src/Main.cpp
	g++ -g -Wall -Weffc++ -std=c++11 -c -Iinclude -o bin/Main.o src/Main.cpp

# Depends on the source and header files 
bin/Session.o: src/Session.cpp
	g++ -g -Wall -Weffc++ -std=c++11 -c -Iinclude -o bin/Session.o src/Session.cpp
bin/User.o: src/User.cpp
	g++ -g -Wall -Weffc++ -std=c++11 -c -Iinclude -o bin/User.o src/User.cpp
bin/Action.o: src/Action.cpp
	g++ -g -Wall -Weffc++ -std=c++11 -c -Iinclude -o bin/Action.o src/Action.cpp
bin/Watchable.o: src/Watchable.cpp
	g++ -g -Wall -Weffc++ -std=c++11 -c -Iinclude -o bin/Watchable.o src/Watchable.cpp


#Clean the build directory
clean: 
	rm -f bin/*
do: 
	valgrind --leak-check=yes ./bin/test
