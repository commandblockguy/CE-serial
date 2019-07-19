#include <usbdrvce.h>

// Piss off a Mateo with this ONE SIMPLE TRICK
#undef NDEBUG
#define DEBUG
#include <debug.h>

#define VERBOSE_EVENTS

#include <tice.h>

#include <stdbool.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>

#include <keypadc.h>
#include <graphx.h>

#include "serial_old.h"
#include "fileioc.h"

#include "nio_ce.h"

void main(void) {
    srl_device_t sdevice = {0};
    usb_error_t error;

    uint24_t cooldown = 0;

    nio_console c1;

    sdevice.configured = false;
    sdevice.device = 0;

    nio_init(&c1, NIO_MAX_COLS, NIO_MAX_ROWS, 0, 0, NIO_COLOR_BLACK, NIO_COLOR_WHITE, true);
    nio_set_default(&c1);
    nio_cursor_type(&c1, NIO_CURSOR_UNDERSCORE);

    if ((error = usb_Init(handle_usb_event, &sdevice, NULL,
                          USB_DEFAULT_INIT_FLAGS)) == USB_SUCCESS) {


        while ((error = usb_WaitForInterrupt()) == USB_SUCCESS) {
            size_t length;
            static char buf[512];
            int write;

            kb_Scan();
            if (kb_IsDown(kb_KeyClear)) break;
            if (kb_IsDown(kb_Key2nd) && sdevice.configured && !cooldown) {
                srl_WriteString(&sdevice, "Test String, to Demonstrate that the Bridge Can Send Messages Both Ways, Though I am Too Lazy to Create a Proper Input System.\n");
                nio_printf("Sent test message.\n");
            }

            if (sdevice.configured && sdevice.type == SRL_FTDI) {
                srl_Read(&sdevice, buf, 512, &length);
                buf[length] = 0;
                if (length) {
                    nio_printf(buf);
                }
            }

            handleDevice(&sdevice);

            if (cooldown) cooldown--;

        }
    }
    if (error) {
        char buf[30];
        dbg_sprintf(dbgout, "Error: %X\n", error);
        nio_printf("Error: %X\n", error);
    }
    nio_printf("Cleaning up...\n");
    usb_Cleanup();
    nio_printf("Press any key to exit\n");
    os_GetKey();
    gfx_End();
}

#if 0
void main(void) {
    srl_device_t sdevice;
    usb_error_t error;

    sdevice.configured = false;
    sdevice.device = 0;

    if ((error = usb_Init(handle_usb_event, &sdevice, NULL,
                          USB_DEFAULT_INIT_FLAGS)) == USB_SUCCESS) {
        while ((error = usb_WaitForInterrupt()) == USB_SUCCESS) {
            kb_Scan();
            if (kb_IsDown(kb_KeyClear)) break;

            handleDevice(&sdevice);

            if (kb_IsDown(kb_Key2nd) && sdevice.configured) {
                char test[] = "Test\r\n";
                size_t length;
                srl_WriteString(&sdevice, test);
                dbg_sprintf(dbgout, "Test\n");
            }

            if (kb_IsDown(kb_KeyAlpha) && sdevice.configured) {
                static char buffer[512];
                size_t length;
                srl_Read(&sdevice, buffer, 512, &length);
                buffer[length] = 0;
                dbg_sprintf(dbgout, "Read %u-byte string:\n", length);
                dbg_sprintf(dbgout, "%s\n", buffer);
            }
        }
    }
    if (error) {
        dbg_sprintf(dbgout, "Error: %X\n", error);
    }
    usb_Cleanup();
    os_GetKey();
}
#endif
