/*
 * MessengerServer.cpp
 *
 *  Created on: May 1, 2016
 *      Author: user
 */

#include "MessengerServer.h"

using namespace std;
using namespace npl;

//constructor for client-server connection
MessengerServer::MessengerServer() {
	dispatcher = new Dispatcher();
	socket = new TCPSocket(MSNGR_PORT);
	//run "run" function (MThread)
	start();
}

void MessengerServer::listSessions(){
	this->dispatcher->listSessions();
}

//virtual destructor
MessengerServer::~MessengerServer() {

}
void MessengerServer::listUsers(){
	this->dispatcher->listUsers();
}
void MessengerServer::listConnectedUsers(){
	this->dispatcher->listConnectedUsers();
}

//closing all client-server connections
void MessengerServer::exit(){
	socket->close();
	delete socket;
	dispatcher->close();
	delete dispatcher;
}

void MessengerServer::listRoomUsers(const string& roomName){
	this->dispatcher->listRoomUsers(roomName);
}

//creating MThread for the server
void MessengerServer::run(){
	while(true){
		//open server MThread for peers who want to connect
		TCPSocket* peer = socket->listenAndAccept();
		if(peer == NULL){
			break;
		}
		cout << "The peer " << socket->fromAddr() << " Connected" << endl;
		//adding the peer to the peers list
		dispatcher->add(peer);
	}
}
void MessengerServer::listRooms(){
	this->dispatcher->listRooms();
}
