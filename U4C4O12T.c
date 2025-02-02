// Bibliotecas
#include <stdio.h>
#include "pico/stdlib.h"
#include "pico/stdlib.h"
#include "hardware/pio.h"
#include "hardware/clocks.h"
#include "pico/bootrom.h"
// Funções próprias
#include "features/PIO.c"
#include "features/numeros.c"
#include "features/convert.c"

// Definição de variáveis para matriz de led.
#define LED_COUNT 25
#define LED_PIN 7

// Configurações dos pinos
const uint redPin = 13;   // Red=13, Blue=12, Green=11
const uint botaoA_pin = 5; // Botão A = 5, Botão B = 6 , BotãoJoy = 22
const uint botaoB_pin = 6; // Botão A = 5, Botão B = 6 , BotãoJoy = 22
const uint reset_pin = 22;

static void gpio_irq_handler(uint gpio, uint32_t events);

// Variáveis globais
uint count = 0;
bool reset = false;
static volatile uint32_t last_time = 0;
bool ledState = 1;

int main()
{
    stdio_init_all();
    initButton(botaoA_pin); // Função que configura o botão
    initButton(reset_pin);
    initButton(botaoB_pin);
    initLED(redPin);

    // Inicializa matriz de LEDs NeoPixel.
    npInit(LED_PIN);
    desenhaMatriz(desliga_LED, 0, 0.8); // Função para desligar todos os LEDs ws2812
    desenhaMatriz(numeros[0], 0, 1);        // Função que desenha o número 0 na matriz de ws2812

    gpio_set_irq_enabled_with_callback(botaoA_pin, GPIO_IRQ_EDGE_FALL, true, &gpio_irq_handler);
    gpio_set_irq_enabled_with_callback(botaoB_pin, GPIO_IRQ_EDGE_FALL, true, &gpio_irq_handler);
    gpio_set_irq_enabled_with_callback(reset_pin, GPIO_IRQ_EDGE_FALL, true, &gpio_irq_handler);

    uint lastcount = count;

    while (true)
    {
        if (count != lastcount && count < 10)//Imprime na matrix 5x5 o valor do contador até 9
        {

            desenhaMatriz(numeros[count], 0, 1);
            lastcount = count;
        }
        else if (reset)//Quando apertar o botão do joystick entra em modo bootloader
        {
            printf("HABILITANDO O MODO GRAVAÇÃO");
            reset_usb_boot(0, 0);
        }
        if (count == 10)//Desliga a matrix 5x5 para o contador = 10
        {
            desenhaMatriz(desliga_LED, 0, 0.8);
            lastcount = count;
        }
        gpio_put(redPin, ledState);
        ledState = !ledState;
        sleep_ms(1e2);
    }
}

void gpio_irq_handler(uint gpio, uint32_t events)
{
    uint32_t current_time = to_ms_since_boot(get_absolute_time());// Espera 200 ms para contornar o debouncing effect
    if (gpio == botaoA_pin && count < 10 && current_time - last_time > 2e2) //Incrementa em +1 o cotador 
    {
        last_time = current_time;
        count++;
    }
    else if (gpio == botaoB_pin && count > 0 && current_time - last_time > 2e2)//Incrementa em -1 o cotador
    {
        last_time = current_time;
        count--;
    }
    else if (gpio == reset_pin)
    {
        reset = 1;
    }
}
