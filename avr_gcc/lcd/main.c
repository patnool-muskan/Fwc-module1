/*
 Corrected AVR HD44780 4-bit driver (PB0..PB5)
 Displays a static "8" on the LCD.

 Wiring assumed (Arduino/AVR PORTB pins):
 PB0 -> RS
 PB1 -> E
 PB2 -> D4
 PB3 -> D5
 PB4 -> D6
 PB5 -> D7

 R/W must be tied to GND. V0 (contrast) -> 10k pot between VCC & GND (wiper -> V0).
*/

#include <avr/io.h>
#include <util/delay.h>
#include <stdlib.h>
#include <stdint.h>

typedef uint8_t byte;

/* bit helpers */
#define ClearBit(x,y) ( (x) &= ~_BV(y) )
#define SetBit(x,y)   ( (x) |=  _BV(y) )

/* pin mapping on PORTB */
#define LCD_RS 0
#define LCD_E  1
#define DAT4   2
#define DAT5   3
#define DAT6   4
#define DAT7   5

#define CLEARDISPLAY 0x01

/* Pulse enable line: E high for a short time then low */
static void PulseEnableLine(void)
{
    SetBit(PORTB, LCD_E);
    _delay_us(2);     // minimum enable pulse width >450ns; 2µs is safe
    ClearBit(PORTB, LCD_E);
    _delay_us(50);    // let the LCD process the nibble
}

/* Send the upper 4 bits of 'data' (bits 4..7 must hold the nibble) */
static void SendNibble(byte data)
{
    /* clear data lines (PB2..PB5) */
    PORTB &= ~((1<<DAT4)|(1<<DAT5)|(1<<DAT6)|(1<<DAT7));

    /* set data lines from bits 4..7 of data */
    if (data & (1<<4)) SetBit(PORTB, DAT4);
    if (data & (1<<5)) SetBit(PORTB, DAT5);
    if (data & (1<<6)) SetBit(PORTB, DAT6);
    if (data & (1<<7)) SetBit(PORTB, DAT7);

    PulseEnableLine();
}

/* Send a full byte in 4-bit mode: high nibble first, then low nibble */
static void SendByte(byte data)
{
    SendNibble(data & 0xF0);               // upper 4 bits at positions 4..7
    SendNibble((data & 0x0F) << 4);        // lower 4 bits shifted into 4..7
}

/* Send command (RS = 0) */
void LCD_Cmd(byte cmd)
{
    ClearBit(PORTB, LCD_RS);
    SendByte(cmd);
    _delay_ms(2);
}

/* Send character (RS = 1) */
void LCD_Char(byte ch)
{
    SetBit(PORTB, LCD_RS);
    SendByte(ch);
    _delay_ms(2);
}

/* Initialize LCD in 4-bit mode (HD44780 sequence) */
void LCD_Init(void)
{
    /* make sure outputs are low initially */
    PORTB &= ~((1<<LCD_RS)|(1<<LCD_E)|(1<<DAT4)|(1<<DAT5)|(1<<DAT6)|(1<<DAT7));

    _delay_ms(50);            // wait after Vcc rises (datasheet: >40ms)

    /* Standard safe init sequence */
    LCD_Cmd(0x33);            // initialize
    LCD_Cmd(0x32);            // set to 4-bit mode
    LCD_Cmd(0x28);            // function set: 4-bit, 2 line, 5x7
    LCD_Cmd(0x0C);            // display on, cursor off
    LCD_Cmd(0x06);            // entry mode: increment cursor
    LCD_Cmd(CLEARDISPLAY);    // clear display
    _delay_ms(3);
}

/* Clear display */
void LCD_Clear(void)
{
    LCD_Cmd(CLEARDISPLAY);
    _delay_ms(3);
}

/* Send NUL-terminated string to LCD */
void LCD_Message(const char *text)
{
    while (*text) {
        LCD_Char((byte)*text++);
    }
}

/* Display integer (decimal) */
void LCD_Integer(int data)
{
    char st[8];
    itoa(data, st, 10);
    LCD_Message(st);
}

int main(void)
{
    /* configure only the pins we use as outputs (keeps other bits safe) */
    DDRB |= (1<<LCD_RS)|(1<<LCD_E)|(1<<DAT4)|(1<<DAT5)|(1<<DAT6)|(1<<DAT7);

    /* Initialize LCD */
    LCD_Init();

    /* Show a static '8' at first position */
    LCD_Clear();
    LCD_Char('8');

    /* loop idle */
    while (1) {
        /* nothing needed - display is static */
        _delay_ms(1000);
    }

    return 0;
}
