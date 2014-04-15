#include "server.h"

void error(const char *msg)
{
    perror(msg);
    exit(1);
}

int main(int argc, char *argv[])
{
	if (argc < 2) 
	{
		fprintf(stderr,"ERROR, no port provided\n");
		exit(1);
	}
	 
	int sockfd, newsockfd;

	uint16_t *buff = new uint16_t[3664];

	serverSetup(argv[1], newsockfd);
	 int j = 0;
	while(1) { 
		cout << "Reading...\n";
		int n = read(newsockfd, buff, sizeof(uint16_t)*3664);
		if (n < 0) error("ERROR reading from socket");

		//bzero(buff, sizeof(uint16_t)*3664);	
		for (int i = 0; i < 3664; i++)
		{
			if (!(i % 6)) puts("");
			printf("%.4X ", buff[i]);
			j++;
		}
		cout << endl;
		bzero(buff, sizeof(uint16_t)*3664);		
		//break;
	}
	
	delete[] buff;
     
     
     //printf("Here is the message: %s\n",buffer);
     int n = write(newsockfd,"I got your message",18);
     if (n < 0) error("ERROR writing to socket");
     close(newsockfd);
     close(sockfd);
     return 0; 
}
