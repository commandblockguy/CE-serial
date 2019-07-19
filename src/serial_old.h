#include <usbdrvce.h>

#include <stdbool.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>

typedef struct SerialDevice {
    usb_device_t device;
    usb_endpoint_t in, out;
    uint8_t type;
    bool configured;
    char *buffer;
    uint24_t bufStart;
    uint24_t bufLen;
} srl_device_t;

enum DeviceType {
    SRL_UNKNOWN,
    SRL_CDC,
    SRL_FTDI
};

usb_error_t handle_usb_event(usb_event_t event, void *event_data, usb_callback_data_t *callback_data);

typedef struct {
    uint32_t rate;
    uint8_t charFormat;
    uint8_t parityType;
    uint8_t dataBits;
} srl_lineCoding_t;

void srl_StartSerial(srl_device_t *sdevice, srl_lineCoding_t *lc);

void handleDevice(srl_device_t *sdevice);

usb_error_t srl_Write(srl_device_t *sdevice, void *data, size_t size, size_t *actual);

#define srl_WriteString(g, s) srl_Write(g, s, strlen(s), NULL)

usb_error_t srl_Read(srl_device_t *sdevice, void *buffer, size_t size, size_t *read);
