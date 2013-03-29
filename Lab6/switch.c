#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>

#include <unistd.h>
#include <fcntl.h>

#include "main.h"
#include "utilities.h"
#include "link.h"
#include "man.h"
// #include "host.h"

#include "switch.h"

#define EMPTY_ADDR  0xffff  /* Indicates that the empty address */
                             /* It also indicates that the broadcast address */
#define MAXBUFFER 1000
#define PIPEWRITE 1 
#define PIPEREAD  0
#define TENMILLISEC 10000   /* 10 millisecond sleep */



void switchMain(switchState * sstate)
{	
	char buffer[1000]; /* The message from the manager */
	char word[1000];
	int  value;
	char replymsg[1000];   /* Reply message to be displayed at the manager */
	packetBuffer tmpbuff;

	int chech_host;
	int host;
	int i;

	int packet_length;
	int head = 0;
	int tail = 0;
	packetBuffer queue[1000];
	packetBuffer q_buffer;



	while(1)
	{
		/* Receive packets */
		for(host = 0; host < MAXCONNECT; host++)
		{
			linkReceive(&(sstate->linkin[host],&tmpbuff);
			if(tmpbuff.valid)
			{
				sstate->recvID = sstate->linkin[host].uniPipeInfo.physIdSrc;
				// update_table(sstate, &tmpbuff, host);
				// insertFIFO(&queue, &tmpbuff, sizeof(packetBuffer), &head, &tail, 1000);
				// break;
			}
		}

		// transmit first packet of queue
		if(head != tail)
		{
			// removeFIFO(&queue, &q_buffer, sizeof(packetBuffer), &head, &tail, 1000);
			// if(q_buffer.dstaddr <1000)
			// transmit(sstate, &q_buffer, BROADCAST);
			// else
			// {	for(host = 0; host < sstate->numConnects; host++)
			// 	{	if(sstate->table[host][1] == q_buffer.dstaddr)
			// 		{	trasmit(sstate,&q_buffer,host);
			// 			break;
			// 		}
			// 	}
			// 	if(host == sstate->numConnects) transmit(sstate, &q_buffer, BROADCAST);
			// }
		}

		// send switch to sleep just like HOST
		usleep(TENMILLISEC);
			
	}
}


void update_table(switchState * sstate, packetBuffer *pbuff, int host)
{	int i;
	for(i = 0; i < MAXCONNECT; i++)
	{
		//if(sstate->table[i][0] == sstate->physidConnect[host]
		//{	sstate->table[i][1] = pbuff->srcaddr;
		//	break;
		//}
	}

	// sstate->tableIndex++;

}




void insertQueue(void *buffer, void *item, usigned itemSize, int * head, int * tail, int bufferSize)
{	}

void removeQueue(void *buffer, void *item, unsigned itemSize, int * head, int * tail, int bufferSize)
{	}

// ----------------------------------------------------- //



void switchTransmitPacket(hostState * hstate, char word[], char replymsg[])
{

char dest[1000];
int  dstaddr;

/* Get the destination address from the manager's command message (word[]) */ 
// Get the destination address from ROUTING TABLE instead
findWord(dest, word, 2);
dstaddr = ascii2Int(dest);

/* Set up the send packet buffer's source and destination addresses */
hstate->sendPacketBuff.dstaddr = dstaddr;
hstate->sendPacketBuff.srcaddr = hstate->netaddr;

/* Transmit the packet on the link */
linkSend(&(hstate->linkout), &(hstate->sendPacketBuff));

/* Message to be sent back to the manager */
strcpy(replymsg,"Packet sent");
}






// ----------------------------------------------------- //

void switchSetNetAddr(switchState * sstate, int netaddr, char replymsg[])
{	sstate->netaddr = netaddr;	}



// ----------------------------------------------------- //

void switchInit(switchState * sstate, int physid)
{

// Initialize the receive and send packet buffers
switchInitRcvPacketBuff(&(sstate->rcvPacketBuff));  
switchInitSendPacketBuff(&(sstate->rcvPacketBuff)); 
}



// ------------- Initialize Packet Buffs ----------------- //

void switchInitSendPacketBuff(packetBuffer * packetbuff)
{
	packetbuff->valid = 0;
	packetbuff->new = 0;
}

void switchInitRcvPacketBuff(packetBuffer * packetbuff)
{
	packetbuff->valid = 0;
	packetbuff->new = 0;
}


// ----------------------------------------------------- //
// probably won't need this nor dl
void switchUploadPacket(switchState * sstate, char fname[], char replymsg[]) 
{
	char c;
	FILE * fp;
	char path[MAXBUFFER];  /* Path to the file */
	char tempbuff[MAXBUFFER]; /* A temporary buffer */
	int length;
	int i;

	// Upload the file into tempbuff 
	
	if (hstate->maindirvalid == 0) {
	   strcpy(replymsg, "Upload aborted:  the host's main directory is not yet chosen");
	return;
	}

	/* Create a path to the file and then open it */
	strcpy(path,"");
	strcat(path, hstate->maindir);
	strcat(path, "/");
	strcat(path, fname);

	fp = fopen(path,"rb"); 
	if (fp == NULL) { /* file didn't open */
	   strcpy(replymsg, "Upload aborted: the file didn't open");
	   return;
	}
	
	length = fread(tempbuff, 1, PAYLOAD_LENGTH+1, fp);
	
	if (length==0) {
	   strcpy(replymsg, "Upload aborted: error in reading the file");
	   return;
	}
	else if (length > PAYLOAD_LENGTH) {
	   strcpy(replymsg, "Upload aborted: file is too big");
	   return;
	}
	
	tempbuff[length] = '\0';
	
	/* Fill in send packet buffer */
	
	hstate->sendPacketBuff.valid=1;
	hstate->sendPacketBuff.length=length;
	
	for (i=0; i<length; i++) { /* Store tempbuff in payload of packet buffer */
	   hstate->sendPacketBuff.payload[i] = tempbuff[i];
	}
	
	/* Message to the manager */
	strcpy(replymsg, "Upload successful");
	
	fclose(fp);
}


void switchDownloadPacket(switchState * sstate, char fname[], char replymsg[]) 
{
char c;
FILE * fp;
char path[MAXBUFFER];  /* Path to the file */

/* Create a path to the file and then open it */

if (hstate->rcvPacketBuff.valid == 0) {
   strcpy(replymsg, "Download aborted: the receive packet buffer is empty");
   return;
}

if (hstate->maindirvalid == 0) {
   strcpy(replymsg, "Download aborted: the host's main directory is not yet chosen");
   return;
}

strcpy(path,"");
strcat(path, hstate->maindir);
strcat(path, "/");
strcat(path, fname);
printf("host:  path to the file: %s\n",path);
fp = fopen(path,"wb"); 

/* Download the packet buffer payload into the file */
if (hstate->rcvPacketBuff.new == 1) {
   fwrite(hstate->rcvPacketBuff.payload,1,hstate->rcvPacketBuff.length,fp);
   hstate->rcvPacketBuff.new=0;
}

/* Message sent to the manager */
strcpy(replymsg, "Download successful");
fclose(fp);
} 



// ----------------------------------------------------- //
// probably won't need
void switchClearRcvFlg(switchState * sstate, char replymsg[])
{
hstate->rcvflag = 0;
hstate->rcvPacketBuff.valid = 0;
hstate->rcvPacketBuff.new = 0;

/* Message to the manager */
strcpy(replymsg, "Host's packet received flag is cleared");
}




// ----------------------------------------------------- //
void switchSetMainDir(switchState * sstate, char dirname[], char replymsg[])
{
strcpy(hstate->maindir, dirname);
hstate->maindirvalid = 1;

/* Message to the manager */
strcpy(replymsg, "Host's main directory name is changed");
}




// ----------------------------------------------------- //



void switchGetHostState(switchState * sstate, managerLink * manLink, char replymsg[])
{
char word[1000];
char empty[7] = "Empty";

/* Create reply message */

replymsg[0] = '\0';  /* Clear reply message */

int2Ascii(word, hstate->physid);
appendWithSpace(replymsg, word);

if (hstate->maindirvalid==0) appendWithSpace(replymsg, empty);
else appendWithSpace(replymsg, hstate->maindir);

if (hstate->netaddr == EMPTY_ADDR) appendWithSpace(replymsg, empty);
else {
   int2Ascii(word, hstate->netaddr);
   appendWithSpace(replymsg, word);
}

if (hstate->nbraddr == EMPTY_ADDR) appendWithSpace(replymsg, empty);
else {
   int2Ascii(word, hstate->nbraddr);
   appendWithSpace(replymsg, word);
}

int2Ascii(word, hstate->rcvPacketBuff.new);
appendWithSpace(replymsg, word);

}

// ----------------------------------------------------- //

void switchInitState(switchState * sstate, int physid)
{
hstate->physid = physid;
hstate->maindirvalid = 0; /* main directory name is empty*/
hstate->netaddr = physid; /* default address */  
hstate->nbraddr = EMPTY_ADDR;  
hstate->rcvPacketBuff.valid = 0;
hstate->rcvPacketBuff.new = 0;
}


