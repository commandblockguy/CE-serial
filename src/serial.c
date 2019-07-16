#include <usbdrvce.h>

// Piss off a Mateo with this ONE SIMPLE TRICK
// Piss off a Mateo with this ONE SIMPLE TRICK
#undef NDEBUG
#define DEBUG
//#define dbg_sprintf sprintf
//#define dbgout (dbg_ptr+strlen(dbg_ptr))
#include <debug.h>

//extern char *dbg_ptr;

#define VERBOSE_EVENTS

#include <tice.h>

#include <stdbool.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>

#include "serial.h"

extern ti_var_t logFile;

extern uint8_t charX;

static void putBlockHex(void *block, size_t size) {
    while (size--)
        dbg_sprintf(dbgout, "%X", *(*(unsigned char **)&block)++);
    dbg_sprintf(dbgout, "\n");
}

#ifdef VERBOSE_EVENTS 
//#define printEvent(event) dbg_sprintf(dbgout, "%s:%X\n", usb_event_names[event], (unsigned)event_data)
void printEvent(event, data) {
    static const char *usb_event_names[] = {
        "USB_ROLE_CHANGED_EVENT",
        "USB_DEVICE_DISCONNECTED_EVENT",
        "USB_DEVICE_CONNECTED_EVENT",
        "USB_DEVICE_DISABLED_EVENT",
        "USB_DEVICE_ENABLED_EVENT",
        "USB_DEVICE_OVERCURRENT_DEACTIVATED_EVENT",
        "USB_DEVICE_OVERCURRENT_ACTIVATED_EVENT",
        "USB_DEFAULT_SETUP_EVENT",
        // Temp debug events:
        "USB_DEVICE_INT",
        "USB_DEVICE_CONTROL_INT",
        "USB_DEVICE_FIFO_INT",
        "USB_DEVICE_DEVICE_INT",
        "USB_OTG_INT",
        "USB_HOST_INT",
        "USB_CONTROL_INPUT_INT",
        "USB_CONTROL_OUTPUT_INT",
        "USB_CONTROL_END_INT",
        "USB_CONTROL_ERROR_INT",
        "USB_CONTROL_ABORT_INT",
        "USB_FIFO0_INPUT_INT",
        "USB_FIFO0_OUTPUT_INT",
        "USB_FIFO0_SHORT_PACKET_INT",
        "USB_FIFO1_INPUT_INT",
        "USB_FIFO1_OUTPUT_INT",
        "USB_FIFO1_SHORT_PACKET_INT",
        "USB_FIFO2_INPUT_INT",
        "USB_FIFO2_OUTPUT_INT",
        "USB_FIFO2_SHORT_PACKET_INT",
        "USB_FIFO3_INPUT_INT",
        "USB_FIFO3_OUTPUT_INT",
        "USB_FIFO3_SHORT_PACKET_INT",
        "USB_DEVICE_RESET_INT",
        "USB_DEVICE_SUSPEND_INT",
        "USB_DEVICE_RESUME_INT",
        "USB_DEVICE_ISOCHRONOUS_ERROR_INT",
        "USB_DEVICE_ISOCHRONOUS_ABORT_INT",
        "USB_DEVICE_ZERO_LENGTH_PACKET_TRANSMIT_INT",
        "USB_DEVICE_ZERO_LENGTH_PACKET_RECEIVE_INT",
        "USB_DEVICE_DMA_FINISH_INT",
        "USB_DEVICE_DMA_ERROR_INT",
        "USB_DEVICE_IDLE_INT",
        "USB_DEVICE_WAKEUP_INT",
        "USB_B_SRP_COMPLETE_INT",
        "USB_A_SRP_DETECT_INT",
        "USB_A_VBUS_ERROR_INT",
        "USB_B_SESSION_END_INT",
        "USB_OVERCURRENT_INT",
        "USB_B_PLUG_REMOVED_INT",
        "USB_A_PLUG_REMOVED_INT",
        "USB_HOST_PORT_CONNECT_STATUS_CHANGE_INT",
        "USB_HOST_PORT_ENABLE_DISABLE_CHANGE_INT",
        "USB_HOST_PORT_OVERCURRENT_CHANGE_INT",
        "USB_HOST_PORT_FORCE_PORT_RESUME_INT",
        "USB_HOST_FRAME_LIST_ROLLOVER_INT",
        "USB_HOST_SYSTEM_ERROR_INT",
        "USB_HOST_ASYNC_ADVANCE_INT",
    };
    char buf[100];
    sprintf(buf, "%s:%X\n", usb_event_names[event], (unsigned)data);
    printText(buf); 
}
#else
#define printEvent(event) dbg_sprintf(dbgout, "%X:%X\n", event, (unsigned)event_data)
#endif

usb_error_t handle_usb_event(usb_event_t event, void *event_data,
                                    usb_callback_data_t *callback_data) {

    switch (event) {
        case USB_ROLE_CHANGED_EVENT:
            printEvent(event, (unsigned)event_data);
            break;
        case USB_DEVICE_DISCONNECTED_EVENT:
            // Let's hope that the compiler realizes that this is the same pointer as callback_data, at least for now
            memset(&(((srl_Device_t*)callback_data)->info), 0, sizeof(srl_DeviceInfo_t));
        case USB_DEVICE_CONNECTED_EVENT:
            printEvent(event, (unsigned)event_data);
            dbg_sprintf(dbgout, "%X", (unsigned)usb_FindDevice(NULL, NULL, USB_SKIP_HUBS));
            break;
        case USB_DEVICE_DISABLED_EVENT:
            printEvent(event, (unsigned)event_data);
            break;
        case USB_DEVICE_ENABLED_EVENT:
            printEvent(event, (unsigned)event_data);
            dbg_sprintf(dbgout, "%X", (unsigned)usb_FindDevice(NULL, NULL, USB_SKIP_HUBS));

            if (!((srl_Device_t*)callback_data)->info.device) {
                ((srl_Device_t*)callback_data)->info.device = event_data;
            }
            break;
        case USB_DEFAULT_SETUP_EVENT: {
            unsigned char i;
            putBlockHex(event_data, 8);
            return USB_IGNORE;
        }
        case USB_HOST_FRAME_LIST_ROLLOVER_INTERRUPT: {
            static unsigned counter;
            dbg_sprintf(dbgout, "%u", ++counter);
            break;
        }
        case USB_DEVICE_INTERRUPT:
        case USB_DEVICE_DEVICE_INTERRUPT:
        case USB_DEVICE_CONTROL_INTERRUPT:
        case USB_DEVICE_WAKEUP_INTERRUPT:
        case USB_HOST_INTERRUPT:
            break;
        default:
            printEvent(event, (unsigned)event_data);
            break;
    }
    return USB_SUCCESS;
}

static bool parseConfigurationDescriptor(srl_Device_t *const sdevice,
                                         const usb_device_descriptor_t *const device,
                                         usb_configuration_descriptor_t *const configuration,
                                         const size_t length) {
    uint8_t *current = (uint8_t *)configuration;
    size_t remaining = length;
    usb_error_t error;
    uint8_t in = 0, out = 0;
    printText("Parsing configuration descriptors...\n");
    while (remaining && (!in || !out)) {
        usb_descriptor_t *descriptor = (usb_descriptor_t *)current;
        if (remaining < 2 || remaining < descriptor->bLength) return false;
        switch (descriptor->bDescriptorType) {
            case USB_INTERFACE_DESCRIPTOR: {
                usb_interface_descriptor_t *interface = (usb_interface_descriptor_t *)descriptor;
                if (device->idVendor == 0x2341 && device->idProduct == 0x0001) {
                    //dbg_sprintf(dbgout, "Found a Uno\n");
                    printText("Found a Uno\n");
                    sdevice->info.type = CDC;
                } else if (device->idVendor == 0x0403 && device->idProduct == 0x6001) {
                    //dbg_sprintf(dbgout, "Found a FTDI\n");
                    printText("Found a FTDI\n");
                    sdevice->info.type = FTDI;
                } else {
                    sdevice->info.type = 0;
                }
                in = out = 0;
                break;
            }
            case USB_ENDPOINT_DESCRIPTOR: {
                usb_endpoint_descriptor_t *endpoint = (usb_endpoint_descriptor_t *)descriptor;
                if (sdevice->info.type && endpoint->bmAttributes == USB_BULK_TRANSFER) {
                    uint8_t *addr = endpoint->bEndpointAddress & USB_DEVICE_TO_HOST ? &in : &out;
                    if (!*addr) *addr = endpoint->bEndpointAddress;
                }
                break;
            }
        }
        current += descriptor->bLength;
        remaining -= descriptor->bLength;
    }
    if (!in || !out) return false;
    if ((error = usb_SetConfiguration(sdevice->info.device, configuration, length)) != USB_SUCCESS) {
        dbg_sprintf(dbgout, "%X\n", error);
        return false;
    }
    sdevice->info.in = usb_GetDeviceEndpoint(sdevice->info.device, in);
    sdevice->info.out = usb_GetDeviceEndpoint(sdevice->info.device, out);
    return true;
}

const lineCoding_t srl_default_lc = {115200, 0, 0, 8};

void srl_StartSerial(srl_Device_t *sdevice, lineCoding_t *lc) {
    switch (sdevice->info.type) {
        default: {
            //dbg_sprintf(dbgout, "Tried to initialize with non-serial device connected.\n");
            printText("Tried to initialize with non-serial device connected.\n");
            return;
        }
        case CDC: {
            const usb_control_setup_t setup = {0x21, 0x20, 0x0000, 0x0000, sizeof(lineCoding_t)};
            usb_error_t error = 0;
            size_t length;

            error = usb_DefaultControlTransfer(sdevice->info.device, &setup, lc, 8, &length);

            if (error) {
                char buf[50];
                //dbg_sprintf(dbgout, "Error %u on ctrl transfer\n", error);
                sprintf(buf, "Error %u on ctrl transfer\n", error);
                printText(buf);
            }

            dbg_sprintf(dbgout, "%u bytes\n", length);
            break;
        }
        case FTDI: {
            usb_control_setup_t setup = {0x40, 0x3, 0x0000, 0x0000, sizeof(lineCoding_t)};
            usb_error_t error = 0;

            setup.wValue = 0x001a; // TODO: convert from baud rate to whatever the hell this is
            setup.wIndex = 0x0000;

            error = usb_DefaultControlTransfer(sdevice->info.device, &setup, NULL, 0, NULL);

            if (error) {
                char buf[50];
                //dbg_sprintf(dbgout, "Error %u on ctrl transfer\n", error);
                sprintf(buf, "Error %u on ctrl transfer\n", error);
                printText(buf);
            }

            break;
        }
    }
    
}

void handleDevice(srl_Device_t *sdevice) {
    char buf[50];
    usb_error_t error;
    usb_device_descriptor_t device;
    size_t length;
    uint8_t index;
    bool found = false;
    usb_configuration_descriptor_t *configuration = NULL;
    if (!sdevice->info.device) return;
    if (!sdevice->info.configured) {
        sdevice->info.configured = true;
        //dbg_sprintf(dbgout, "Device marked as configured.\n");
        printText("Device marked as configured.\n");
        if ((error = usb_GetDescriptor(sdevice->info.device, USB_DEVICE_DESCRIPTOR,
                                       0, &device, sizeof(device), &length))
            != USB_SUCCESS) goto err;
        if (length < sizeof(device)) goto noerr;
        putBlockHex(&device, sizeof(device));
        for (index = 0; !found && index != device.bNumConfigurations; ++index) {
            length = usb_GetConfigurationDescriptorTotalLength(sdevice->info.device, index);
            if (!(configuration = malloc(length))) goto noerr;
            if ((error = usb_GetDescriptor(sdevice->info.device, USB_CONFIGURATION_DESCRIPTOR,
                                           index, configuration, length, &length))
                != USB_SUCCESS) goto err;
            dbg_sprintf(dbgout, "%u:", index);
            putBlockHex(configuration, length);
            found = parseConfigurationDescriptor(sdevice, &device, configuration, length);
            free(configuration); configuration = NULL;
        }
        if (!found) goto noerr;

        //dbg_sprintf(dbgout, "In: %X | Out: %X\n", usb_GetEndpointAddress(sdevice->info.in), usb_GetEndpointAddress(sdevice->info.out));
        sprintf(buf, "In: %X | Out: %X\n", usb_GetEndpointAddress(sdevice->info.in), usb_GetEndpointAddress(sdevice->info.out));
        printText(buf);
        if (sdevice->info.type) {
            srl_StartSerial(sdevice, &srl_default_lc);
        }
    }
    goto noerr;
 err:
    //dbg_sprintf(dbgout, "Error in device handling: %X\n", error);
    sprintf(buf, "Error in device handling: %X\n", error);
    printText(buf);
 noerr:
    if (configuration) free(configuration);
    //memset(sdevice, 0, sizeof(srl_Device_t));
 }

usb_error_t srl_Write(srl_Device_t *sdevice, void *data, size_t size, size_t *actual) {
    usb_error_t error;

    error = usb_BulkTransfer(sdevice->info.out, data, size, 0, actual);

    dbg_sprintf(dbgout, "%X:%u\n", error, *actual);

    return error;
}

usb_error_t srl_Read(srl_Device_t *sdevice, void *buffer, size_t size, size_t *read) {
    size_t totalSize;

    //dbg_sprintf(dbgout, "Starting to read %u bytes to buffer %p\n", size, buffer);

    for(totalSize = 0; totalSize < size;) {
        char buf[512];
        size_t length;
        usb_error_t error;

        size_t actualSize = size - totalSize;

        //dbg_sprintf(dbgout, "%u bytes read so far, reading up to %u now\n", totalSize, actualSize);

        error = usb_BulkTransfer(sdevice->info.in, buf, 512, 0, &length);

        //dbg_sprintf(dbgout, "Transferred: %u\n", length);

        if (error) {
            dbg_sprintf(dbgout, "Error: %X\n", error);
            return error;
        }

        switch (sdevice->info.type) {
            case CDC: {
                memcpy(buffer + totalSize, buf, length);
                totalSize += length;
                break;
            }
            case FTDI: {
                uint16_t status = *((uint16_t*)buf);
                //dbg_sprintf(dbgout, "FTDI input status: %X\n", status);
                memcpy(buffer + totalSize, buf + 2, length - 2);
                totalSize += length - 2;
                break;
            }
        }

        if (length != 64) {
            *read = totalSize;
            return USB_SUCCESS;
        }
    }

    *read = totalSize;
    return USB_SUCCESS;
}
