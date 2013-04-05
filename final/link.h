/* Definitions and prototypes for the link (link.c)
 */

#ifndef LINK_H
#define LINK_H

/* Number of Links = (0,2,6,12,20)=> numLinks = N*(N+1) */
//#define NUMLINKS 30 // Now set by config file
#include "netconfig.h"

enum LinkType {UNIPIPE}; /* UNIPIPE = unidirectional pipe */

enum UniPipeType {BLOCKING, NONBLOCKING};

typedef struct {
   enum UniPipeType pipeType;
   int         fd[2];
   int         physIdSrc;
   int	       physIdDst;
} UniPipeInfo;

typedef struct {			/* Has all the information to implement a link */
   int linkID;				/* ID for the link */
   enum LinkType linkType;	/* The type of link */
   UniPipeInfo uniPipeInfo; /* If the link is a pipe, this is the information */
} LinkInfo;

typedef struct {
   int numlinks;
   LinkInfo link[MAXNODE];
} linkArrayType;

/* Transmit the packet in pbuff on the link */
int linkSend(LinkInfo * link, packetBuffer * pbuff);

/* Downloads a packet from the link into pbuff */
int linkReceive(LinkInfo * link, packetBuffer * pbuff);

/* Closes a link */
int linkClear(LinkInfo * link);

/* Initializes a link */
int linkCreate(LinkInfo * link);

#endif