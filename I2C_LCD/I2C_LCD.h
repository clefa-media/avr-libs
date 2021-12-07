/**
 * @file I2C_LCD.h
 *
 * @author ClefaMedia
 *
 * @version 1.0
 *
 * @copyright
 * Copyright (C) ClefaMedia 2021. 
 * All Rights MIT Licensed.
 *
 * @brief This library was created to connect a Liquid Crystal Display 
 * with a Hitachi HD44780U controller and an I2C-I/O-Expander PCF8574 over I2C.
 * Maximum display dimensions: 1x80, 2x40, 4x20
 * 
 * The I2C-Master library from Peter Fleury is used for the I2C-connection.
 */


#ifndef _I2C_LCD_H                  // Prevents duplicate
#define _I2C_LCD_H   1              // forward declarations

#include <avr/io.h>                 // Requires AVR Input/Output
#include <inttypes.h>               // Requires Inttypes

#define I2C_LCD_ADDRESS 0x4E        // full 8-bit address of the I2C-Modul

// I2C Multiplexer to LCD
#define I2C_LCD_RS      0x01
#define I2C_LCD_RW      0x02
#define I2C_LCD_E       0x04
#define I2C_LCD_BL      0x08
#define I2C_LCD_DB4     0x10
#define I2C_LCD_DB5     0x20
#define I2C_LCD_DB6     0x40
#define I2C_LCD_DB7     0x80
#define I2C_LCD_DB      0xF0

// commands
#define I2C_LCD_CLEARDISPLAY 0x01
#define I2C_LCD_RETURNHOME 0x02
#define I2C_LCD_ENTRYMODESET 0x04
#define I2C_LCD_DISPLAYCONTROL 0x08
#define I2C_LCD_CURSORSHIFT 0x10
#define I2C_LCD_FUNCTIONSET 0x20
#define I2C_LCD_SETCGRAMADDR 0x40
#define I2C_LCD_SETDDRAMADDR 0x80

// flags for display entry mode
#define I2C_LCD_ENTRYRIGHT 0x00
#define I2C_LCD_ENTRYLEFT 0x02
#define I2C_LCD_ENTRYSHIFTINCREMENT 0x01
#define I2C_LCD_ENTRYSHIFTDECREMENT 0x00

// flags for display on/off control
#define I2C_LCD_DISPLAY 0x04
#define I2C_LCD_CURSOR 0x02
#define I2C_LCD_BLINK 0x01

// flags for display/cursor shift
#define I2C_LCD_DISPLAYMOVE 0x08
#define I2C_LCD_CURSORMOVE 0x00
#define I2C_LCD_MOVERIGHT 0x04
#define I2C_LCD_MOVELEFT 0x00

// flags for function set
#define I2C_LCD_8BITMODE 0x10
#define I2C_LCD_4BITMODE 0x00
#define I2C_LCD_2LINE 0x08
#define I2C_LCD_1LINE 0x00
#define I2C_LCD_5x10DOTS 0x04
#define I2C_LCD_5x8DOTS 0x00

#define I2C_LCD_ON  0xFF
#define I2C_LCD_OFF 0x00 

/** ===================================================
 * @brief function to initialize the I2C-LCD-Modul
 * + set 4-Bit mode
 * + clear display, cursor, blink
 * + set entry mode
 * + set dimensions
 * Need to be called only once
 * 
 * The I2C-Bus must be initialized in the main-file (f.e. 80kHz)
 * with this code: "I2CMasterInit(SCL_CLK)"
 * 
 * @param cols  LCD Colums  
 * @param lines LCD Rows
 */
void I2C_LCD_init(uint8_t cols, uint8_t lines);

/** ===================================================
 * @brief function to clear the LCD 
 * and set Cursor to 1, 1 (home)
 */
void I2C_LCD_clear(void);

/** ===================================================
 * @brief function to set the cursor 
 * to the home position (1,1)
 */
void I2C_LCD_home(void);

/** ===================================================
 * @brief function to set the cursor to a specific position
 * Home Position (upper, left corner) is 1, 1
 * 
 * @param col column: >0 && <numcolumn
 * @param row row: >0 && <numcolumn
 */
void I2C_LCD_setCursor(uint8_t col, uint8_t row); 

/** ===================================================
 * @brief function to set the Cursor
 * without a integreated I2C connection to a specific position.
 * Home Position (upper, left corner) is 1, 1
 * Only use when I2C-connection is etablished!
 * @param col column: >0 && <numcolumn
 * @param row row: >0 && <numcolumn
 */
void I2C_LCD_setCursorWOI2C(uint8_t col, uint8_t row);

/** ===================================================
 * @brief function to print an array with characters
 * linebreaks are made by the modul automatically
 * 
 * @param str "string", array with characters
 */
void I2C_LCD_print(uint8_t str[]);

/** ===================================================
 * @brief function to print a single character (ASCII or custom)
 * to the LCD-Modul
 * 
 * @param c Character (ASCII-code)
 */
void I2C_LCD_printChar(uint8_t c);

/** ===================================================
 * @brief function to dis/enable the LCD layer of the modul
 * 
 * @param state ON/OFF
 */
void I2C_LCD_display(uint8_t state);

/** ===================================================
 * @brief function to dis/enable the backlight of the modul
 * 
 * @param state ON/OFF
 */
void I2C_LCD_backlight(uint8_t state);

/** ===================================================
 * @brief function to dis/enable the blink behavier of the cursor
 * only visible when the cursor state is on
 * 
 * @param state ON/OFF
 */
void I2C_LCD_blink(uint8_t state);

/** ===================================================
 * @brief function to set the visibility of the cursor
 * 
 * @param state ON/OFF
 */
void I2C_LCD_cursor(uint8_t state);

/** ===================================================
 * @brief function to set the textflow to left -> right
 */
void I2C_LCD_leftToRight(void);

/** ===================================================
 * @brief function to set the textflow to right -> right
 * 
 * f.e. print("Hello World") results in "dlroW olleH" on the display
 */
void I2C_LCD_rightToLeft(void);

/** ===================================================
 * @brief function to shift the entire display one step to the left
 * special case: 4 row displays are shifting the content throw 2 lines
 */
void I2C_LCD_scrollDisplayLeft(void);

/** ===================================================
 * @brief function to shift the entire display one step to the right
 * special case: 4 row displays are shifting the content throw 2 lines
 */
void I2C_LCD_scrollDisplayRight(void);

/** ===================================================
 * @brief function to fix the cursor on his position
 * so the text will move "out of the cursor"
 * 
 * @param state ON/IFF
 */
void I2C_LCD_cursorFixPosition(uint8_t state);

/** ===================================================
 * @brief function to create a custom char in the CGRAM
 * There are 8 free spaces available
 * 
 * @param location location in the CGRAM 0x00 - 0x07
 * @param charmap 5x8 array with dots
 */
void I2C_LCD_createChar(uint8_t location, uint8_t charmap[]);

/** ===================================================
 * @brief function to write a single character (ASCII & custom)
 * to the display. No I2C connections is etabilshed
 * 
 * @param c character
 */
void I2C_LCD_write(uint8_t c);

/** ===================================================
 * @brief function to write a command to the LCD-controller
 * with 2 4-bit nipples
 * 
 * @param cmd 8-bit command
 */
void I2C_LCD_command4bit(uint8_t cmd);

/** ===================================================
 * @brief function to write an 8-bit command to the LCD-controller
 * where only the first four bits are relevant
 * 
 * @param cmd 8-bit command
 */
void I2C_LCD_command8bit(uint8_t cmd);

/** ===================================================
 * @brief function to set the row offset f.e. by a 4-row display
 * 
 * @param row1 startaddress of row 1
 * @param row2 startaddress of row 2
 * @param row3 startaddress of row 3
 * @param row4 startaddress of row 4
 */
void I2C_LCD_setRowOffsets(uint8_t row1, uint8_t row2, uint8_t row3, uint8_t row4);

/** ===================================================
 * @brief function to write a command to the I2C I/O-Extender
 * 
 * @param i2c_data 8-bit data (4 databits, backlight, clock, rw, rs)
 */
void I2C_LCD_push(uint8_t i2c_data);


/** @brief variable to store the status of the backlight */
uint8_t backlight;
/** @brief number of lines of the display */
uint8_t numlines;
/** @brief number of columns of the display */
uint8_t numcols;
/** @brief last displayfunction cmd */
uint8_t displayfunction;
/** @brief last displaycontrol cmd */
uint8_t displaycontrol;
/** @brief last displaymode cmd */
uint8_t displaymode;
/** @brief array to store all rowoffsets */
uint8_t row_offsets[4];


#endif                                         // End prevent duplicate forward
/* _I2C_LCD_H */                               // declarations block

/**
 * TERMS OF USE: MIT License
 *
 * Permission is hereby granted, free of charge, to any person obtaining a
 * copy of this software and associated documentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation
 * the rights to use, copy, modify, merge, publish, distribute, sublicense,
 * and/or sell copies of the Software, and to permit persons to whom the
 * Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL
 * THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
 * DEALINGS IN THE SOFTWARE.
 */