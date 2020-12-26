//
// Created by zoix on 23/12/2020.
//

#include "../include/connectionHandler.h"
#include <stdlib.h>
#include <mutex>

using namespace std;
bool connected = true;
mutex _mutex;


class KeyboardReader{

private:
    ConnectionHandler * connectionHandler;
public:
    KeyboardReader(ConnectionHandler &connectionHandler) : connectionHandler(&connectionHandler){}
    void run() {

        while (connected){

            lock_guard<mutex> lock(_mutex);

            const short bufsize = 1024;
            char buf[bufsize];
            cin.getline(buf,bufsize);
            string line(buf);
            vector<string*> commandline;
            connectionHandler->analyse(commandline,line);



            if (*commandline[0] == "ADMINREG"){
                char  * opcode = (char *)(malloc(2));
                connectionHandler->shortToBytes(1, opcode);
                connectionHandler->sendBytes(opcode, 2);
                connectionHandler->sendFrameAscii(*commandline[1],'\0');
                connectionHandler->sendFrameAscii(*commandline[2],'\0');
                free(opcode);
            }
            else if (*commandline[0] == "STUDENTREG"){
                char  * opcode = (char *)(malloc(2));
                connectionHandler->shortToBytes(2, opcode);
                connectionHandler->sendBytes(opcode, 2);
                connectionHandler->sendFrameAscii(*commandline[1],'\0');
                connectionHandler->sendFrameAscii(*commandline[2],'\0');
                free(opcode);
            }
            else if (*commandline[0] == "LOGIN"){
                char  * opcode = (char *)(malloc(2));
                connectionHandler->shortToBytes(3, opcode);
                connectionHandler->sendBytes(opcode, 2);
                connectionHandler->sendFrameAscii(*commandline[1],'\0');
                connectionHandler->sendFrameAscii(*commandline[2],'\0');
                free(opcode);
            }
            else if (*commandline[0] == "LOGOUT"){
                char  * opcode = (char *)(malloc(2));
                connectionHandler->shortToBytes(4, opcode);
                connectionHandler->sendBytes(opcode, 2);
                free(opcode);
            }
            else if (*commandline[0] == "COURSEREG"){
                char  * opcode = (char *)(malloc(2));
                connectionHandler->shortToBytes(5, opcode);
                connectionHandler->sendBytes(opcode, 2);
                short * courseNumber = (short *)malloc( 2);
                char command[commandline[1]->length()];
                connectionHandler->relax(command,commandline[1]);
                connectionHandler->sendBytes(command,2);
                free(opcode);
                free(courseNumber);
            }
            else if (*commandline[0] == "KDAMCHECK"){
                char  * opcode = (char *)(malloc(2));
                connectionHandler->shortToBytes(6, opcode);
                connectionHandler->sendBytes(opcode, 2);
                short * courseNumber = (short *)malloc( 2);
                char command[commandline[1]->length()];
                connectionHandler->relax(command,commandline[1]);
                connectionHandler->sendBytes(command,2);
                free(opcode);
                free(courseNumber);

            }
            else if (*commandline[0] == "COURSESTAT"){char  * opcode = (char *)(malloc(2));
                connectionHandler->shortToBytes(7, opcode);
                connectionHandler->sendBytes(opcode, 2);
                short * courseNumber = (short *)malloc( 2);
                char command[commandline[1]->length()];
                connectionHandler->relax(command,commandline[1]);
                connectionHandler->sendBytes(command,2);
                free(opcode);
                free(courseNumber);
            }
            else if (*commandline[0] == "STUDENTSTAT"){
                char  * opcode = (char *)(malloc(2));
                connectionHandler->shortToBytes(8, opcode);
                connectionHandler->sendBytes(opcode,2);
                connectionHandler->sendFrameAscii(*commandline[1],'\0');
                free(opcode);
            }
            else if (*commandline[0] == "ISREGISTERED"){
                char  * opcode = (char *)(malloc(2));
                connectionHandler->shortToBytes(9, opcode);
                connectionHandler->sendBytes(opcode, 2);
                short * courseNumber = (short *)malloc( 2);
                char command[commandline[1]->length()];
                connectionHandler->relax(command,commandline[1]);
                connectionHandler->sendBytes(command,2);
                free(opcode);
                free(courseNumber);
            }
            else if (*commandline[0] == "UNREGISTER"){
                char  * opcode = (char *)(malloc(2));
                connectionHandler->shortToBytes(10, opcode);
                connectionHandler->sendBytes(opcode, 2);
                short * courseNumber = (short *)malloc( 2);
                char command[commandline[1]->length()];
                connectionHandler->relax(command,commandline[1]);
                connectionHandler->sendBytes(command,2);
                free(opcode);
                free(courseNumber);
            }
            else if (*commandline[0] == "MYCOURSES"){
                char  * opcode = (char *)(malloc(2));
                connectionHandler->shortToBytes(11, opcode);
                connectionHandler->sendBytes(opcode, 2);
                short * courseNumber = (short *)malloc( 2);
                char command[commandline[1]->length()];
                connectionHandler->relax(command,commandline[1]);
                connectionHandler->sendBytes(command,2);
                free(opcode);
                free(courseNumber);
            }

            else{
                cout<< "Damn wrong message detected" <<endl;
                break;
                }

        }




    }

};


class SocketReader{

private:
    ConnectionHandler * connectionHandler;
public:
    SocketReader(ConnectionHandler &connectionHandler) : connectionHandler(&connectionHandler){}
    void run() {
        while (connected) {
        lock_guard<mutex> lock(_mutex);

            char * replyBytes[4];
            connectionHandler->getBytes(*replyBytes,4);
            char * opcodeAsBytes[] = {replyBytes[0], replyBytes[1]};
            char * messageOpcodeAsBytes[] = {replyBytes[2],replyBytes[3]};

            short opcode = connectionHandler->bytesToShort(*opcodeAsBytes);
            short messageOpcode = connectionHandler->bytesToShort(*messageOpcodeAsBytes);


            if (opcode == 12){
                string optionalPart;
                connectionHandler->getFrameAscii(optionalPart,'\0');
                optionalPart = optionalPart.substr(0,optionalPart.length()-1); // it may be -2 to remove null character, will see during testing...
                string space = " ";
                optionalPart = space.append(optionalPart);
                cout<< "ACK " << messageOpcode << optionalPart << endl;
            }
            else if (opcode == 13){
                cout<<"ERROR " << messageOpcode << endl;
            }
            else{
                cout<< "Damn wrong message detected" <<endl;
                break;
            }
        }
    }
};



int main (int argc, char *argv[]) {
        if (argc < 3) {
            cerr << "Usage: " << argv[0] << " host port" << endl << endl;
            return -1;
        }
        string host = argv[1];
        short port = atoi(argv[2]);

        ConnectionHandler connectionHandler(host, port);
        if (!connectionHandler.connect()) {
            cerr << "Cannot connect to " << host << ":" << port << endl;
            return 1;
        }


        KeyboardReader keyboardReader(connectionHandler);
        SocketReader socketReader(connectionHandler);


        thread keyboardListener(&KeyboardReader::run,keyboardReader);
        thread socketListener(&SocketReader::run,socketReader);



        keyboardListener.join();
        socketListener.join();
        connectionHandler.close();
        return 0;
}