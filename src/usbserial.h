#ifndef H_USBSERIAL
#define H_USBSERIAL

#include <stdint.h>
#include <stdlib.h>
#include <stdbool.h>

#ifdef __cplusplus
extern "C" {
#endif

enum charFormat {
	//number of stop bits
	sb_1 = 0,
	sb_1_5,
	sb_2
};

enum parityType {
	parity_none = 0,
	parity_odd,
	parity_even,
	parity_mark,
	parity_space
};

//usually {9600,0,0,8}
typedef struct {
	uint32_t rate;
	uint8_t charFormat;
	uint8_t parityType;
	uint8_t dataBits;
} lineCoding_t;

char test(uint8_t arg0);

void usb_PrePower(uint24_t time);

void usb_Cleanup();

//Initialize a USB device. Call this only once, before srl_ConfigSerial
//Returns 0 if failed
uint8_t srl_InitDevice();

//Configure serial transmission. Must call this before sending or recieving data.
void srl_ConfigSerial(lineCoding_t* lc);

//Get line coding data
//First byte is inaccurate?
lineCoding_t srl_GetLineCoding(void);

//Write bytes from a buffer to serial
void srl_Write(void* buf, uint24_t len);

//Write a string to serial
#define srl_WriteString(str) srl_Write((str), strlen((str)) + 1)

//Write a single byte to serial
#define srl_WriteByte(byte) srl_Write(&(byte), 1)

//todo: srl_Printf() ?

//Read bytes. Returns number of bytes transfered.
uint24_t srl_Read(void* buf, uint24_t len);

//Read one byte
//Will wait for a byte if there is not one currently avaliable - possibly forever
char srl_ReadByte(void);

//Check if there are any bytes available
bool srl_Available(void);

//Wait for a byte to be available without reading it
void srl_Await(void);

#ifdef __cplusplus
}
#endif

#endif
