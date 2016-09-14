//============================================================================
// Name        : Client Main.cpp
// Author      : Eyal Yaakovi & Shahar Tako
// Version     : 1.0
// Copyright   : College of Management
// Description : Network Programming Project
//============================================================================

#include <iostream>
#include "MessengerClient.h"


using namespace std;
using namespace npl;

void help();

int main() {
	cout << "Messenger Client Application" << endl<<endl;
	MessengerClient * client = new MessengerClient();
	help();							//Print commands
	string msg;						//get msg from user
	string command;					//command from user

	while (true) {
		msg.clear();
		command.clear();

		cin >> command;				//get user command
		if (command == "c") {
			string ip;
			cin >> ip;
			client->connect(ip);
		}else if (command == "login") {
			string user;
			cin >> user;
			string password;
			cin >> password;
			client->login(user, password);
		}else if (command == "register") {
			string user;
			cin >> user;
			string password;
			cin >> password;
			client->registerUser(user, password);
		}else if (command == "lu") {
			client->listUsers();
		}else if (command == "lcu") {
			client->listConnectedUsers();
		}else if (command == "lr") {
			client->listRooms();

		}else if (command == "lru") {		//List all users in a room
			string roomName;
			cin >> roomName;
			client->listRoomUsers(roomName);
		}else if (command == "or") {
			string roomName;
			cin >> roomName;
			client->enterRoom(roomName);
		}else if (command == "l") {
			client->printClientStatus();
		}else if (command == "cr") {		//Close room
			client->closeCurrentRoom();
		}else if (command == "o") {
			string peerUser;
			cin >> peerUser;
			client->openSession(peerUser);
		}else if (command == "s"){
			getline(std::cin, msg);
			if (msg.length() > 0 && msg[0] == ' ')
				msg.erase(0, 1);
			client->send(msg);
		}else if (command == "cs") {
			client->closeSessionOrExitRoom();
		}else if (command == "d") {
			client->disconnect();
		}else if (command == "help"){	//Print Commands
        	help();
        }else if (command == "x") {		//Exit
			client->exit();
			break;
		}else {
			cout << "Wrong Command" << endl;
		}
	}
	cout << "messenger was closed" << endl;
	return 0;
}

void help() {
	cout << "c <ip> - Connect to Server" << endl
	 << "login <user> <password> - Log in to Server" << endl
	 << "register <user> <password> - Register to Server" << endl<<endl
	 << "lu - List all Users from Server" << endl
	 << "lcu - List all Connected Users from Server" << endl
	 << "lr - List Rooms available in Server" << endl
	 << "lru <room name> - List Users in a Room " << endl<<endl
	 << "o <user> - Open Session with user" << endl
	 << "or <room name> - Open a Room"<< endl
	 << "s <message> - Send Message" << endl
	 << "cs - Close Session / Exit room " << endl
	 << "cr - Close Room [Admin only]" << endl<<endl
	 << "l - Print User status" << endl
	 << "help - Print Commands"<<endl
	 << "d - Disconnect" << endl
	 << "x - Exit" << endl;
}
