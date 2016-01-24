#include "ninjaskit/ninjaskit.h"
#include "lcd/lcd.h"

LiquidCrystal lcd({PA, 1}, {PB, 5}, {PA, 3}, {PA, 6}, {PA, 4}, {PA, 2}, {PA, 0});

void hard_fault_handler(void)
{
    lcd.set_cursor(0, 0);
    lcd.print("Hard fault.");

    while(true)
    { }
}


int main(void)
{
    clock_setup();

    spi2.begin();

    configure_as_output({PB, 0});
    set_pin({PB, 0}, true);
    etk::sleep_ms(300);

	//configure chip select pin
    auto cs = gpio_pin(PA, 8);
    configure_as_output(cs);
    set_pin(cs, true);

	//start LCD screen
    lcd.begin();


    etk::sleep_ms(500);
    while(true)
    {
        lcd.set_cursor(0, 0);
        lcd.print("Temp: ");

        set_pin(cs, false);

        union spidata
        {
            char bytes[4];
            int32 data;
        };

        spidata data;
        data.bytes[3] = spi2.read();
        data.bytes[2] = spi2.read();
        data.bytes[1] = spi2.read();
        data.bytes[0] = spi2.read();

        set_pin(cs, true);

        lcd.set_cursor(2, 6);

        int32 v = data.data;

        if (v & 0x80000000)
            v = 0xFFFFC000 | ((v >> 18) & 0x00003FFFF);
        else
            v >>= 18;

        real_t deg_c = v;
        deg_c *= 0.25;
        lcd.print(deg_c, " C");
        etk::sleep_ms(500);
    }
}


