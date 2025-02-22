#include <stdlib.h>
#include <string.h>
#include "config_matriz.h"
#include "pio_matrix.pio.h"
#include "init_GPIO.h"
#include "hardware/adc.h"
#include "inc/ssd1306_i2c.h"

// Configurações do Joystick
#define JOYSTICK_X_PIN 27    // ADC1 (GP27)
#define JOYSTICK_Y_PIN 26    // ADC0 (GP26)
#define THRESHOLD_LOW 1500
#define THRESHOLD_HIGH 2500

// Configurações do OLED
#define I2C_SDA 14
#define I2C_SCL 15

// Enumeração das direções
typedef enum {
    DIR_NEUTRO,
    DIR_ESQUERDA,
    DIR_DIREITA,
    DIR_CIMA,
    DIR_BAIXO
} Direcao;

// Buffer e área de renderização do OLED
static uint8_t oled_buffer[ssd1306_buffer_length];
static struct render_area frame_area = {
    start_column: 0,
    end_column: ssd1306_width - 1,
    start_page: 0,
    end_page: ssd1306_n_pages - 1,
    buffer_length: 0
};

void init_joystick() {
    adc_init();
    adc_gpio_init(JOYSTICK_X_PIN);
    adc_gpio_init(JOYSTICK_Y_PIN);
}

Direcao ler_direcao() {
    adc_select_input(1); // Ler eixo X (GP27)
    uint16_t x = adc_read();
    
    adc_select_input(0); // Ler eixo Y (GP26)
    uint16_t y = adc_read();

    if (x < THRESHOLD_LOW) return DIR_ESQUERDA;
    if (x > THRESHOLD_HIGH) return DIR_DIREITA;
    if (y < THRESHOLD_LOW) return DIR_BAIXO;
    if (y > THRESHOLD_HIGH) return DIR_CIMA;
    
    return DIR_NEUTRO;
}

void mostrar_direcao(Direcao dir, PIO pio, uint sm) {
    switch(dir) {
        case DIR_ESQUERDA:
            desenho_pio(seta_direita, valor_led, pio, sm, 0.0, 0.0, 0.35);
            break;
        case DIR_DIREITA:
            desenho_pio(seta_esquerda, valor_led, pio, sm, 0.0, 0.0, 0.35);
            break;
        case DIR_CIMA:
            desenho_pio(seta_cima, valor_led, pio, sm, 0.0, 0.0, 0.35);
            break;
        case DIR_BAIXO:
            desenho_pio(seta_baixo, valor_led, pio, sm, 0.0, 0.0, 0.35);
            break;
        default:
            desenho_pio(apagar_leds, valor_led, pio, sm, 0.0, 0.0, 0.0);
    }
}

void atualizar_oled(Direcao dir) {
    static Direcao ultima_dir = DIR_NEUTRO;
    
    // Só atualiza se a direção mudar
    if (dir == ultima_dir) return;
    ultima_dir = dir;

    memset(oled_buffer, 0, ssd1306_buffer_length);

    const char *texto = NULL;
    switch(dir) {
        case DIR_CIMA:    texto = "TOP";    break;
        case DIR_BAIXO:  texto = "DOWN";   break;
        case DIR_ESQUERDA: texto = "LEFT";  break;
        case DIR_DIREITA: texto = "RIGHT";  break;
        default: // Neutro - não mostra nada
            render_on_display(oled_buffer, &frame_area);
            return;
    }

    // Centraliza o texto
    int largura = strlen(texto) * 6;
    int x = (ssd1306_width - largura) / 2;
    ssd1306_draw_string(oled_buffer, x, 8, (char *)texto);
    
    render_on_display(oled_buffer, &frame_area);
}

// Adicione esta função de inicialização
void mostrar_mensagem_inicial() {
    uint8_t buffer_inicial[ssd1306_buffer_length];
    memset(buffer_inicial, 0, ssd1306_buffer_length);
    
    // Desenha a mensagem inicial
    ssd1306_draw_string(buffer_inicial, 20, 8, "BEMVINDO");
    ssd1306_draw_string(buffer_inicial, 30, 16, "USUARIO!");
    render_on_display(buffer_inicial, &frame_area);
    
    // Mantém a mensagem por 2 segundos
    sleep_ms(2000);
    
    // Limpa o display após a mensagem inicial
    memset(buffer_inicial, 0, ssd1306_buffer_length);
    render_on_display(buffer_inicial, &frame_area);
}

int main() {
    stdio_init_all();
    init_gpio();
    init_joystick();

    // Inicialização do OLED
    i2c_init(i2c1, ssd1306_i2c_clock * 1000);
    gpio_set_function(I2C_SDA, GPIO_FUNC_I2C);
    gpio_set_function(I2C_SCL, GPIO_FUNC_I2C);
    gpio_pull_up(I2C_SDA);
    gpio_pull_up(I2C_SCL);
    ssd1306_init();
    calculate_render_area_buffer_length(&frame_area);

    mostrar_mensagem_inicial(); // Exibe a mensagem inicial

    // Inicialização da matriz de LEDs
    PIO pio = pio0;
    uint offset = pio_add_program(pio, &pio_matrix_program);
    uint sm = pio_claim_unused_sm(pio, true);
    pio_matrix_program_init(pio, sm, offset, OUT_PIN);

    while(1) {
        Direcao direcao = ler_direcao();
        mostrar_direcao(direcao, pio, sm);
        atualizar_oled(direcao);
        sleep_ms(50);
    }
}