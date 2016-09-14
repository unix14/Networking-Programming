//============================================================================
// Name        : Server Main.cpp
// Author      : Eyal Yaakovi & Shahar Tako
// Version     : 1.0
// Copyright   : College of Management
// Description : Network Programming Project
//============================================================================

#include <iostream>
#include "MessengerServer.h"

using namespace std;
using namespace npl;

void help();

int main() {
	string command;						//command from Command Line Interface
	cout<< "Messenger Server Application"<<endl;
	MessengerServer* server = new MessengerServer();	//run server
	help();			//Print commands

	//server is listening while he is running
	while(true){
		//clearing buffer from string "command"
		command.clear();
		cin >> command;
		if(command == "x"){					//Exit- by run destructors
			server->exit();
			break;
		}else if(command == "lu"){			//List all Users from file
            server->listUsers();
        }else if(command == "lcu"){			//List currently connected Users
            server->listConnectedUsers();
        }else if(command == "ls"){			//List all Sessions
            server->listSessions();
        }else if(command == "lr"){			//List all Rooms
            server->listRooms();
        }else if(command == "lru"){			//List users from a room
            string roomName;
            cin >> roomName;
            server->listRoomUsers(roomName);
        }else if (command == "help"){
        	help();
        }else{
			cout<<"Wrong input, try again"<<endl;
		}
	}
	delete server;
	cout<<"Messenger Server was closed"<<endl;
	return 0;
}

void help(){
	cout<<endl
	<< "lu - List Users"<<endl
	<<"lcu- List Connected Users"<<endl
    <<"ls - List Sessions"<<endl
	<<"lr - List Rooms"<<endl
	<<"lru <room name> - List Users in a Room"<<endl<<endl
	<<"help - Show help commands" <<endl
	<<"x - Exit"<<endl;
}
