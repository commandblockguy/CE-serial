/**
 * @file nio_ce.h
 * @author  Julian Mackeben aka compu <compujuckel@googlemail.com>
 * @author  Adrien Bertrand aka Adriweb (CE port and mods)
 * @version 4.0
 *
 * @section LICENSE
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston,
 * MA 02110-1301  USA
 *
 * @section DESCRIPTION
 *
 * Nspire I/O (CE port) header file
 */

#ifndef NSPIREIO_H
#define NSPIREIO_H

#ifndef PLATFORM_H
#define PLATFORM_H

#define NIO_CHAR_WIDTH 6
#define NIO_CHAR_HEIGHT 8

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>

// CE-specific stuff
#include <tice.h>
#include <graphx.h>
#include <keypadc.h>

// Fullscreen definitions

#define NIO_MAX_ROWS 30
#define NIO_MAX_COLS 53

#define SCREEN_WIDTH    gfx_lcdWidth
#define SCREEN_HEIGHT   gfx_lcdHeight

void wait_key_pressed(void); // blocks until a key is pressed
bool any_key_pressed(void); // non-blocking, TRUE if any key pressed

#define strerror(errno) "errno"

/** Initializes double buffering.
*/
bool nio_scrbuf_init();

/** Clears the screen buffer.
*/
void nio_scrbuf_clear();

/** Frees the screenbuffer and restores the screen to its original state.
*/
void nio_scrbuf_free();

char* nio_get_back_buffer();

// These functions are the same on all platforms...

void nio_set_global_color(unsigned int color);
void nio_vram_pixel_set(unsigned int x, unsigned int y);
void nio_vram_fill(unsigned x, unsigned y, unsigned w, unsigned h);
void nio_vram_draw(void);
void nio_vram_scroll(unsigned x, unsigned y, unsigned w, unsigned h, unsigned scroll);
unsigned int nio_cursor_clock(void);
unsigned char nio_ascii_get(uint8_t* adaptive_cursor_state);

#endif


/**
 * @file queue.h
 * @author  Julian Mackeben aka compu <compujuckel@googlemail.com>
 * @version 3.1
 *
 * @section LICENSE
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston,
 * MA 02110-1301  USA
 *
 * @section DESCRIPTION
 *
 * Queue header
 */

#ifndef QUEUE_H
#define QUEUE_H

#define QUEUE_SIZE 500

/** queue structure */
typedef struct
{
    char data[QUEUE_SIZE + 1];
    int start;
    int end;
    int count;
} queue;

/** Initialize queue.
    @param q Queue to initialize
*/
void queue_init(queue* q);

/** Push value to the end of the queue.
    @param q Queue
    @param val Value to push
*/
void queue_put(queue* q, char val);

/** Get value from the end of the queue.
    @param q Queue
    @return the value
*/
char queue_get_top(queue* q);

/** Get value from the beginning of the queue.
    @param q Queue
    @return the value
*/
char queue_get(queue* q);

/** Check if the queue is empty.
    @param q Queue
    @return true if empty
*/
bool queue_empty(queue* q);

#endif








#define HISTORY_LINES 6

/** Color defines */
enum
{
    NIO_COLOR_BLACK = 0,
    NIO_COLOR_RED,
    NIO_COLOR_GREEN,
    NIO_COLOR_YELLOW,
    NIO_COLOR_BLUE,
    NIO_COLOR_MAGENTA,
    NIO_COLOR_CYAN,
    NIO_COLOR_GRAY,
    NIO_COLOR_LIGHTBLACK,
    NIO_COLOR_LIGHTRED,
    NIO_COLOR_LIGHTGREEN,
    NIO_COLOR_LIGHTYELLOW,
    NIO_COLOR_LIGHTBLUE,
    NIO_COLOR_LIGHTMAGENTA,
    NIO_COLOR_LIGHTCYAN,
    NIO_COLOR_WHITE
};

/** console structure */
typedef struct
{
    char* data;
    unsigned short* color;
    queue* input_buf;
    int cursor_x;
    int cursor_y;
    int max_x;
    int max_y;
    int offset_x;
    int offset_y;
    unsigned char default_background_color;
    unsigned char default_foreground_color;
    bool drawing_enabled;
    bool cursor_enabled;
    int cursor_type;
    int cursor_line_width;
    unsigned char cursor_custom_data[6];
    bool cursor_blink_enabled;
    bool cursor_blink_status;
    unsigned cursor_blink_timestamp;
    unsigned cursor_blink_duration;
    int (*idle_callback)(void*);
    void* idle_callback_data;
    int history_line;
    char *history[HISTORY_LINES];
    int pending;
} nio_console_private;

typedef nio_console_private *nio_console;

#define NIO_KEY_UP 0x80
#define NIO_KEY_DOWN 0x81
#define NIO_KEY_ESC 0x82

#define NIO_CURSOR_BLOCK 0
#define NIO_CURSOR_UNDERSCORE 1
#define NIO_CURSOR_VERTICAL 2
#define NIO_CURSOR_CUSTOM 3
#define NIO_CURSOR_ADAPTIVE 4

/** Draws a char to the VRAM on the given position. For internal use.
    @param x x position in columns
    @param y y position in rows
    @param ch Char
    @param bgColor Background color
    @param textColor text color
*/
void nio_vram_pixel_putc(int x, int y, char ch, int bgColor, int textColor);

/** Draws a string to the VRAM on the given position. For internal use.
    @param x x position in columns
    @param y y position in rows
    @param str String
    @param bgColor Background color
    @param textColor text color
*/
void nio_vram_pixel_puts(int x, int y, const char* str, int bgColor, int textColor);

/** Draws a string to the VRAM on the given position. For internal use.
    @param offset_x x offset in px
    @param offset_y y offset in px
    @param x x position in columns (px*NIO_CHAR_WIDTH)
    @param y y position in rows (px*NIO_CHAR_HEIGHT)
    @param str String
    @param bgColor Background color
    @param textColor text color
*/
void nio_vram_grid_puts(int offset_x, int offset_y, int x, int y, const char *str, unsigned char bgColor, unsigned char textColor);

/** Draws a char to the VRAM on the given position. For internal use.
    @param offset_x x offset in px
    @param offset_y y offset in px
    @param x x position in columns (px*NIO_CHAR_WIDTH)
    @param y y position in rows (px*NIO_CHAR_HEIGHT)
    @param ch Char
    @param bgColor Background color
    @param textColor text color
*/
void nio_vram_grid_putc(int offset_x, int offset_y, int x, int y, char ch, unsigned char bgColor, unsigned char textColor);

/** Sets a default console that will be used for all functions without console argument, e.g. nio_puts()
    @param c Console
*/
void nio_set_default(nio_console* c);

/** Give control to a function when waiting for input (i.e. the cursor is flashing).
    Useful for performing background tasks.
    The callback function should return 0 on success or a non-zero value to abort input.
    @param c console
    @param cb Callback function
    @param data Data passed to the callback function
*/
void nio_set_idle_callback(nio_console* c, int (*callback)(void*), void* data);

/** Gets the default console.
    @return default console
*/
nio_console* nio_get_default(void);

/** Clears a console.
    @param c Console
*/
void nio_clear(nio_console* c);

/** Scrolls a console one line down.
    @param c Console
*/
void nio_scroll(nio_console* c);

/** Draws a char from the console to the VRAM. For internal use.
    @param c Console
    @param pos_x x position
    @param pos_y y position
*/
void nio_vram_csl_drawchar(nio_console* c, int pos_x, int pos_y);

/** Saves a char in a console without drawing it. For internal use.
    @param c Console
    @param ch Char
    @param pos_x x position
    @param pos_y y position
*/
void nio_csl_savechar(nio_console* c, char ch, int pos_x, int pos_y);

/** Sets the background- and text color of a console. You can use the predefined colors (NIO_COLOR_*)
    @param c Console
    @param background_color Background color
    @param foreground_color Text color
*/
void nio_color(nio_console* c, unsigned char background_color, unsigned char foreground_color);

/** Changes the drawing behavior of a console.
    @param c Console
    @param enable_drawing If this is true, a console will automatically be updated if text is written to it.
*/
void nio_drawing_enabled(nio_console* c, const bool enable_drawing);

/** Initializes a console.
    @param c Console
    @param size_x console width. Use NIO_MAX_COLS to get a full-width console.
    @param size_y console height. Use NIO_MAX_ROWS to get a full-height console.
    @param offset_x x position
    @param offset_y y position
    @param background_color Background color. Use predefined colors (NIO_COLOR_*)
    @param foreground_color Text color. Use predefined colors (NIO_COLOR_*)
    @param drawing_enabled See nio_drawing_enabled()
    @return true if successful
*/
bool nio_init(nio_console* c, int size_x, int size_y, int offset_x, int offset_y, unsigned char background_color, unsigned char foreground_color, const bool drawing_enabled);

/** Uninitializes a console. This should always be called before the program ends.
    @param c Console
*/
void nio_free(nio_console* c);

/** See [fflush](http://www.cplusplus.com/reference/clibrary/cstdio/fflush/)
    \note This is useful for consoles with enable_drawing set to false. Using this function draws the console to the screen.
*/
int nio_fflush(nio_console* c);

/** See [fputc](http://www.cplusplus.com/reference/clibrary/cstdio/fputc/)
*/
int nio_fputc(int character, nio_console* c);

/** See [write](http://pubs.opengroup.org/onlinepubs/9699919799/functions/write.html)
    \note For use in libsyscalls.
*/
int nio_write(nio_console *c, char *ptr, int len);

/** See [putchar](http://www.cplusplus.com/reference/clibrary/cstdio/putchar/)
*/
int nio_putchar(int character);

/** See [fputs](http://www.cplusplus.com/reference/clibrary/cstdio/fputs/)
*/
int nio_fputs(const char* str, nio_console* c);

/** See [puts](http://www.cplusplus.com/reference/clibrary/cstdio/puts/)
*/
int nio_puts(const char* str);

/** See [fgetc](http://www.cplusplus.com/reference/clibrary/cstdio/fgetc)
*/
int nio_fgetc(nio_console* c);

/** See [getchar](http://www.cplusplus.com/reference/clibrary/cstdio/getchar)
*/
int nio_getchar(void);

/** See [read](http://pubs.opengroup.org/onlinepubs/9699919799/functions/read.html)
    \note For use in libsyscalls.
*/
int nio_read(nio_console *csl, char *str, int num);

/** See [fgets](http://www.cplusplus.com/reference/clibrary/cstdio/fgets/)
*/
char* nio_fgets(char* str, int num, nio_console* c);

/** See [gets](http://www.cplusplus.com/reference/clibrary/cstdio/gets/)
*/
char* nio_gets(char* str);// __attribute__((deprecated));

/** Like [gets](http://www.cplusplus.com/reference/clibrary/cstdio/gets/), but with a maximum length parameter
*/
char* nio_getsn(char* str, int num);

/** See [fscanf](http://www.cplusplus.com/reference/cstdio/fscanf/)
*/
/*
#define nio_fscanf(c, format, ...) \
({ \
    char tmp[100]; \
    nio_fgets(tmp,100,c); \
    sscanf(tmp,format, ##__VA_ARGS__); \
})
*/

/** See [scanf](http://www.cplusplus.com/reference/cstdio/scanf/)
*/
/*
#define nio_scanf(format, ...) \
({ \
    nio_fscanf(nio_get_default(),format, ##__VA_ARGS__); \
})
*/

//int nio_vfprintf(nio_console* c, const char* format, va_list* arglist);

/** See [fprintf](http://www.cplusplus.com/reference/clibrary/cstdio/fprintf/)
*/
int nio_fprintf(nio_console* c, const char* format, ...);

/** See [printf](http://www.cplusplus.com/reference/clibrary/cstdio/printf/)
*/
int nio_printf(const char* format, ...);

/** See [perror](http://www.cplusplus.com/reference/clibrary/cstdio/perror/)
*/
void nio_perror(const char* str);

// Macro of nio_fgetc
#define nio_getc nio_fgetc

// Macro of nio_fputc
#define nio_putc nio_fputc

/** See [_getch](http://msdn.microsoft.com/de-de/library/078sfkak\(v=vs.80\).aspx)
    \note unlike _getch, this takes a console as an argument!
*/
int nio_getch(nio_console* c);

/** See [_getch](http://msdn.microsoft.com/de-de/library/078sfkak(v=vs.80).aspx)
*/
int nio__getch(void);

/** See [_getche](http://msdn.microsoft.com/de-de/library/kswce429\(v=vs.80\).aspx)
    \note unlike _getche, this takes a console as an argument!
*/
int nio_getche(nio_console* c);

/** See [_getche](http://msdn.microsoft.com/de-de/library/kswce429\(v=vs.80\).aspx)
*/
int nio__getche(void);

/** Returns the current time.
    @return Current RTC time
*/
unsigned nio_time_get();

/** Draws the cursor of the console, if enabled.
    @param c Console
*/
void nio_cursor_draw(nio_console* c);

/** Erases the cursor of the console, if enabled.
    @param c Console
*/
void nio_cursor_erase(nio_console* c);

/** Draws a blinking cursor, if enabled. Blinking occurs on an interval set inside the console.
    @param c Console
*/
void nio_cursor_blinking_draw(nio_console* c);

/** Resets the blinking cursor timer.
    @param c Console
*/
void nio_cursor_blinking_reset(nio_console* c);

/** Enables the console cursor.
    @param c Console
    @param enable_cursor When this is true, a cursor will be drawn to the screen, false: no cursor shown.
*/
void nio_cursor_enable(nio_console* c, bool enable_cursor);

/** Enables console cursor blinking.
    @param c Console
    @param enable_cursor_blink When this is true, the cursor will blink, false: no cursor blinking will occur.
*/
void nio_cursor_blinking_enable(nio_console* c, bool enable_cursor_blink);

/** Sets the console cursor blink duration (the time it takes to switch on or off)
    @param c Console
    @param duration The time (in seconds) it takes to switch on or off.
*/
void nio_cursor_blinking_duration(nio_console* c, int duration);

/** Sets the console cursor type.
    @param c Console
    @param cursor_type The cursor type. 0 is a block cursor (like a
    Linux X11 terminal), 1 is an underscore cursor (like a Windows Command
    Prompt window), 2 is a vertical bar cursor (like a regular text box),
    3 is a custom cursor that is set via nio_cursor_custom, and 4 is an
    adaptive cursor: It shows the current state of shift/ctrl/caps (default).

    If you specify an invalid value, NspireIO will silenty fail and set the
    cursor type to 0, a block cursor.

    You may also use the predefined types as arguments. (NIO_CURSOR_*)
*/
void nio_cursor_type(nio_console* c, int cursor_type);

/** Sets the console cursor width.
    @param c Console
    @param cursor_width The cursor line width. This only applies to cursors
    1 and 2 (underscore and vertical bar). All others cursor types will not
    be affected by this setting.

    For the underscore cursor, it must be greater than 0 and less than or
    equal to CHAR_HEIGHT (as defined by charmap.h). At the time of writing,
    CHAR_HEIGHT is 8. Therefore, for an underscore cursor,
    0 < cursor_width <= 8.

    For a vertical bar cursor, it must be greater than 0 and less than or
    equal to CHAR_WIDTH (as defined by charmap.h). At the time of writing,
    CHAR_WIDTH is 6. Therefore, for a vertical bar cursor, 0 < cursor_width < 6.

    If you wish to draw a blank cursor, you probably should disable the cursor
    altogether with nio_cursor_enable(nio_console, false).

    Note that if you specify an out-of-range value, NspireIO will silently fail
    and reset the cursor width to 1.
*/
void nio_cursor_width(nio_console* c, int cursor_width);

/** Sets the console cursor width.
    @param c Console
    @param cursor_data The custom cursor data. This is in the form of a char[6]
    array. This pretty much uses the format (and the drawing code) for character
    drawing, so take a look at charmap.h for examples. Note that the characters
    in charmap.h are truncated, so they will display differently.

    By default, if this is not specified and the cursor type is set to the
    custom cursor type (3), the custom cursor will be set to
    {0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF} (a block cursor).
*/
void nio_cursor_custom(nio_console* c, const unsigned char cursor_data[6]);

#endif

