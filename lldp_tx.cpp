/*
 * txsocket.cpp
 *
 *  Created on: Feb 25, 2018
 *      Author: pournami
 */

#include "lldp_tx.h"

tx_socket::tx_socket() {
	// TODO Auto-generated constructor stub

}

int tx_socket::create_socket()
{
	sock_id = socket(AF_PACKET, SOCK_RAW, htons(ETH_P_ALL));
	if (sock_id < 0) {
		cout << __FUNCTION__ <<  "errno: " << errno <<endl;
		return sock_id;
	}
	cout<< __FUNCTION__ << __LINE__<< ":sock_id=" << sock_id << endl;
	return sock_id;
}


void tx_socket::send_packet(packet pckt, int ifindex)
{
	int ret;

	memset(&sock_addr, 0, sizeof(struct sockaddr_ll));

	sock_addr.sll_ifindex = ifindex;
	sock_addr.sll_family = AF_PACKET;
	cout << __FUNCTION__ << "ifindex: " << ifindex << endl;

	cout << __FUNCTION__ << " socket id" << sock_id <<endl;

	ret = sendto(sock_id, &pckt.pkt, sizeof(pckt.pkt), 0, (struct sockaddr*)&sock_addr, sizeof(struct sockaddr_ll));
	if (ret < 0)
			cout << __FUNCTION__ <<  "errno: " << errno << endl;
	cout<< __FUNCTION__ << " :packet send ret=" << ret << endl;
}

void tx_socket:: close_socket()
{
	close(sock_id);
}

tx_socket::~tx_socket() {

}

