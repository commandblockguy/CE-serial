#include <usbdrvce.h>

// Piss off a Mateo with this ONE SIMPLE TRICK
#undef NDEBUG
#define DEBUG
//#define dbg_sprintf sprintf
//#define dbgout (dbg_ptr+strlen(dbg_ptr))
#include <debug.h>

#define VERBOSE_EVENTS

#include <tice.h>

#include <stdbool.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>

#include <keypadc.h>
#include <graphx.h>

#include "serial.h"
#include "fileioc.h"

#if 1

#define LH 10

ti_var_t logFile;

void newLine(uint8_t *charX) {
    gfx_CopyRectangle(gfx_buffer, gfx_buffer, 0, LH, 0, 0, LCD_WIDTH, LCD_HEIGHT - LH);
    gfx_SetColor(gfx_black);
    gfx_FillRectangle(0, LCD_HEIGHT - LH, LCD_WIDTH, LH);
    gfx_BlitBuffer();
    dbg_sprintf(dbgout, "\n");
    *charX = 0;
    gfx_SetTextXY(0, LCD_HEIGHT - LH);
}

void printText(char *str) {
    static uint8_t charX = 0;
    gfx_SetTextXY(charX * 8, LCD_HEIGHT - LH);
    for(; str[0]; str++) {
        switch (str[0]) {
            case '\n':
            case '\r': {
                newLine(&charX);
                break;
            }

            case '\b': {
                if(charX) {
                    charX--;
                    gfx_SetColor(gfx_black);
                    gfx_FillRectangle(charX * 8, LCD_HEIGHT - LH, 8, LH);
                    break;
                }
            }

            default: {
                if (charX >= 40) newLine(&charX);
                gfx_PrintChar(str[0]);
                dbg_sprintf(dbgout, "%c", str[0]);
                charX++;
                break;
            }
        }
    }
    gfx_BlitBuffer();
}

void main(void) {
    srl_Device_t sdevice = {0};
    usb_error_t error;

    uint24_t cooldown = 0;

    sdevice.info.configured = false;
    sdevice.info.device = 0;

    ti_CloseAll();

    logFile = ti_Open("logFile", "w");

    gfx_Begin();
    gfx_SetDrawBuffer();
    gfx_FillScreen(gfx_black);
    gfx_SetTextFGColor(39);
    gfx_SetMonospaceFont(8);
    gfx_BlitBuffer();

    if ((error = usb_Init(handle_usb_event, &sdevice, NULL,
                          USB_DEFAULT_INIT_FLAGS)) == USB_SUCCESS) {

        static char buf[512];

        while ((error = usb_WaitForInterrupt()) == USB_SUCCESS) {
            size_t length;

            kb_Scan();
            if (kb_IsDown(kb_KeyClear)) break;
            if (kb_IsDown(kb_Key2nd) && sdevice.info.configured && !cooldown) {
                srl_WriteString(&sdevice, "Test String, to Demonstrate that the Bridge Can Send Messages Both Ways, Though I am Too Lazy to Create a Proper Input System.\n");
                printText("Sent test message.\n");
                cooldown = 100;
            }

            if (sdevice.info.configured && sdevice.info.type == FTDI) {
                srl_Read(&sdevice, buf, 512, &length);
                buf[length] = 0;
                if (length) {
                    printText(buf);
                }
            }

            handleDevice(&sdevice);

            if (cooldown) cooldown--;

        }
    }
    if (error) {
        char buf[30];
        //dbg_sprintf(dbgout, "Error: %X\n", error);
        sprintf(buf, "Error: %X\n", error);
        printText(buf);
    }
    printText("Cleaning up...\n");
    usb_Cleanup();
    printText("Press any key to exit\n");
    os_GetKey();
    gfx_End();
    ti_CloseAll();
}

#else
void main(void) {
    srl_Device_t sdevice;
    usb_error_t error;

    sdevice.info.configured = false;
    sdevice.info.device = 0;

    if ((error = usb_Init(handle_usb_event, &sdevice, NULL,
                          USB_DEFAULT_INIT_FLAGS)) == USB_SUCCESS) {
        while ((error = usb_WaitForInterrupt()) == USB_SUCCESS) {
            kb_Scan();
            if (kb_IsDown(kb_KeyClear)) break;

            handleDevice(&sdevice);

            if (kb_IsDown(kb_Key2nd) && sdevice.info.configured) {
                char test[] = "Test\r\n";
                size_t length;
                srl_WriteString(&sdevice, test);
                dbg_sprintf(dbgout, "Test\n");
            }

            if (kb_IsDown(kb_KeyAlpha) && sdevice.info.configured) {
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
