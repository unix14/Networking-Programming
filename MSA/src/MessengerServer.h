

#ifndef MESSENGERSERVER_H_
#define MESSENGERSERVER_H_

#include "Dispatcher.h"


namespace npl {

//MThread for client server connection
class MessengerServer : public MThread{
	TCPSocket* socket;
	Dispatcher* dispatcher;

public:
	MessengerServer();
	virtual ~MessengerServer();


	void listUsers();
	void listConnectedUsers();
	void listSessions();
	void listRooms();
	void listRoomUsers(const string& roomName);
	void exit();
	void run();
};

} /* namespace npl */

#endif /* MESSENGERSERVER_H_ */
