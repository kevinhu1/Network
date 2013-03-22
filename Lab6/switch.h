/*
 * switch.h
 */

#define NAME_LENGTH 100
#define MAXCONNECT 3	// number of links for a switch

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
//	routingTable rt[MAXCONNECT];
          int nbraddr[MAXCONNECT];
	  LinkInfo linkin[MAXCONNECT];
	  LinkInfo linkout[MAXCONNECT];

	int recvID;		// physical ID of incoming packet
} switchState;

void switchMain(switchState * sstate);
// do EVERYTHING

// check if there is an incoming packet
// determine buffer length
// store in queue / receive packet buffer
// check routing table, add in if does not exist
// send out appropriate data determined from routing table


// ----------------------------------------------------- //
// our very own functions!

void update_table(switchState * sstate, packetBuffer *pbuff, int host);
void insertQueue(void *buffer, void *item, usigned itemSize, int * head, int * tail, int bufferSize);
void removeQueue(void *buffer, void *item, unsigned itemSize, int * head, int * tail, int bufferSize);



// ----------------------------------------------------- //

void switchTransmitPacket(hostState * hstate, char word[], char replymsg[]);
// get destination address from routing table
// set up send packet buffer's source and dest addr
// transmit packet on link




void switchSetNetAddr(switchState * sstate, int netaddr, char replymsg[]);
// simply sets netwerk address






void switchInit(switchState * sstate, int physid);
// initialize state
// Initialize recv/send packet buffers





void switchInitSendPacketBuff(packetBuffer * packetbuff);
// initialize a new packet buffer to zero




void switchUploadPacket(switchState * sstate, char fname[], char replymsg[]);
// upload file into tempbuff






void switchInitRcvPacketBuff(packetBuffer * packetbuff);
// initialize a new receive packet to zero





void switchDownloadPacket(switchState * sstate, char fname[], char replymsg[]);



//probably won't need
void switchClearRcvFlg(switchState * sstate, char replymsg[])
// clears receive flag LOL





void switchSetMainDir(switchState * sstate, char dirname[], char replymsg[]);
// sets main directory name





void switchGetHostState(switchState * sstate, managerLink * manLink, char replymsg[]);


void switchInitState(switchState * sstate, int physid);
