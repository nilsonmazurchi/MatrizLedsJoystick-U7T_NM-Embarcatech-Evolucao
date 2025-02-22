#ifndef INIT_GPIO_H  
#define INIT_GPIO_H

#include "pico/stdlib.h"

#define OUT_PIN 7  // Mesmo pino definido no config_matriz.h

void init_gpio(){
    // Apenas configuração básica necessária para a matriz
    gpio_init(OUT_PIN);
    gpio_set_dir(OUT_PIN, GPIO_OUT);
}

#endif