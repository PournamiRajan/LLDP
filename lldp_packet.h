/*
 * lldp_packet.h
 *
 *  Created on: Feb 25, 2018
 *      Author: pournami
 *    Email id: pournami.puthenpurayilrajan@sjsu.edu
 */

#include <string.h>
#include <iostream>
#ifndef PACKET_H_
#define PACKET_H_
#define CHASSIS_ID 10
#define PORT_ID 1
#define TTL 30
using namespace std;
class packet {
private:

	enum lldp_tlv_type{
		lldp_tlv_type_eof,
		lldp_tlv_type_chassis_id,
		lldp_tlv_type_port_id,
		lldp_tlv_type_ttl
	};
	struct eth_header
	{
		unsigned char mac_da[6];
		unsigned char mac_sa[6];
		char eth_type[2];
	};

	struct chassis_tlv
	{
		short type:7 ;
		short length:9;
		int chassis_id;
	};
	struct port_tlv
	{
		short type:7 ;
		short length:9;
		int port_id;
	};
	struct ttl_tlv
	{
		short type:7 ;
		short length:9;
		int ttl_id;
	};
	struct lldp_mand
	{
		struct chassis_tlv chassis;
		struct port_tlv port;
		struct ttl_tlv ttl;

	};




public:
	packet();
	struct lldp_packet
		{
			struct eth_header header;
			struct lldp_mand mand;
		}pkt;
	void create_packet(unsigned char macda[6], unsigned char macsa[6]);
	void set_mac_sa(char *macsa);
	virtual ~packet();

};

#endif /* PACKET_H_ */
