#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <tice.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <keypadc.h>

#include "usbserial.h"

char data[6] = {0x00,0x11,0x22,0x33,0x44,0x55};

void main(void) {
	lineCoding_t lc = {9600, 0, 0, 8};
	char byte = 0;
	char str[10];

	os_ClrHome();
	usb_PrePower(3000);
	if(!srl_InitDevice()) goto err;
	srl_ConfigSerial(&lc);
	srl_Write(data, 6);
	byte = srl_ReadByte();
	sprintf(str, "%X", byte);
	os_PutStrFull(str);
	delay(6000);
	err:
	usb_Cleanup();
	while(!os_GetCSC());
}
