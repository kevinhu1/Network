
#ifndef SWITCH_H
#define SWITCH_H

#include <string.h>
#include <stdlib.h>
#include <netdb.h>
#include <unistd.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <fcntl.h>
#include <stdio.h>

#include "main.h"
#include "link.h"

#define TENMILLISEC 10000
#define BROADCAST 1010
#define SWITDATA 4

/* MOVE to SWITCH */
/*==========================================================================*/
typedef struct {
	char switchid;					/* identification of switch */
	int numConnects;				/* number of host connected to switch */
	int table[MAXCONT][SWITDATA];	/* switch routing table */
	int tableIndex;					/* next index to use for the table */
	packetBuffer sendPacketBuff;	/* send packet buffer */
	packetBuffer rcvPacketBuff;		/* receive packet buffer */
	int physidConnect[MAXCONT];		/* Physical IDs of the connected nodes */
	LinkInfo linkin[MAXCONT];		/* Incoming communication link */
	LinkInfo linkout[MAXCONT];		/* Outgoing communication link */
	int RecvID;						/* Physical ID of Incoming Packet */
} switState;

/* - Table[i][0] =>  Network Address
 * - Table[i][1] =>  Physical ID
 */

/* - switchInit which initializes the host.
 * - hostInitRcvPacketBuff, which initializes the receive packet buffer
 * - hostInitSendPacketBuff, which initializes the send packet buffer
 */
void switchInit(switState * switstate); 
void swtichInitRcvPacketBuff(packetBuffer * packetbuff);
void swtichInitSendPacketBuff(packetBuffer * packetbuff);
void switchMain(switState * switstate); 
/*==========================================================================*/


void SwitchMain(switState * swit);
void update_table(switState * swit, packetBuffer * pbuff, int check_host);
void insertFIFO(void *buffer, void *item, unsigned itemSize, int * head, int * tail, int bufferSize);
void removeFIFO(void *buffer, void *item, unsigned itemSize, int * head, int * tail, int bufferSize);
void transmit(switState * swit, packetBuffer * q_buffer, int sendval);

#endif






