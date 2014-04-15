#include "server.h"

void serverSetup(char* port_num, int &newsockfd)
{
	  int sockfd, portno;
     socklen_t clilen;
     //char buffer[256];
     //uint16_t buf[2];

     //uint16_t *buff = new uint16_t[3664];

     //DataQueue data;// = new DataQueue();
     
     struct sockaddr_in serv_addr, cli_addr;
     int n;
     
     sockfd = socket(AF_INET, SOCK_STREAM, 0);
     if (sockfd < 0) 
        printf("ERROR opening socket");
     bzero((char *) &serv_addr, sizeof(serv_addr));
     portno = atoi(port_num);//atoi(argv[1]);
     serv_addr.sin_family = AF_INET;
     serv_addr.sin_addr.s_addr = INADDR_ANY;
     serv_addr.sin_port = htons(portno);
     if (bind(sockfd, (struct sockaddr *) &serv_addr,
              sizeof(serv_addr)) < 0) 
              printf("ERROR on binding");
     listen(sockfd,5);
     clilen = sizeof(cli_addr);
     newsockfd = accept(sockfd, 
                 (struct sockaddr *) &cli_addr, 
                 &clilen);
     if (newsockfd < 0) 
          printf("ERROR on accept");

}

