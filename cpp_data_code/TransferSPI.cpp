#include "TransferSPI.h"

//static const char *device = "/dev/spidev1.0";
//static uint8_t mode;
//uint8_t bits = 16;
//uint32_t speed = 2*500000;
//static uint16_t delay;
//unsigned int inputGPIO = 26;  //P8_14

//const char *device = "/dev/spidev1.0";
//unsigned int inputGPIO = 26;

void transfer(uint16_t* data, int sockfd, char a)
{	
	int n;
	int j = 0;
	while (j < 5)
	{
		n = write(sockfd, data, sizeof(uint16_t)*32);
		j++;
	}
}

void transfer(int sockfd)
{
	unsigned int value, counter;//, i;
  FILE *file;
  //char name[60];

	uint8_t bits = 16;
	uint32_t speed = 2*500000;
	unsigned int inputGPIO = 26;
	const char *device = "/dev/spidev1.0";

	int fd = open(device, O_RDWR);
  
  gpioExport(inputGPIO);
  gpioSetDirection(inputGPIO, INPUT);
  
  uint16_t tx[] = { 0x1010, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, };
  uint16_t rx[ARRAY_SIZE(tx)] = {0, };
  struct spi_ioc_transfer tr;
  tr.tx_buf = (unsigned long)tx,
  tr.rx_buf = (unsigned long)rx,
  tr.len = 2,
  //tr.delay_usecs = delay,
  tr.speed_hz = speed,
  tr.bits_per_word = bits;
  
  while (1)
  {
    //DataQueue *data = new DataQueue();
    //snprintf(name, sizeof(name), "%d.dat", i);
    //fopen(file, name, "w");
	uint16_t *buff = new uint16_t[3664];
    counter = 0;
    //i = 0;
    while(counter < 3664)
    {
      file = fopen("data6.txt", "a+");		
      
      
		
      do
      {
				gpioGetValue(inputGPIO, &value);
      } while (value != HIGH); 
      
      int ret = ioctl(fd, SPI_IOC_MESSAGE(1), &tr);
      if (ret < 1)
			pabort("can't send spi message");
      
      //printf("%.4X\n", rx[0]);
      fprintf(file, "%i\n", rx[0]);
      //fprintf(file, "%.4X\n", rx[0]);

      //data->push(rx[0]);
		buff[counter++] = rx[0];
      
      fclose(file);
		//counter++;		
    }
   
   	//i++;
	//for (int i = 0; i < 3664; i++)
	//{
	//	if (!(i % 6)) puts("");
	//	printf("%.4X ", buff[i]);
	//}
	
	/*for (int i = 0; i < 3664; i++)
		{
			if (!(i % 6)) puts("");
			printf("%i ", buff[i]);
		}
		cout << endl;*/


	int n;
	cout << "Writing...\n";
	n = write(sockfd, buff, sizeof(uint16_t)*3664);
	if (n < 0) 
    	fprintf(stderr, "ERROR writing from socket");
    	
    	delete[] buff;
    	//fclose(file);
	//break;
  }

  for (int i = 0; i < ARRAY_SIZE(tx); i++) {
    if (!(i % 6))
      puts("");
    printf("%.4X ", rx[i]);
  }
  puts("");
	
  gpioUnexport(inputGPIO);
}

/*
void print_usage(const char *prog)
{
	printf("Usage: %s [-DsbdlHOLC3]\n", prog);
	puts("  -D --device   device to use (default /dev/spidev1.1)\n"
	     "  -s --speed    max speed (Hz)\n"
	     "  -d --delay    delay (usec)\n"
	     "  -b --bpw      bits per word \n"
	     "  -l --loop     loopback\n"
	     "  -H --cpha     clock phase\n"
	     "  -O --cpol     clock polarity\n"
	     "  -L --lsb      least significant bit first\n"
	     "  -C --cs-high  chip select active high\n"
	     "  -3 --3wire    SI/SO signals shared\n");
	exit(1);
}

void parse_opts(int argc, char *argv[])
{
	while (1) {
		static const struct option lopts[] = {
			{ "device",  1, 0, 'D' },
			{ "speed",   1, 0, 's' },
			{ "delay",   1, 0, 'd' },
			{ "bpw",     1, 0, 'b' },
			{ "loop",    0, 0, 'l' },
			{ "cpha",    0, 0, 'H' },
			{ "cpol",    0, 0, 'O' },
			{ "lsb",     0, 0, 'L' },
			{ "cs-high", 0, 0, 'C' },
			{ "3wire",   0, 0, '3' },
			{ "no-cs",   0, 0, 'N' },
			{ "ready",   0, 0, 'R' },
			{ NULL, 0, 0, 0 },
		};
		int c;

		c = getopt_long(argc, argv, "D:s:d:b:lHOLC3NR", lopts, NULL);

		if (c == -1)
			break;

		switch (c) {
		case 'D':
			device = optarg;
			break;
		case 's':
			speed = atoi(optarg);
			break;
		case 'd':
			delay = atoi(optarg);
			break;
		case 'b':
			bits = atoi(optarg);
			break;
		case 'l':
			mode |= SPI_LOOP;
			break;
		case 'H':
			mode |= SPI_CPHA;
			break;
		case 'O':
			mode |= SPI_CPOL;
			break;
		case 'L':
			mode |= SPI_LSB_FIRST;
			break;
		case 'C':
			mode |= SPI_CS_HIGH;
			break;
		case '3':
			mode |= SPI_3WIRE;
			break;
		case 'N':
			mode |= SPI_NO_CS;
			break;
		case 'R':
			mode |= SPI_READY;
			break;
		default:
			print_usage(argv[0]);
			break;
		}
	}
}
*/
