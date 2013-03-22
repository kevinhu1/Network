#include "switch.h"

void switchInit(switchState * sstate, int physid)
{

	switchInitState(sstate, physid);     /* Initialize host's state */

	/* Initialize the receive and send packet buffers */
	switchInitRcvPacketBuff(&(sstate->rcvPacketBuff));  
	switchInitSendPacketBuff(&(sstate->rcvPacketBuff)); 
}

void switchMain(switchState * sstate)
{
char word[1000];
int  value;
packetBuffer tmpbuff;

while(1) {

   /* Check if there is a command message from the manager */
   int length; /* Size of string in pipe */
   length = hostCommandReceive(&(sstate->manLink),buffer);

   if (length > 1) { /* Execute the manager's command */
      findWord(word, buffer, 1);
      if (strcmp(word, "SetNetAddr")==0) {
         findWord(word, buffer, 2); /* Find net address */
         hostSetNetAddr(hstate, value, replymsg);
         hostReplySend(&(hstate->manLink),"DISPLAY",replymsg);
      }
      else if (strcmp(word, "SetMainDir")==0) {
         findWord(word, buffer, 2); /* Find directory name */
         hostSetMainDir(hstate, word, replymsg);
         hostReplySend(&(hstate->manLink),"DISPLAY",replymsg);
      }
      else if (strcmp(word, "ClearRcvFlg")==0) {
         hostClearRcvFlg(hstate, replymsg);
         hostReplySend(&(hstate->manLink),"DISPLAY",replymsg);
      }
      else if (strcmp(word, "UploadPacket")==0) {
         findWord(word, buffer, 2); /* Find file name */
         hostUploadPacket(hstate, word, replymsg); 
         hostReplySend(&(hstate->manLink), "DISPLAY",replymsg);
      }
      else if (strcmp(word, "DownloadPacket")==0) {
         findWord(word, buffer, 2); /* Find file name */
         hostDownloadPacket(hstate, word, replymsg);
         hostReplySend(&(hstate->manLink), "DISPLAY",replymsg);
      }
      else if (strcmp(word, "GetHostState")==0) {
         hostGetHostState(hstate, &(hstate->manLink), replymsg);
         hostReplySend(&(hstate->manLink), "GetHostStateAck",replymsg);
      }
      else if (strcmp(word, "TransmitPacket")==0) {
         hostTransmitPacket(hstate, buffer, replymsg);
         hostReplySend(&(hstate->manLink), "DISPLAY", replymsg);
      }
   } /* end of if */

   /* Check if there is an incoming packet */
   linkReceive(&(hstate->linkin), &tmpbuff);

   /* 
    * If there is a packet and if the packet's destination address 
    * is the host's network address then store the packet in the
    * receive packet buffer
    */
   if (tmpbuff.dstaddr == hstate->netaddr && tmpbuff.valid == 1 && tmpbuff.new == 1) {
      hstate->rcvPacketBuff = tmpbuff;
      hstate->rcvPacketBuff.new = 1;
      hstate->rcvPacketBuff.valid = 1;
   }

   /* The host goes to sleep for 10 ms */
   usleep(TENMILLISEC);

} /* End of while loop */

}

int switchPacketReceive(switchState * sstate, char command[])
{
	return 0;
}
