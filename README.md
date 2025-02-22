# Controle de Matriz LED e Display OLED com Joystick - Embarcatech

![Demo Project](https://img.youtube.com/vi/SEU_VIDEO_ID/0.jpg)  
*(Vídeo demonstrativo - substitua pelo link real)*

## 🚀 Funcionalidades Principais
- **Controle direcional com Joystick**:
  - ↔️ Movimento Horizontal (Eixo X)
  - ↕️ Movimento Vertical (Eixo Y)
  - 🎮 4 direções reconhecidas: Cima, Baixo, Esquerda, Direita
- **Visualização em tempo real**:
  - Matriz LED 8x8 exibe setas direcionais em azul
  - Display OLED 128x32 mostra texto descritivo
- **Modos de operação**:
  - Mensagem inicial de boas-vindas
  - Feedback visual imediato dos movimentos
  - Reset automático para estado neutro

## 🛠️ Tecnologias Utilizadas
| Componente          | Especificações                |
|---------------------|-------------------------------|
| Microcontrolador    | Raspberry Pi Pico (RP2040)    |
| Display OLED        | SSD1306 (I2C, 128x32 pixels)  |
| Matriz LED          | 8x8 com driver PIO            |
| Joystick            | Analógico (2 eixos)           |
| Protocolos          | I2C, PIO, ADC                 |

## 📦 Instalação
### Pré-requisitos
- [Visual Studio Code](https://code.visualstudio.com/)
- [Pico SDK](https://github.com/raspberrypi/pico-sdk)
- [CMake](https://cmake.org/) versão 3.12+

# Clone o repositório
git clone https://github.com/seu-usuario/projeto-matriz-oled.git
cd projeto-matriz-oled

# Configure o ambiente
- mkdir build
- cd build
- cmake ..
- make -j4

## 🔌 Diagrama de Conexões
| Componente       | GPIO Pico | Tipo       |
|------------------|-----------|------------|
| Joystick (Eixo X)| GPIO26    | ADC0       |
| Joystick (Eixo Y)| GPIO27    | ADC1       |
| OLED SDA         | GPIO14    | I2C1       |
| OLED SCL         | GPIO15    | I2C1       |
| Matriz LED DATA  | GPIO0     | PIO0       |

## 🎮 Como Usar
### **Inicialização**:
- OLED exibe "Bem-vindos! Embarcatech"
- Todos LEDs apagados

### **Controles**:
- ➡️ Direita: LED → | OLED "RIGHT"
- ⬅️ Esquerda: LED ← | OLED "LEFT"
- ⬆️ Cima: LED ↑ | OLED "TOP"
- ⬇️ Baixo: LED ↓ | OLED "DOWN"

### **Modo Neutro**:
- Sem movimento por 2s → LEDs apagados
- OLED mantém última direção

## ⚙️ Customização
```c
// config_matriz.h
#define BRILHO_LED 0.35    // Valores entre 0.0-1.0
#define THRESHOLD_LOW 1500  // Valor mínimo do ADC
#define THRESHOLD_HIGH 2500 // Valor máximo do ADC
#define TEMPO_DEBOUNCE 50   // ms para filtro de ruído
```

## ❗ Troubleshooting  
| Erro Comum               | Solução                      |  
|--------------------------|------------------------------|  
| LEDs não acendem         | Verifique conexão PIO        |  
| OLED sem display         | Confira endereço I2C (0x3C)  |  
| Leituras inconsistentes  | Calibre valores do ADC       |  
| Flickering na matriz     | Ajuste temporização no PIO   |  

## 📄 Licença  
**MIT License** - Consulte o arquivo [LICENSE](LICENSE) para detalhes.  

**Desenvolvido por** Nilson Mazurchi  
**Mentoria Embarcatech** - 2024  
🚀 [Veja outros projetos](https://github.com/seu-usuario)