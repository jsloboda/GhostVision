#ifndef _CLIENT_H_
#define _CLIENT_H_

#include <stdio.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>

//#include "DataQueue.h"
#include <iostream>
using namespace std;

int clientSetup(char*, char*, int&);

#endif /*_CLIENT_H_*/
