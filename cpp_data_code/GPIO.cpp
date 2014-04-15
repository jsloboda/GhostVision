#include "GPIO.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>
#include <fcntl.h>
#include <poll.h>
#include <iostream>

int gpioExport(unsigned int gpio)
{
  int fd, len;
  char buffer[MAX_BUF];
  
  fd = open(GPIO_DIR "/export", O_WRONLY);
  if (fd < 0) {
    perror("gpio/export");
    return fd;
  }
  
  len = snprintf(buffer, sizeof(buffer), "%d", gpio);
  write(fd, buffer, len);
  close(fd);
  
  return 0;
}

int gpioUnexport(unsigned int gpio)
{
  int fd, len;
  char buffer[MAX_BUF];
  
  fd = open(GPIO_DIR "/unexport", O_WRONLY);
  if (fd < 0) {
    perror("gpio/export");
    return fd;
  }
  
  len = snprintf(buffer, sizeof(buffer), "%d", gpio);
  write(fd, buffer, len);
  close(fd);
 
  return 0;
}

int gpioSetDirection(unsigned int gpio, enum PIN_DIRECTION flag)
{
  int fd;
  char buffer[MAX_BUF];
  
  snprintf(buffer, sizeof(buffer), GPIO_DIR  "/gpio%d/direction", gpio);
  
  fd = open(buffer, O_WRONLY);
  if (fd < 0) {
    perror("gpio/direction");
    return fd;
  }
  
  if (flag == OUTPUT)
    write(fd, "out", 4);
  else
    write(fd, "in", 3);
  
  close(fd);
  
  return 0;
}

int gpioSetValue(unsigned int gpio, enum PIN_VALUE value)
{
  int fd;
  char buffer[MAX_BUF];
  
  snprintf(buffer, sizeof(buffer), GPIO_DIR "/gpio%d/value", gpio);
  
  fd = open(buffer, O_WRONLY);
  if (fd < 0)
  {
    perror("gpio/set-value");
    return fd;
  }
  
  if (value == LOW)
    write(fd, "0", 2);
  else
    write(fd, "1", 2);
  
  close(fd);
  
  return 0;
}

int gpioGetValue(unsigned int gpio, unsigned int *value)
{
  int fd;
  char buffer[MAX_BUF];
  char ch;
  
  snprintf(buffer, sizeof(buffer), GPIO_DIR "/gpio%d/value", gpio);
  
  fd = open(buffer, O_RDONLY);
  if (fd < 0) {
    perror("gpio/get-value");
    return fd;
  }
  
  read(fd, &ch, 1);
  
  if (ch != '0') 
    *value = 1;
  else 
    *value = 0;
  
  
  close(fd);
  
  return 0;
}

int fdOpen(unsigned int gpio)
{
  int fd;
  char buffer[MAX_BUF];
  
  snprintf(buffer, sizeof(buffer), GPIO_DIR "/gpio%d/value", gpio);
  
  fd = open(buffer, O_RDONLY | O_NONBLOCK );
  if (fd < 0) {
    perror("gpio/fd_open");
  }
  
  return fd;
}

int fdClose(int fd)
{
  return close(fd);
}
