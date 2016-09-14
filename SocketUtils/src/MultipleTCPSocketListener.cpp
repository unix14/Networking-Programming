/*
 * MultipleTCPSocketListener.cpp
 *
 *  Created on: Mar 20, 2016
 *      Author: user
 */

#include "MultipleTCPSocketListener.h"

using namespace npl;
	void MultipleTCPSocketListener::add(TCPSocket* socket){
		if (std::find(sockets.begin(),sockets.end(),socket) == sockets.end()) // add to vector if not exist already
			sockets.push_back(socket);

	}

	void MultipleTCPSocketListener::remove(TCPSocket *socket) {
		sockets.erase(std::remove(sockets.begin(),sockets.end(), socket),sockets.end());
	}

	void MultipleTCPSocketListener::add(vector<TCPSocket*> sockets){
		this->sockets = sockets;
	}

	TCPSocket* MultipleTCPSocketListener::listen(int timeout){
		fd_set set;
		int nfd = 0;
		FD_ZERO(&set);
		vector<TCPSocket*>::iterator iter = sockets.begin();
		for(;iter!= sockets.end();iter++){
			TCPSocket* sock = *iter;
			int fd = sock->getSocketFd();
			//cout<<sock->fromAddr()<<endl;
			FD_SET(fd,&set);
			if (fd >= nfd){
				nfd = fd+1;
			}
		}

		int rc;
		if(timeout > 0){
			struct timeval timet;
			timet.tv_sec = timeout;
			timet.tv_usec = 0;
			rc = select(nfd, &set,NULL,NULL,&timet);
		}else{
			rc = select(nfd, &set,NULL,NULL,NULL);
		}
		if (rc<1){
			FD_ZERO(&set);
			return NULL;
		}

		iter = sockets.begin();
		for(;iter!= sockets.end();iter++){
			TCPSocket* sock = *iter;
			int fd = sock->getSocketFd();
			if(FD_ISSET(fd,&set)){
				FD_ZERO(&set);
				return sock;
			}
		}
		FD_ZERO(&set);
		return NULL;
	}