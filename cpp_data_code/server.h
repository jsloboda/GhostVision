#ifndef _SERVER_H_
#define _SERVER_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h> 
#include <sys/socket.h>
#include <netinet/in.h>

#include <iostream>
//#include "DataQueue.h"
using namespace std;

void serverSetup(char* port_num, int &newsockfd);

#endif


