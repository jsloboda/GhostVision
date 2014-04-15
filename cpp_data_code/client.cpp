#include "client.h"

int clientSetup(char* port_num, char* host_name, int &sockfd)
{
  
  //int sockfd;
  int portno;

  struct sockaddr_in serv_addr;
  struct hostent *server;
  
  portno = atoi(port_num);//argv[2]);

  sockfd = socket(AF_INET, SOCK_STREAM, 0);

  if (sockfd < 0)
    printf("ERROR opening socket\n");

  server = gethostbyname(host_name);//argv[1]);

  if (server == NULL)
  {                                            
    fprintf(stderr, "ERROR, no such host\n");
    exit(0);
  }

  bzero((char*) &serv_addr, sizeof(serv_addr));

  serv_addr.sin_family = AF_INET;

  bcopy((char *)server->h_addr, (char*)&serv_addr.sin_addr.s_addr,
	server->h_length);

  serv_addr.sin_port = htons(portno);

  if (connect(sockfd, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0)
    printf("ERROR connecting\n");

  return 1;

}
