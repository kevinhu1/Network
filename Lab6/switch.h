/*
 * switch.h
 */

#define NAME_LENGTH 100
#define MAXCONNECT 3	// number of links for a switch
#define SWITCHDATA 4
#define BROADCAST 1010 

typedef struct {  /* state of switch */
	char switchid;
	int numConnects;	// number of hosts connected to switch
	int table[MAXCONT][SWITCHDATA];	// switch routing table
	int tableIndex;			// next index to use for table

	packetBuffer sendPacketBuff;
	packetBuffer rcvPacketBuff;

	int physidConnect[MAXCONNECT];	// physical IDs of connected nodes

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
void switchInitRcvPacketBuff(packetBuffer * packetbuff);
// initialize a new packet to zero




void switchUploadPacket(switchState * sstate, char fname[], char replymsg[]);
// upload file into tempbuff; do not need to upload






// do not need to download packets
void switchDownloadPacket(switchState * sstate, char fname[], char replymsg[]);



//probably won't need flag
void switchClearRcvFlg(switchState * sstate, char replymsg[])
// clears receive flag




// do not need to set main directory for switches
void switchSetMainDir(switchState * sstate, char dirname[], char replymsg[]);
// sets main directory name




// involves using manager, probably no need
// void switchGetHostState(switchState * sstate, managerLink * manLink, char replymsg[]);


void switchInitState(switchState * sstate, int physid);
