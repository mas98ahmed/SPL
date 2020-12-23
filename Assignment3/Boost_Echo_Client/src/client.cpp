//
// Created by zoix on 23/12/2020.
//

#include "../include/connectionHandler.h"
using namespace std;
bool connected = true;
class KeyboardReader{

private:
    ConnectionHandler * connectionHandler;
public:
    KeyboardReader(ConnectionHandler &connectionHandler) : connectionHandler(connectionHandler){}
    void run() {

        while (connected){
            const short bufsize = 1024;
            char buf[bufsize];
            cin.getline(buf,bufsize);
            string line(buf);
            int len = line.length();
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

        thread keyboardListener(keyboardReader);
        thread socketListener(socketReader);

        keyboardListener.join();
        socketListener.join();


    }

};