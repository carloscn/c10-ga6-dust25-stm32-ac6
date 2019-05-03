/*
 * ga6.h
 *
 *  Created on: 2019Äê4ÔÂ2ÈÕ
 *      Author: lifim
 */


#include "uart.h"
#include "delay.h"

typedef struct ga6_t GA6;

struct ga6_hw_t {
    UART* uart;
};

struct ga6_t {

    struct ga6_hw_t hw;
    GA6 *self;
    struct config_t {
        unsigned char ip[4];
        uint16_t port;
    } server_info;
    void (*init)(GA6* self);
    void (*socket_send)(GA6* self, unsigned char *s, int len);

};

extern GA6* ga6_new_dev();
