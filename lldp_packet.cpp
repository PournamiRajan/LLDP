/*
 * packet.cpp
 *
 *  Created on: Feb 25, 2018
 *      Author: pournami
 */

#include "lldp_packet.h"

packet::packet() {

}

void packet::create_packet(unsigned char macda[6], unsigned char macsa[6])
{
	memset(&pkt, 0, sizeof(pkt));
	memcpy(pkt.header.mac_da, macda, 6);
	memcpy(pkt.header.mac_sa, macsa, 6);
	pkt.header.eth_type[0]=0x88;
	pkt.header.eth_type[1]=0xcc;
	cout<<"struct ether size = "<<sizeof(eth_header)<<endl;
	cout<<"size of short int "<<sizeof(short)<<endl;
	pkt.mand.chassis.type = lldp_tlv_type_chassis_id;
	pkt.mand.chassis.length = 4;
	pkt.mand.chassis.chassis_id = CHASSIS_ID;
	cout<<"struct chassis size = "<<sizeof(chassis_tlv)<<endl;

	pkt.mand.port.type = lldp_tlv_type_port_id;
	pkt.mand.port.length = 4;
	pkt.mand.port.port_id = PORT_ID;
	cout<<"struct port size = "<<sizeof(port_tlv)<<endl;

	pkt.mand.ttl.type = lldp_tlv_type_ttl;
	pkt.mand.ttl.length = 2;
	pkt.mand.ttl.ttl_id = TTL;
	cout<<"struct ttl size = "<<sizeof(ttl_tlv)<<endl;


}

void packet::set_mac_sa(char* macsa)
{
	memcpy(pkt.header.mac_sa, macsa, 6);
}


packet::~packet() {

}

