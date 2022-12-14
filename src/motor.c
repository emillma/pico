#include "hardware/pwm.h"

void configure_pwm()
{
    uint pwm_out_start = 10;
    for (uint pin = pwm_out_start; pin < pwm_out_start + 6; pin += 2)
    {
        gpio_set_function(pin, GPIO_FUNC_PWM);
        gpio_set_function(pin + 1, GPIO_FUNC_PWM);

        uint slice_num = pwm_gpio_to_slice_num(pin);
        pwm_config config = pwm_get_default_config();
        pwm_config_set_clkdiv(&config, 1.0f);
        pwm_init(slice_num, &config, false);

        uint level = 125;
        pwm_set_wrap(slice_num, level * 2);
        pwm_set_chan_level(slice_num, PWM_CHAN_A, level - 1);
        pwm_set_chan_level(slice_num, PWM_CHAN_B, level + 1);
        pwm_set_output_polarity(slice_num, false, true);
        pwm_set_phase_correct(slice_num, true);
    }
    pwm_set_mask_enabled(0b1111111);
}