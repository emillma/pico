#include "pico/stdlib.h"

#pragma once

int64_t turn_off(alarm_id_t id, void *user_data)
{
    gpio_put(25, 0);
    return 0;
}

void blink_for(uint32_t ms)
{
    gpio_put(25, 1);
    add_alarm_in_ms(ms, turn_off, NULL, false);
}

void blink_fast(uint32_t duration = 300)
{
    uint32_t time = to_ms_since_boot(get_absolute_time());
    while (to_ms_since_boot(get_absolute_time()) < time + duration)
    {
        blink_for(25);
        sleep_ms(50);
    }
}

void init_led()
{
    gpio_init(25);
    gpio_set_dir(25, GPIO_OUT);
    blink_fast();
}

void led_on()
{
    gpio_put(25, 1);
}
void led_off()
{
    gpio_put(25, 0);
}

void led_set(bool state)
{
    gpio_put(25, state);
}

void led_error(uint32_t duration = 500)
{
    while (true)
    {
        led_on();
        sleep_ms(duration);
        led_off();
        sleep_ms(duration);
    }
}