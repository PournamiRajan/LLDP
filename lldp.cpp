#include "lldp.h"

lldp::lldp() :txPortDb(NULL)
{
	thread tx(&lldp::tx_thread, this);
	thread rx(&lldp::rx_thread, this);

	cout << "I am main" << endl;
	/* on every second initiate tx and rx processing */
	while (1) {
		/* on every second set trigger */
		std::this_thread::sleep_for(std::chrono::seconds(1));
		tx_start = 1;
		rx_start = 1;
	}
	tx.join();
	rx.join();
}

lldp::~lldp()
{

}

void lldp::txDbInit(int sock_id)
{
	int ret;
	struct ifreq if_in, if_mac;
	txPortDb = new txPort[NUM_PORTS];
	memset(txPortDb, 0, sizeof(NUM_PORTS * sizeof(txPort)));

	/* fetch data from hw */
	memset(&if_in, 0, sizeof(struct ifreq));
	strncpy(if_in.ifr_name, "eth0",sizeof(if_in.ifr_name));
	txPortDb[0].ifname = "eth0";
	ret = ioctl(sock_id, SIOCGIFINDEX, &if_in);
	if (ret < 0) {
		cout << __FUNCTION__ <<  "errno: " << errno << endl;
		perror("socket");
	}
	memset(&if_mac, 0, sizeof(struct ifreq));
	strncpy(if_mac.ifr_name, "eth0",sizeof(if_mac.ifr_name));
	memcpy(txPortDb[0].ifmac, if_mac.ifr_hwaddr.sa_data, sizeof (txPortDb[0].ifmac));
	ret = ioctl(sock_id, SIOCGIFHWADDR, &if_mac);
	if (ret < 0) {
		cout << __FUNCTION__ <<  "errno: " << errno << endl;
		perror("socket");
	}
	txPortDb[0].ifindex = if_in.ifr_ifindex;
	txPortDb[0].portStatus = 1;
	txPortDb[0].adminStatus = 1;
	txPortDb[0].elapsedTime = 0;
}

void lldp::tx_thread()
{
	cout << "I am tx thread" <<endl;
	tx_socket tx_sock;
	int sock_id = tx_sock.create_socket();
	cout<<__FUNCTION__ << " created socket" << endl;
	txDbInit(sock_id);

	while (1) {
		if (tx_start) {
			tx_start = 0;
			for (int i = 0; i < NUM_PORTS; i++) {
				if (!txPortDb[i].portStatus)
					continue;

				txPortDb[i].elapsedTime++;
				if (txPortDb[i].elapsedTime != LLDP_TX_WINDOW)
					continue;

				txPortDb[i].elapsedTime = 0;
				packet pckt;
				unsigned char macda[6]={0x01, 0x80, 0xC2, 0x00, 0x00, 0x0E};
				unsigned char macsa[6]={0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
				pckt.create_packet(macda, txPortDb[i].ifmac);
				cout<<__FUNCTION__ << " created packet" << endl;
				tx_sock.send_packet(pckt, txPortDb[i].ifindex);
				cout<<__FUNCTION__ << " sent packet" << endl;
			}
		}
	}
}

void lldp::rx_thread ()
{
	cout << "I am rx thread" <<endl;

	/* create rxdb and txdb */
	//rxDbInit();

}

int main()
{
	lldp l = lldp();
	while(1);
	return 0;
}


