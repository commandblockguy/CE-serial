#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <tice.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

uint24_t receive(void* buf);

char buffer[512];
uint24_t bufferStart = 0, bufferLen = 0;

uint24_t srl_Read(void* out, uint24_t size) {
	uint24_t transferred;
	char str[24];
	os_PutStrFull("srl_Read");
	os_NewLine();
	if(size <= bufferLen) {
		os_PutStrFull("lte buflen");
		os_NewLine();
		memcpy(out, &buffer[bufferStart], size);
		bufferStart += size;
		bufferLen -= size;
		return size;
	}
	else {
		os_PutStrFull("gt buflen");
		os_NewLine();
		memcpy(out, &buffer[bufferStart], bufferLen);
		transferred = bufferLen;
		bufferLen = 0;
		bufferStart = 0;
		bufferLen = receive(buffer);
		if(!bufferLen)
			return transferred;
		return transferred + srl_Read(out + transferred, size - transferred);
	}
}

bool srl_Available() {
	os_PutStrFull("srl_Avail");
	os_NewLine();
	if(bufferLen) return true;
	os_PutStrFull("empty buf");
	os_NewLine();
	bufferStart = 0;
	bufferLen = receive(buffer);
	return bufferLen > 0;
}

void srl_Await() {
	os_PutStrFull("srl_Await");
	os_NewLine();
	while(!srl_Available());
}

char srl_ReadByte() {
	int val;
	os_PutStrFull("srl_ReadByte");
	os_NewLine();
	srl_Await();
	srl_Read(&val, 1);
	return val;
}
