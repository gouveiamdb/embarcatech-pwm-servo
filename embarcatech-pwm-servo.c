#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/pwm.h"

#define SERVO_PIN 22
#define PWM_FREQ 50
#define CLOCK_DIV 64
#define WRAP_COUNT 39062

uint16_t us_to_count(uint16_t us) {
    return us * (125000 / CLOCK_DIV) / 1000;
}

void setup_pwm() {
    gpio_set_function(SERVO_PIN, GPIO_FUNC_PWM);
    uint slice_num = pwm_gpio_to_slice_num(SERVO_PIN);

    pwm_set_clkdiv(slice_num, CLOCK_DIV);
    pwm_set_wrap(slice_num, WRAP_COUNT);
    
    pwm_set_enabled(slice_num, true);
}

void move_servo_smooth(uint16_t start, uint16_t end) {
    int step = (start < end) ? 5 : -5;
    uint16_t slice_num = pwm_gpio_to_slice_num(SERVO_PIN);

    for (int us = start; (step > 0) ? us <= end : us >= end; us += step) {
        pwm_set_chan_level(slice_num, PWM_CHAN_A, us_to_count(us));
        sleep_ms(10);  // Atraso de ajuste de 10ms
    }
}

int main() {
    stdio_init_all();
    setup_pwm();

    while (true) {
        // 180 graus (2400µs)
        printf("Movendo para 180 graus\n");
        pwm_set_chan_level(pwm_gpio_to_slice_num(SERVO_PIN), PWM_CHAN_A, us_to_count(2400));
        sleep_ms(5000);

        // 90 graus (1470µs)
        printf("Movendo para 90 graus\n");
        pwm_set_chan_level(pwm_gpio_to_slice_num(SERVO_PIN), PWM_CHAN_A, us_to_count(1470));
        sleep_ms(5000);

        // 0 graus (500µs)
        printf("Movendo para 0 graus\n");
        pwm_set_chan_level(pwm_gpio_to_slice_num(SERVO_PIN), PWM_CHAN_A, us_to_count(500));
        sleep_ms(5000);

        // movimento suave
        printf("Movendo suavemente de 0° a 180°\n");
        move_servo_smooth(500, 2400);
        
        printf("Movendo suavemente de 180° a 0°\n");
        move_servo_smooth(2400, 500);
        
    }

    return 0;
}
