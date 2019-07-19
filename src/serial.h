#include <usbdrvce.h>

#include <stdbool.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>

typedef struct srl_Device {
    usb_device_t device;
    usb_endpoint_t in, out;
    uint8_t type;
    bool configured;
    char *buffer;
    uint24_t bufStart;
    uint24_t bufLen;
} srl_device_t;

enum srl_DeviceType {
    SRL_UNKNOWN,
    SRL_CDC,
    SRL_FTDI
};

typedef uint8_t srl_deviceType_t;

typedef struct srl_LineCoding {
    uint32_t rate;
    uint8_t charFormat;
    uint8_t parityType;
    uint8_t dataBits;
} srl_lineCoding_t;

void srl_Init(srl_device_t *srl, usb_device_t dev, void *buffer);

srl_deviceType_t srl_GetType(usb_device_t dev);

void srl_SetRate(srl_device_t *srl, uint24_t rate);
uint24_t srl_GetRate(srl_device_t *srl);

void srl_SetCoding(srl_device_t *srl, const srl_lineCoding_t *coding);
void srl_GetCoding(srl_device_t *srl, srl_lineCoding_t *coding);

size_t srl_Available(srl_device_t *srl);

void srl_ScheduleRead(srl_device_t *srl, void *buffer, size_t length, const void *handler(usb_error_t err, size_t length, void *callback_data), void *callback_data);
void srl_ScheduleWrite(srl_device_t *srl, const void *buffer, size_t length, const void *handler(usb_error_t err, void *callback_data), void *callback_data);

void srl_Read(srl_device_t *srl, void *buffer, size_t length);
void srl_Read_Timeout(srl_device_t *srl, void *buffer, size_t length, uint24_t timeout);
void srl_Write(srl_device_t *srl, const void *buffer, size_t length);

uint8_t srl_ReadByte(srl_device_t *srl);

void srl_printf(srl_device_t *srl, const char *format, ...);

void srl_PrintString(srl_device_t *srl, const char *str);

// Cleanup?
