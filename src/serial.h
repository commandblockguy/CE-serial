#include <usbdrvce.h>

#include <stdbool.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>

typedef struct SerialDeviceInfo {
    usb_device_t device;
    usb_endpoint_t in, out;
    uint8_t type;
    bool configured;
} srl_DeviceInfo_t;

typedef struct SerialDevice {
    srl_DeviceInfo_t info;
    char buffer[512];
    uint24_t bufStart;
    uint24_t bufLen;
} srl_Device_t;

enum DeviceType {
    UNKNOWN,
    CDC,
    FTDI
};

usb_error_t handle_usb_event(usb_event_t event, void *event_data, usb_callback_data_t *callback_data);

typedef struct {
    uint32_t rate;
    uint8_t charFormat;
    uint8_t parityType;
    uint8_t dataBits;
} lineCoding_t;

void srl_StartSerial(srl_Device_t *sdevice, lineCoding_t *lc);

void handleDevice(srl_Device_t *sdevice);

usb_error_t srl_Write(srl_Device_t *sdevice, void *data, size_t size, size_t *actual);

#define srl_WriteString(g, s) srl_Write(g, s, strlen(s), NULL)

usb_error_t srl_Read(srl_Device_t *sdevice, void *buffer, size_t size, size_t *read);
