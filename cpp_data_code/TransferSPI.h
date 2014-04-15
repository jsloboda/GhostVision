#ifndef _TRANSFERSPI_H_
#define _TRANSFERSPI_H_

#include <stdint.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#include <linux/types.h>
#include <linux/spi/spidev.h>

#include "GPIO.h"
//#include "DataQueue.h"
#include <iostream>
using namespace std;

#define ARRAY_SIZE(a) (sizeof(a) / sizeof((a)[0]))

//extern const char *device;// = "/dev/spidev1.0";
//extern uint8_t mode;
//extern uint8_t bits; //= 16;
//extern uint32_t speed;// = 2*500000;
//extern uint16_t delay;
//extern unsigned int inputGPIO;// = 26;  //P8_14

static void pabort(const char *s)
{
  perror(s);
  abort(); 
}

void transfer(uint16_t*, int, char);
void transfer(int);
//void print_usage(const char *prog);
//void parse_opts(int argc, char *argv[]);

#endif /*_TRANSFERSPI_H_*/
