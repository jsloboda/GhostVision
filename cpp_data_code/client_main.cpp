#include "client.h"
#include "TransferSPI.h"
//#include "GPIO.h"

int main(int argc, char * argv[])
{
	int sockfd;
 
	int r = clientSetup(argv[2], argv[1], sockfd);
  	if (r < 0)
  	{
  		fprintf(stderr, "Client setup failed\n");
    	exit(0);
  	}

	
	transfer(sockfd);
  
  //n = write(sockfd, buff, sizeof(uint16_t)*32);

	/*
  if (n < 0) 
    fprintf(stderr, "ERROR writing to socket");
  
  bzero(buffer,256);
  
  n = read(sockfd,buffer,255);
  
  if (n < 0) 
    fprintf(stderr, "ERROR reading from socket");
  */
  close(sockfd);
    
  return 0;
}
