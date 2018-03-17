/*
 * lldp_tx.h
 *
 *  Created on: Feb 25, 2018
 *      Author: pournami
 *    Email id: pournami.puthenpurayilrajan@sjsu.edu
 */
#include <sys/socket.h>
#include <sys/ioctl.h>
#include <net/if.h>
#include <string.h>
#include <arpa/inet.h>
#include <linux/if_packet.h>
#include <linux/if_ether.h>
#include <unistd.h>
#include "lldp_packet.h"
#include <iostream>
#include <errno.h>
using namespace std;


#ifndef TXSOCKET_H_
#define TXSOCKET_H_

class tx_socket {
private:
	int sock_id = 0;
	struct sockaddr_ll sock_addr;

public:
	tx_socket();
	int create_socket();
	void send_packet(packet pckt, int ifindex);
	void close_socket();

	virtual ~tx_socket();
};

#endif /* TXSOCKET_H_ */
