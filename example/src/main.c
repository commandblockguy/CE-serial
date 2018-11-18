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

void testRead(void* buf, uint24_t size);

char *data = "abcd";

void main(void) {
	lineCoding_t lc = {9600, 0, 0, 8};
	char byte = 0;
	char str[10];
	char abuf[64];
	int size;
	int i;

	os_ClrHome();
	usb_PrePower(3000);
	if(!srl_InitDevice()) goto err;
	os_PutStrFull("device inited");
	os_NewLine();
	srl_ConfigSerial(&lc);
	srl_SetControlLineState(3);
	os_PutStrFull("config set");
	os_NewLine();
	do {
		kb_Scan();
		if(kb_Data[1] & kb_2nd) {
			int size = 7;
			testRead(abuf, size);
			//sprintf(str, "%i: ", recd);
			//os_PutStrFull(str);
			//for(i = 0; i < size; i++) {
			//	sprintf(str, "%2X", abuf[i]);
			//	os_PutStrFull(str);
			//}
			//os_NewLine();
			delay(100);
		}
		if(kb_Data[1] & kb_Yequ) {
			srl_Write(data, 4);
			os_PutStrFull("data written");
			os_NewLine();
			delay(100);
		}

	} while(!(kb_Data[6] & kb_Clear));
	err:
	os_PutStrFull("cleaning up");
	usb_Cleanup();
	//while(!os_GetCSC());
}
