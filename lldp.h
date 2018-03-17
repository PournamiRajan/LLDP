/*
 * lldp.h
 *
 *  Created on: Feb 25, 2018
 *      Author: pournami
 *    Email id: pournami.puthenpurayilrajan@sjsu.edu
 */

#ifndef LLDP_H_
#define LLDP_H_

#include <sys/socket.h>
#include <stdio.h>
#include "lldp_packet.h"
#include "lldp_tx.h"
#include <iostream>
#include <thread>
#include <chrono>
#include <atomic>
#include <net/if.h>
#include <string.h>
#include <arpa/inet.h>
#include <linux/if_packet.h>
#include <linux/if_ether.h>

using namespace std;
#define NUM_PORTS 10
#define LLDP_TX_WINDOW 30

atomic<int> tx_start;
atomic<int> rx_start;

class lldp {
private:
	typedef struct txPort_ {
		int portId;
		int adminStatus;
		int portStatus;
		string ifname;
		unsigned char ifmac[6];
		int ifindex;
		int elapsedTime;
	} txPort;
	txPort *txPortDb;


public:
	lldp();
	~lldp();
	void tx_thread();
	void rx_thread();
	void txDbInit(int sock_id);
	//void rxDbInit(int sock_id)
};


#endif /* LLDP_H_ */
