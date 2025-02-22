#ifndef CONFIG_MATRIZ_H  
#define CONFIG_MATRIZ_H

#include "pio_matrix.pio.h"

#define NUM_PIXELS 25

// Variáveis para a matriz
uint32_t valor_led;
double r = 0.0, b = 0.0, g = 0.0;


// Pino de saída da matriz (WS2812) da placa 
#define OUT_PIN 7

// Padrão para apagar os LEDs
double apagar_leds[NUM_PIXELS] =   
                        {0.0, 0.0, 0.0, 0.0, 0.0,
                         0.0, 0.0, 0.0, 0.0, 0.0, 
                         0.0, 0.0, 0.0, 0.0, 0.0,
                         0.0, 0.0, 0.0, 0.0, 0.0,
                         0.0, 0.0, 0.0, 0.0, 0.0};

// Padrões para as setas
double seta_direita[NUM_PIXELS] =   
                        {0.0, 0.0, 0.35, 0.0, 0.0,
                         0.0, 0.0, 0.0, 0.35, 0.0, 
                         0.35, 0.35, 0.35, 0.35, 0.35,
                         0.0, 0.0, 0.0, 0.35, 0.0,
                         0.0, 0.0, 0.35, 0.0, 0.0};

double seta_esquerda[NUM_PIXELS] =   
                        {0.0, 0.0, 0.35, 0.0, 0.0,
                         0.0, 0.35, 0.0, 0.0, 0.0, 
                         0.35, 0.35, 0.35, 0.35, 0.35,
                         0.0, 0.35, 0.0, 0.0, 0.0,
                         0.0, 0.0, 0.35, 0.0, 0.0};

double seta_cima[NUM_PIXELS] =   
                        {0.0, 0.0, 0.35, 0.0, 0.0,
                         0.0, 0.35, 0.35, 0.35, 0.0, 
                         0.35, 0.0, 0.35, 0.0, 0.35,
                         0.0, 0.0, 0.35, 0.0, 0.0,
                         0.0, 0.0, 0.35, 0.0, 0.0};

double seta_baixo[NUM_PIXELS] =   
                        {0.0, 0.0, 0.35, 0.0, 0.0,
                         0.0, 0.0, 0.35, 0.0, 0.0, 
                         0.35, 0.0, 0.35, 0.0, 0.35,
                         0.0, 0.35, 0.35, 0.35, 0.0,
                         0.0, 0.0, 0.35, 0.0, 0.0};

// Rotina para definição da intensidade de cores do LED
uint32_t matrix_rgb(double b, double r, double g)
{
  unsigned char R, G, B;
  R = r * 255;
  G = g * 255;
  B = b * 255;
  return (G << 24) | (R << 16) | (B << 8);
}

// Rotina para acionar a matriz de LEDs - WS2812B
void desenho_pio(double *desenho, uint32_t valor_led, PIO pio, uint sm, double r, double g, double b)
{
    for (int16_t i = 0; i < NUM_PIXELS; i++) {
        valor_led = matrix_rgb(desenho[24-i], r, g);
        pio_sm_put_blocking(pio, sm, valor_led);
    }
}

#endif