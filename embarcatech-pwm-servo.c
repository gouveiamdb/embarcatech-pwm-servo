#include <stdio.h>          // Biblioteca para uso de printf
#include "pico/stdlib.h"    // Biblioteca para uso de sleep_ms
#include "hardware/pwm.h"   // Biblioteca para uso de PWM

#define SERVO_PIN 22        // Pino de controle do servo motor
#define LED_PIN 12          // Pino de LED para visualização do movimento
#define PWM_FREQ 50         // Frequência do sinal PWM
#define CLOCK_DIV 64        // Divisor de clock para gerar frequência de 50Hz
#define WRAP_COUNT 39062    // Contador de wrap para a frequência de 50Hz

// Função para converter um valor em microsegundos para o contador
uint16_t us_to_count(uint16_t us) {
    return (us * WRAP_COUNT) / 20000; // Conversão baseada no período de 20ms (20000us)
}

// Função para configurar o PWM
void setup_pwm() {
    gpio_set_function(SERVO_PIN, GPIO_FUNC_PWM); // Define o pino do servo como PWM
    gpio_set_function(LED_PIN, GPIO_FUNC_PWM);   // Define o pino do LED RGB como PWM
    
    uint16_t slice = pwm_gpio_to_slice_num(SERVO_PIN);  
    uint16_t led = pwm_gpio_to_slice_num(LED_PIN);   


    pwm_set_clkdiv(slice, CLOCK_DIV);   // Define divisor de clock para o servo
    pwm_set_wrap(slice, WRAP_COUNT);    // Define período do PWM para o servo
    
    pwm_set_clkdiv(led, CLOCK_DIV);   // Define divisor de clock para o LED
    pwm_set_wrap(led, WRAP_COUNT);    // Define período do PWM para o LED
    
    pwm_set_enabled(slice, true);   // Habilita o PWM do servo
    pwm_set_enabled(led, true);   // Habilita o PWM do LED
}

// Função para mover o servo de forma suave
void move_servo_smooth(uint16_t start, uint16_t end) {
    int step = (start < end) ? 5 : -5;  // Corrigido para inverter corretamente
    uint16_t slice = pwm_gpio_to_slice_num(SERVO_PIN);
    uint16_t led = pwm_gpio_to_slice_num(LED_PIN);

    for (int us = start; (step > 0) ? us <= end : us >= end; us += step) {
        pwm_set_chan_level(slice, PWM_CHAN_A, us_to_count(us)); // Ajusta posição do servo
        pwm_set_chan_level(led, PWM_CHAN_A, us_to_count(us)); // Ajusta posição do LED
        printf("Servo: %d us | LED: %d us\n", us, us);  // Exibe valores no terminal
        sleep_ms(10);  // Pequeno atraso para suavizar o movimento
    }
}

int main() {
    stdio_init_all();
    setup_pwm();

    // Posicionar servo inicialmente em 0°
    printf("Inicializando em 0°\n");
    pwm_set_chan_level(pwm_gpio_to_slice_num(SERVO_PIN), PWM_CHAN_A, us_to_count(500));
    pwm_set_chan_level(pwm_gpio_to_slice_num(LED_PIN), PWM_CHAN_A, us_to_count(500));
    sleep_ms(2000);

    while (true) {
        // Movimentos fixos
        printf("Movendo para 180 graus\n");
        pwm_set_chan_level(pwm_gpio_to_slice_num(SERVO_PIN), PWM_CHAN_A, us_to_count(2400));
        sleep_ms(5000);

        printf("Movendo para 90 graus\n");
        pwm_set_chan_level(pwm_gpio_to_slice_num(SERVO_PIN), PWM_CHAN_A, us_to_count(1470));
        sleep_ms(5000);

        printf("Movendo para 0 graus\n");
        pwm_set_chan_level(pwm_gpio_to_slice_num(SERVO_PIN), PWM_CHAN_A, us_to_count(500));
        sleep_ms(5000);

        // Movimento contínuo
        printf("Movendo suavemente de 0° a 180°\n");
        move_servo_smooth(500, 2400);

        printf("Movendo suavemente de 180° a 0°\n");
        move_servo_smooth(2400, 500);
    }

    return 0;
}
