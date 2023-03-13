#include <stdio.h>
#include "pico/stdlib.h"
#include "pico/bootrom.h"
#include "pico/stdio_usb.h"
#include "pico/stdio.h"

#include "hardware/clocks.h"
#include "hardware/watchdog.h"

#include "external.h"

bool repeating_timer_callback(struct repeating_timer *t)
{
    // current time
    uint64_t time = get_absolute_time();
    printf("Timer %llu\n", time);

    return true;
}

void process_data(void *data)
{
    printf("Data available!\n");
}

void blink_fast()
{
    uint64_t time = get_absolute_time();
    while (get_absolute_time() - time < (int)(0.5 * 1000000))
    {
        gpio_put(25, 1);
        sleep_ms(100);
        gpio_put(25, 0);
        sleep_ms(100);
    }
}

int main()
{
    stdio_init_all();
    // stdio_set_translate_crlf(&stdio_usb, false);
    gpio_init(25);
    gpio_set_dir(25, GPIO_OUT);
    blink_fast();
    printf("Hello, world!\n");
    printf("%i", PICO_STDIO_UART_SUPPORT_CHARS_AVAILABLE_CALLBACK);
    struct repeating_timer timer;
    add_repeating_timer_ms(500, repeating_timer_callback, NULL, &timer);
    char data[100];
    stdio_set_chars_available_callback(process_data, data);

    char hello;
    while (true)
    {
        sleep_ms(10);
        scanf("%c", &hello);
        printf("Got data: %c\n", hello);
        // if (hello == 'R')
        // {
        //     printf("Resetting...\n");
        //     reset_usb_boot(0, 0);
        // }
    }
}