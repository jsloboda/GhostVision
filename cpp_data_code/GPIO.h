#ifndef _GPIO_H_
#define _GPIO_H_

#define GPIO_DIR "/sys/class/gpio"
#define POLL_TIMEOUT (3 * 1000) /* 3 seconds */
#define MAX_BUF 64

enum PIN_DIRECTION {INPUT, OUTPUT};
enum PIN_VALUE {LOW, HIGH};

int gpioExport(unsigned int gpio);
int gpioUnexport(unsigned int gpio);
int gpioSetDirection(unsigned int gpio, enum PIN_DIRECTION out_flag);
int gpioSetValue(unsigned int gpio, enum PIN_VALUE value);
int gpioGetValue(unsigned int gpio, unsigned int *value);
int fdOpen(unsigned int gpio);
int fdClose(int fd);

#endif /*_GPIO_H_*/
