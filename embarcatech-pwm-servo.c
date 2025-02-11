#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/pwm.h"

#define SERVO_PIN 22
#define PWM_FREQ 50
#define WRAP_COUNT 39062

void setup_pwm() {
    pwm_init(pwm_gpio_to_slice_num(SERVO_PIN), PWM_FREQ, WRAP_COUNT);
    pwm_set_gpio_level(SERVO_PIN, 0);
    pwm_set_enabled(pwm_gpio_to_slice_num(SERVO_PIN), true);

    uint slice_num = pwm_gpio_to_slice_num(SERVO_PIN);
}


int main() {
    stdio_init_all();
    setup_pwm();

    uint slice_num = pwm_gpio_to_slice_num(SERVO_PIN);

    while (true) {
        // 180 graus (2400µs)
        printf("Movendo para 180 graus\n");
        pwm_set_chan_level(slice_num, PWM_CHAN_A, us_to_count(2400));
        sleep_ms(5000);

        // 90 graus (1470µs)
        printf("Movendo para 180 graus\n");
        pwm_set_chan_level(slice_num, PWM_CHAN_A, us_to_count(2400));
        sleep_ms(5000);

        // 0 graus (500µs)
        printf("Movendo para 0 graus\n");
        pwm_set_chan_level(slice_num, PWM_CHAN_A, us_to_count(500));
        sleep_ms(5000);
    }
}
