
#ifndef SRC_DISPATCHER_H_
#define SRC_DISPATCHER_H_

#include <algorithm>
#include <vector>
#include <map>
#include "Brocker.h"
#include "MultipleTCPSocketListener.h"
#include "TCPMessengerProtocol.h"
#include "ChatRoom.h"
#include "Users.h"

namespace npl {

//MThread, call-back for chat room and brocker
class Dispatcher: public MThread,
		ChatRoom::ChatRoomHandler,
		Brocker::BrockerHandler {


	vector<TCPSocket*> peers;//peers list
	vector<Brocker*> brockers;//brocbers list
	vector<ChatRoom*> chatRooms;//chat rooms list
	map<string, string> registeredUsers; //users who are registered-in ram
	map<string, TCPSocket*> loggedInUsers; //logged in and connected- in ram- user name and ip
	MultipleTCPSocketListener* listener;
	Users* users;//list of user from users class (name, password)

	bool running;
	void login(TCPSocket* peer, const string& data);
	void registerUser(TCPSocket* peer, const string& data);
	void enterRoom(TCPSocket* peer, const string& data);
	void openSession(TCPSocket* peer, const string& data);
	void listUsers(TCPSocket* peer, const string& data);
	void listConnectedUsers(TCPSocket* peer, const string& data);
	void listRooms(TCPSocket* peer, const string& data);
	void listRoomUsers(TCPSocket* peer, const string& data);
	void exit(TCPSocket* peer, const string& data);
public:
	Dispatcher();

	void listUsers();
	void listConnectedUsers();
	void listSessions();
	void listRooms();
	void listRoomUsers(const string& roomName);

	void add(TCPSocket* peer);
	void removePeer(TCPSocket* peer);
	void run();
	void close();

	//call back client make an exit from brocker or chatroom without notifying
	virtual void onClientExit(Brocker * brocker, TCPSocket* peerA,TCPSocket* peerB);
	virtual void onClientExit(ChatRoom* chatRoom, TCPSocket* peer);

	//call back client make disconnect from a chatroom
	virtual void onClientDisconnect(ChatRoom* chatRoom, TCPSocket* peer);

	//call back closing chatroom or brocker- client notifying
	virtual void onClose(ChatRoom* chatRoom, map<string, TCPSocket*> peersMap);
	virtual void onClose(Brocker * brocker, TCPSocket* peerA, TCPSocket* peerB);

	//validation- if the user logged in oe not
	bool isLoggedIn(TCPSocket *sock);

};

} /* namespace npl */

#endif /* SRC_DISPATCHER_H_ */
