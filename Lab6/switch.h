/*
 * switch.h
 */

#define NAME_LENGTH 100

typedef struct {  /* routing table */
	int nbraddr;
	LinkInfo linkin;
	LinkInfo linkout;
}  routingTable;

typedef struct {  /* state of switch */
	int physid;
	char maindir[NAME_LENGTH];
	int maindirvalid;
	int netaddr;
	packetBuffer sendPacketBuff;
	packetBuffer rcvPacketBuff;
	routingTable rt[3];
} switchState;

void switchMain(switchState * sstate);

void switchInit(switchState * sstate, int physid);


