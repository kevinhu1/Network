/* Switch Node Functions */

#include "switch.h"

//#define DEBUG_RCV
//#define DEBUG_SEN


/* Main Switch Funcrion */
void SwitchMain(switState * swit)
{
	int check_host, host, j;
	int packet_length;
	int head = 0;
	int tail = 0;
	packetBuffer pbuff;
	packetBuffer queue[1000];
	packetBuffer q_buffer;
	
	/* Switch Node Forever Loop */
	while(1)
	{		
		/* Receive packets */
		for(host = 0; host < swit->numConnects; host++)
		{
			linkReceive(&(swit->linkin[host]), &pbuff);
			
			if(pbuff.valid)
			{	
				#ifdef DEBUG_RCV
				printf("Link %d received\n",swit->linkin[host].linkID);
				printf("PipeSRC %d\n",swit->linkin[host].uniPipeInfo.physIdSrc);
				printf("PipeDST %d\n",swit->linkin[host].uniPipeInfo.physIdDst);
				printf("Received: %s\n", pbuff.payload);
				#endif
				swit->RecvID = swit->linkin[host].uniPipeInfo.physIdSrc;
				update_table(swit, &pbuff, host);
				insertFIFO(&queue, &pbuff, sizeof(packetBuffer), &head, &tail, 1000);
				break;
			}
		}
		
		/* Transmit first packet of queue */
		if(head != tail)	
		{
			removeFIFO(&queue, &q_buffer, sizeof(packetBuffer), &head, &tail, 1000);
			if(q_buffer.dstaddr < 1000) 
				transmit(swit, &q_buffer, BROADCAST);
			else 
			{	for(host = 0; host < swit->numConnects; host++)
				{	
					if(swit->table[host][1] == q_buffer.dstaddr)
					{	transmit(swit, &q_buffer, host);
						break;
					}
				}
				if(host == swit->numConnects) transmit(swit, &q_buffer, BROADCAST);
			}
		}
		/* The switch goes to sleep for 20 ms */
		usleep(TENMILLISEC);
		usleep(TENMILLISEC);
	}
}


/* Update the routing table */
void update_table(switState * swit, packetBuffer *pbuff, int host)
{
	int i;
	for(i = 0; i < swit->numConnects; i++)
	{
		if(swit->table[i][0] == swit->physidConnect[host])
		{	swit->table[i][1] = pbuff->srcaddr;
			break;
		}
	}
	//swit->table[swit->tableIndex][0] = swit->physidConnect[host];	 
	//swit->table[swit->tableIndex][1] = pbuff->srcaddr;
	//printf("Source ID  : %d\n", swit->physidConnect[host]);
	//printf("Source Addr: %d\n", pbuff->srcaddr);
	swit->tableIndex++;
}


/* Insert a packetBuffer into the FIFO */
void insertFIFO(void *buffer, void *item, unsigned itemSize, int * head, int * tail, int bufferSize)
{
	memmove(buffer + ((*tail)*itemSize), item, itemSize);
	*tail = ((*tail)+1) % bufferSize;
	if(*tail == *head) *head = ((*head)++ % bufferSize);
}


/* Remove a packetBuffer into the FIFO */
void removeFIFO(void *buffer, void *item, unsigned itemSize, int * head, int * tail, int bufferSize)
{
	if(*head == *tail) return;
	
	memmove(item, buffer+((*head)*itemSize), itemSize);
	*head = ((*head) + 1 % bufferSize);
}



/* Transmit a packetBuffer */
void transmit(switState * swit, packetBuffer * q_buffer, int sendval)
{
	#ifdef DEBUG_SEN
	printf("Sent: %s\n", q_buffer->payload);
	#endif
	
	LinkInfo SendLink;
	int i, j;
	
	if(sendval != BROADCAST)
	{	SendLink = swit->linkout[sendval];
		linkSend(&SendLink, q_buffer);
	}
	else
	{	for(i = 0; i < swit->numConnects; i++)
		{	if(swit->physidConnect[i] != swit->RecvID)
			{	SendLink = swit->linkout[i];
			 	linkSend(&SendLink, q_buffer);
			}
		}
	}
}


/* MOVE to SWITCH */
/*==========================================================================*/

/* Initializes the host */
void switchInit(switState * switstate)
{	
	/* Initialize the receive and send packet buffers */
	hostInitRcvPacketBuff(&(switstate->rcvPacketBuff));  
	hostInitSendPacketBuff(&(switstate->rcvPacketBuff)); 
}

/* Initialize send packet buffer */
void switchInitSendPacketBuff(packetBuffer * packetbuff)
{
	packetbuff->valid = 0;
	packetbuff->new = 0;
}

/* Initialize receive packet buffer  */ 
void switchInitRcvPacketBuff(packetBuffer * packetbuff)
{
	packetbuff->valid = 0;
	packetbuff->new = 0;
}

/*==========================================================================*/


