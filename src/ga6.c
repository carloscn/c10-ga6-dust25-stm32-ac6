/*
 * ga6.c
 *
 *  Created on: 2019Äê4ÔÂ2ÈÕ
 *      Author: lifim
 */

#include "ga6.h"



const unsigned char *at_attach_network = "AT+CGATT=1\r\n\0";		// AT+CGATT=1
const unsigned char *at_set_pdp_para = "AT+CGDCONT=1,\"IP\",\"CMNET\"\r\n\0";		//AT+CGDCONT=1,"IP","CMNET"
const unsigned char *at_active_network = "AT+CGACT=1,1\r\n\0";						// AT+CGACT=1,1
const unsigned char *at_link_tcp =  "AT+CIPSTART=\"TCP\",\"47.103.2.174\",8001\r\n\0"; //AT+CIPSTART="TCP","47.103.2.174",8001

const unsigned char *at_send_state = "AT+CIPSEND\r\n\0";		//AT+CIPSEND
const unsigned char *at_socket_break = "AT+CIPCLOSE\r\n\0";

static void _send_msg(UART* uart, unsigned char *s, int len)
{
    uart->write_string(uart, s, len);
    DELAY_MS(8000);
}

void ga6_socket_msg(GA6* self, unsigned char *s, int len)
{
	int i;

    self->hw.uart->write_string(self->hw.uart, s, len);
    self->hw.uart->write_byte(self->hw.uart, 0x1A);
	for (i = 0; i < 1; i ++)
		DELAY_MS(1000);
	self->hw.uart->write_string(self->hw.uart, at_send_state, len);
}

void ga6_init(GA6* self)
{
    _send_msg(self->hw.uart, at_attach_network, -1);
    _send_msg(self->hw.uart, at_set_pdp_para, -1);
    _send_msg(self->hw.uart, at_active_network, -1);
    _send_msg(self->hw.uart, at_link_tcp, -1);
    DELAY_MS(9000);
    DELAY_MS(9000);
    DELAY_MS(9000);
    self->hw.uart->write_string(self->hw.uart, at_send_state, -1);
}


GA6* ga6_new_dev()
{
    GA6* dev = (GA6*)malloc(sizeof(GA6));

    dev->hw.uart = uart_new_dev(UART_ID_1, 9600);
    dev->init = &ga6_init;
    dev->socket_send = &ga6_socket_msg; //47.103.2.174
    dev->server_info.ip[0] = 47;
    dev->server_info.ip[1] = 103;
    dev->server_info.ip[2] = 2;
    dev->server_info.ip[3] = 174;
    dev->server_info.port = 8001;

    return dev;
}


