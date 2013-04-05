
/* Create nonblocking connections from the manager to all hosts */
void netCreateConnections(manLinkArrayType * manLinkArray); 

/* Create all nonblocking links */
void netCreateLinks(linkArrayType * linkArray);

/* 
 * Close all connections except the outgoing connection
 * from the host to manager and the incoming connection from
 * the manager to host
 */ 
void netCloseConnections(manLinkArrayType *  manLinkArray, int hostid);

/* Set up the end nodes of the links to create a network topology */
void netSetNetworkTopology(linkArrayType * linkArray, netconf *netconfig);

/* Find host's outgoing link and return its index from the link array */
int netHostOutLink(linkArrayType * linkArray, int hostid); 

/* Find host's incoming link and return its index from the link array */
int netHostInLink(linkArrayType * linkArray, int hostid); 

/* Find switche incoming/outgoing link and return its index from the link array */
int netSwitchInLink(linkArrayType * linkArray, int switchid, int skip); 
int netSwitchOutLink(linkArrayType * linkArray, int switchid, int skip); 

/* Close links not used by the host */
void netClearHostOtherLinks(linkArrayType * linkArray, int hostid);

/* Close links not connected to the switch */
void netCloseSwitchOtherLinks(linkArrayType * linkArray, switState switstate, int swtichid);

/* Close all links */
void netCloseLinks(linkArrayType * linkArray); 

/* Close the host's side of a connection between a host and manager */
void netCloseManConnections(manLinkArrayType * manLinkArray);

