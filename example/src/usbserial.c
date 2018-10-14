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
	if(size <= bufferLen) {
		memcpy(out, &buffer[bufferStart], size);
		bufferStart += size;
		bufferLen -= size;
		return size;
	}
	else {
		memcpy(out, &buffer[bufferStart], bufferLen);
		transferred = bufferLen;
		bufferLen = 0;
		bufferStart = 0;
		bufferLen = receive(buffer);
		if(!bufferLen)
			return transferred;
		return srl_Read(out + transferred, size - transferred);
	}
}

bool srl_Available() {
	if(bufferLen) return true;
	bufferStart = 0;
	bufferLen = receive(buffer);
	return bufferLen > 0;
}

void srl_Await() {
	while(!srl_Available());
}

char srl_ReadByte() {
	int val;
	srl_Await();
	srl_Read(&val, 1);
	return val;
}
