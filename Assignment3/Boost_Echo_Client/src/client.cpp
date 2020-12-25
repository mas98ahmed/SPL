//
// Created by zoix on 23/12/2020.
//

#include "../include/connectionHandler.h"
#include <mutex>

using namespace std;
bool connected = true;
mutex &_mutex;


class KeyboardReader{

private:
    ConnectionHandler * connectionHandler;
public:
    KeyboardReader(ConnectionHandler &connectionHandler) : connectionHandler(connectionHandler){}
    void run() {

        while (connected){

            string line = cin.getline();
            int len = line.length();
            vector<string*> commandline;
            connectionHandler.analyse(commandline,line);

            if (commandline[0] == "ADMINREG"){
                line = line.substr(line.find(delimiter)+1);
                string username = line.substr(0,line.find(delimiter));
                line = line.substr(line.find(delimiter)+1);
                string password = line;
                connectionHandler->getBytes("1",2);
            }
            else if (commandline[0] == "STUDENTREG"){
                line = line.substr(line.find(delimiter));
                line = line.substr(line.find(delimiter)+1);
            }
            else if (commandline[0] == "LOGIN"){
                line = line.substr(line.find(delimiter));
            }
            else if (commandline[0] == "LOGOUT"){
                line = line.substr(line.find(delimiter));
            }
            else if (commandline[0] == "COURSEREG"){
                line = line.substr(line.find(delimiter));
            }
            else if (commandline[0] == "KDAMCHECK"){
                line = line.substr(line.find(delimiter));
            }
            else if (commandline[0] == "COURSESTAT"){
                line = line.substr(line.find(delimiter));
            }
            else if (commandline[0] == "STUDENTSTAT"){
                line = line.substr(line.find(delimiter));
            }
            else if (commandline[0] == "ISREGISTERED"){
                line = line.substr(line.find(delimiter));
            }
            else if (commandline[0] == "UNREGISTER"){
                line = line.substr(line.find(delimiter));
            }
            else if (commandline[0] == "MYCOURSES"){
                line = line.substr(line.find(delimiter));
            }
            else if (commandline[0] == "ACK"){
                line = line.substr(line.find(delimiter));
            }
            else if (commandline[0] == "ERR"){
                line = line.substr(line.find(delimiter));
            }
                else{

                }
        }



    }
};


class SocketReader{

private:
    ConnectionHandler * connectionHandler;
public:
    SocketReader(ConnectionHandler &connectionHandler) : connectionHandler(connectionHandler){}
    void run() {
        while (connected) {
        lock_guard<mutex> lock(_mutex);
        }
    }
};









    int main (int argc, char *argv[]) {
        if (argc < 3) {
            std::cerr << "Usage: " << argv[0] << " host port" << std::endl << std::endl;
            return -1;
        }
        std::string host = argv[1];
        short port = atoi(argv[2]);

        ConnectionHandler connectionHandler(host, port);
        if (!connectionHandler.connect()) {
            std::cerr << "Cannot connect to " << host << ":" << port << std::endl;
            return 1;
        }

        KeyboardReader keyboardReader(connectionHandler);
        SocketReader socketReader(connectionHandler);

        thread keyboardListener(&keyboardReader::run,keyboardReader);
        thread socketListener(&socketReader::run,socketReader);

        keyboardListener.join();
        socketListener.join();

        connectionHandler.close();

    }

};