/*
    Ninjaskit LCD Driver
    
    Copyright (C) 2016 Samuel Cowen

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#ifndef LCD_H_INCLUDED
#define LCD_H_INCLUDED

#include <etk/etk.h>
#include "ninjaskit/ninjaskit.h"


class LiquidCrystal : public etk::Stream<LiquidCrystal>
{
public:
    LiquidCrystal(gpio_pin rs, gpio_pin enable, gpio_pin rw,
                  gpio_pin d0, gpio_pin d1, gpio_pin d2, gpio_pin d3);

    void begin();

    void clear();
    void home();

    void set_cursor(uint8 row, uint8 col);

    void display();
    void no_display();

    void show_cursor(bool cursor = true);
    void blink_cursor(bool blink = true);


    //puts a single character onto the LCD
    //this function is used by etk::Stream so you can write strings, ints and floats using << operators
    void put(char c)
    {
        send(c, true);
    }


private:
    void command(uint8 cmd);

    void send(uint8 cmd, bool mode);

    void write_bits(uint8_t value);
    void pulse();

    void busy_wait();

    gpio_pin rs_pin, enable_pin, rw_pin;
    gpio_pin data_pins[4];

    uint8 display_function;
    uint8 display_control;

    const uint8 LCD_CLEARDISPLAY = 0x01;
    const uint8 LCD_RETURNHOME = 0x02;
    const uint8 LCD_ENTRYMODESET = 0x04;
    const uint8 LCD_DISPLAYCONTROL = 0x08;
    const uint8 LCD_CURSORSHIFT = 0x10;
    const uint8 LCD_FUNCTIONSET = 0x20;
    const uint8 LCD_SETCGRAMADDR = 0x40;
    const uint8 LCD_SETDDRAMADDR =0x80;
    const uint8 LCD_ENTRYRIGHT = 0x00;
    const uint8 LCD_ENTRYLEFT = 0x02;
    const uint8 LCD_ENTRYSHIFTINCREMENT = 0x01;
    const uint8 LCD_ENTRYSHIFTDECREMENT = 0x00;
    const uint8 LCD_DISPLAYON =0x04;
    const uint8 LCD_DISPLAYOFF =0x00;
    const uint8 LCD_CURSORON =0x02;
    const uint8 LCD_CURSOROFF =0x00;
    const uint8 LCD_BLINKON =0x01;
    const uint8 LCD_BLINKOFF =0x00;
    const uint8 LCD_DISPLAYMOVE =0x08;
    const uint8 LCD_CURSORMOVE =0x00;
    const uint8 LCD_MOVERIGHT =0x04;
    const uint8 LCD_MOVELEFT =0x00;
    const uint8 LCD_8BITMODE = 0x10;
    const uint8 LCD_4BITMODE = 0x00;
    const uint8 LCD_2LINE = 0x08;
    const uint8 LCD_1LINE = 0x00;
    const uint8 LCD_5x10DOTS = 0x04;
    const uint8 LCD_5x8DOTS = 0x00;
};

#endif


