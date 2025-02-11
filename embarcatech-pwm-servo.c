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
}


int main() {
    stdio_init_all();
    setup_pwm();

    while (true) {
        printf("Hello, world!\n");
        sleep_ms(1000);
    }
}
