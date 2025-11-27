/* 
  ###############
  # MIT License #
  ###############
  Copyright (c) 2025 José U.M Tavares

  Permission is granted, free of charge, to any person who obtains a copy
  of this software and associated documentation files (the "Software"), to handle
  the Software without restriction, including, without limitation, rights
  to use, copy, modify, merge, publish, distribute, sublicense and/or sell
  copies of the Software, and to permit persons to whom the Software is provided
  to do so, subject to the following conditions:

  The above copyright notice and this permission notice must be included in all
  copies or substantial portions of the Software.

  Projeto: Quimikey
  Programação: José Ubirajara Moreira Tavares
  Técnico em Eletrônica Faculdade de Tecnologia do SENAI-RS - 2015
  Projetista Eletrônico Sinbrax Tecnologia em Leds - Lagoa de Fora - Sombrio-SC
  Data: 19 de Novembro de 2025
  Descrição: 
  O código faz parte do sistema Quimikey, que simula a interação com a tabela periódica utilizando um display LCD.
  O sistema permite a exibição de informações de elementos químicos com base em um teclado matricial.
  Através da interação do usuário, o sistema exibe detalhes como o nome, símbolo, número atômico e massa atômica.
  O sistema também utiliza LEDs RGB para indicar a família química dos elementos selecionados, utilizando a biblioteca NeoPixel.
*/

// Inclusão das bibliotecas necessárias
#include <Wire.h>               // Biblioteca I2C (comunicação no barramento Wire)
#include <LiquidCrystal_I2C.h>  // Driver do LCD via I2C (mostra texto no display)
#include "lcd_display.h"        // Funções do display (Funções para controle do LCD)
#include "keypad.h"             // Funções do teclado matricial (Funções para leitura do teclado)
#include "elementos.h"          // Estruturas e dados do sistema (Dados dos elementos químicos)
#include "serial_comunicacao.h" // Envio e recebimento via Serial (Funções para comunicação serial)
#include <Adafruit_NeoPixel.h>  // Biblioteca NeoPixel (Controle da barra de LEDs RGB)

// Definições dos pinos e número de LEDs no NeoPixel
#define NUM_PIXELS 8           // Número de LEDs na barra NeoPixel
#define PIXEL_PIN 12           // Pino para controle dos LEDs

// Criação do objeto NeoPixel
Adafruit_NeoPixel pixels(NUM_PIXELS, PIXEL_PIN, NEO_GRB + NEO_KHZ800);

// Definição das cores para cada família (Índice do Vetor vai de 0 a 8, o índice 0 corresponde à Família 1)
uint32_t coresFamilia[9] = {
  pixels.Color(255, 0, 0),   // Família 1 - Metais alcalinos (Vermelho)
  pixels.Color(255, 165, 0), // Família 2 - Metais alcalino-terrosos (Laranja)
  pixels.Color(255, 255, 0), // Família 3 - Metais de transição (Amarelo)
  pixels.Color(0, 255, 0),   // Família 4 - Metais pós-transição (Verde)
  pixels.Color(0, 0, 255),   // Família 5 - Semimetais (Azul)
  pixels.Color(0, 255, 255), // Família 6 - Não metais (Ciano)
  pixels.Color(255, 0, 255), // Família 7 - Gases nobres (Roxo)
  pixels.Color(255, 192, 203), // Família 8 - Lantanídeos (Rosa)
  pixels.Color(255, 105, 180)  // Família 9 - Actinídeos (Magenta)
};

// Definindo as linhas e colunas do teclado matricial
const int linhas[9] = {3, 4, 5, 6, 7, 8, 9, 10, 11};  // Pinos que controlam as linhas do teclado
const int colunas[18] = {22, 24, 25, 26, 27, 28, 29, 30, 31, 32, 33, 34, 35, 36, 37, 38, 39, 41};  // Pinos que controlam as colunas do teclado

// Controle de teclas pressionadas
bool keyPressed[9][18];   // Matriz para armazenar o estado de cada tecla
unsigned long pressTime[9][18];  // Armazena o tempo de pressionamento de cada tecla
unsigned long lastActivity = 0;  // Armazena o tempo da última atividade (para inatividade)
const unsigned long idleTimeout = 5000;  // Tempo para inatividade antes de mostrar a mensagem padrão

/*
  Função: keypad_init
  Descrição: 
    A função keypad_init() é responsável por configurar os pinos do teclado matricial. 
    As linhas são configuradas como saídas (HIGH) e as colunas como entradas com pull-up, 
    permitindo que o teclado funcione corretamente.
    Além disso, os LEDs NeoPixel são inicializados e um teste simples é feito para garantir 
    que cada LED acenda nas cores apropriadas.
*/
void keypad_init() {
  // Inicializa as linhas do teclado como saídas (HIGH) e as colunas como entradas com pull-up
  for (int i = 0; i < 9; i++) {
    pinMode(linhas[i], OUTPUT);     // Configura os pinos das linhas como saídas
    digitalWrite(linhas[i], HIGH);  // Deixa as linhas desativadas inicialmente (HIGH)
  }

  for (int i = 0; i < 18; i++) {
    pinMode(colunas[i], INPUT_PULLUP); // Colunas em repouso = HIGH (usando o pull-up interno)
  }

  memset(keyPressed, 0, sizeof(keyPressed));  // Limpa o estado das teclas
  lastActivity = millis();                    // Registra o momento da última atividade
  
  // Inicialização do NeoPixel
  pixels.begin();  // Inicializa o NeoPixel
  pixels.clear();  // Limpa os LEDs ao iniciar
  pixels.show();   // Atualiza os LEDs

  // Teste básico do Neopixel acendendo todas as cores no boot vai e volta
  pixels.setPixelColor(0, pixels.Color(255, 0, 0));  // Acende o primeiro LED
  pixels.show();
  delay(200);  // Mantém o LED vermelho por 1 segundo
  pixels.setPixelColor(1, pixels.Color(255, 165, 0));  // Acende o segundo LED
  pixels.show();
  delay(200);  
  pixels.setPixelColor(2, pixels.Color(255, 255, 0));  // Acende o terceiro LED
  pixels.show();
  delay(200);  
  pixels.setPixelColor(3, pixels.Color(0, 255, 0));  // Acende o quarto LED
  pixels.show();
  delay(200);  
  pixels.setPixelColor(4, pixels.Color(0, 0, 255));  // Acende o quinto LED 
  pixels.show();
  delay(200);  
  pixels.setPixelColor(5, pixels.Color(0, 255, 255));  // Acende o sexto LED
  pixels.show();
  delay(200);  
  pixels.setPixelColor(6, pixels.Color(255, 0, 255));  // Acende o sétimo LED 
  pixels.show();
  delay(200); 
  pixels.setPixelColor(7, pixels.Color(255, 192, 203));  // Acende o oitavo LED 
  pixels.show();
  delay(200); 
  pixels.setPixelColor(6, pixels.Color(255, 0, 255));  // Acende o sétimo LED 
  pixels.show();
  delay(200); 
  pixels.setPixelColor(5, pixels.Color(0, 255, 255));  // Acende o sexto LED
  pixels.show();
  delay(200); 
  pixels.setPixelColor(4, pixels.Color(0, 0, 255));  // Acende o quinto LED 
  pixels.show();
  delay(200);
  pixels.setPixelColor(3, pixels.Color(0, 255, 0));  // Acende o quarto LED
  pixels.show();
  delay(200);
  pixels.setPixelColor(2, pixels.Color(255, 255, 0));  // Acende o terceiro LED
  pixels.show();
  delay(200);
  pixels.setPixelColor(1, pixels.Color(255, 165, 0));  // Acende o segundo LED
  pixels.show();
  delay(200);   
  pixels.setPixelColor(0, pixels.Color(0, 200, 0));  // Acende o primeiro LED
  pixels.show();
  delay(500);  // Mantém o LED  por 0,5 segundo
}

/*
  Função: lerTeclado
  Descrição: 
    A função lerTeclado() é responsável por escanear as teclas do teclado matricial.
    Ela ativa uma linha por vez e verifica se alguma tecla nas colunas foi pressionada.
    Ao detectar uma tecla pressionada, a função exibe as informações do elemento selecionado 
    e aciona o LED correspondente à família do elemento.
*/
void lerTeclado() {
  bool algumaTeclaPressionada = false;  // Flag para verificar se alguma tecla foi pressionada

  // Varre as linhas e colunas para verificar quais teclas foram pressionadas
  for (int row = 0; row < 9; row++) {
    // Desativa todas as linhas
    for (int r = 0; r < 9; r++) digitalWrite(linhas[r], HIGH);  // Coloca todas as linhas em HIGH
    digitalWrite(linhas[row], LOW);  // Ativa uma linha por vez (nível baixo)
    delayMicroseconds(50);           // Espera para estabilizar o sinal

    // Varre as colunas para verificar se algum botão foi pressionado
    for (int col = 0; col < 18; col++) {
      int leitura = digitalRead(colunas[col]);

      // Se o botão foi pressionado (com diodo)
      if (leitura == LOW) {
        delay(10);  // Debounce simples
        if (digitalRead(colunas[col]) == LOW) { // Confirma leitura após debounce
          algumaTeclaPressionada = true;

          if (!keyPressed[row][col]) {
            keyPressed[row][col] = true;
            pressTime[row][col] = millis();
            lastActivity = millis();  // Atualiza o tempo da última atividade

            // Exibe o elemento selecionado e aciona os LEDs
            mostrarElemento(row, col, 1); // Exibe o nome e símbolo
            acionarLED(row, col); // Aciona o LED correspondente à família do elemento
            enviarDadosSerial(matrizPeriodica[row][col]); // Envia os dados do elemento via serial
          }

          // Exibe mais detalhes após 2 segundos de pressionamento
          if (millis() - pressTime[row][col] >= 2000) {
            mostrarElemento(row, col, 2); // Exibe número atômico e massa
          }
        }
      } else {
        keyPressed[row][col] = false;  // Libera a tecla quando não pressionada
      }
    }
  }

  // Retorna à mensagem padrão após 5 segundos de inatividade
  if (!algumaTeclaPressionada && (millis() - lastActivity >= idleTimeout)) {
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("QuimiKey!");
    lcd.setCursor(0, 1);
    lcd.print("Tecle um elemento");
    lastActivity = millis();  // Reinicia o contador de inatividade
    
    apagarLEDs();  // Apaga os LEDs ao voltar para a tela inicial
  }
}

/*
  Função: acionarLED
  Descrição: 
    Aciona o LED com base na família do elemento selecionado. 
    A função obtém a cor da família do elemento a partir da matriz de cores e acende os LEDs correspondentes.
  Parâmetros:
    - row: Linha da tabela periódica (índice da linha)
    - col: Coluna da tabela periódica (índice da coluna)
*/
void acionarLED(int row, int col) {
  const Elemento* e = matrizPeriodica[row][col];  // Obtém o elemento selecionado
  if (e == NULL) return;                       // Se o elemento for nulo, não faz nada

  // Obtém a cor da família do elemento e aciona o LED correspondente
  uint32_t corFamilia = coresFamilia[e->familia - 1];  // Ajuste do índice (familia vai de 1 a 9, mas o índice do vetor vai de 0 a 8)

  // Aciona a barra de LED com a cor correspondente à família
  for (int i = 0; i < NUM_PIXELS; i++) {
    pixels.setPixelColor(i, corFamilia);  // Define a cor para todos os LEDs
  }

  pixels.show();  // Atualiza os LEDs
}

/*
  Função: apagarLEDs
  Descrição: 
    Apaga todos os LEDs da barra NeoPixel. Esta função é chamada quando o sistema retorna à tela inicial.
*/
void apagarLEDs() {
  for (int i = 0; i < NUM_PIXELS; i++) {
    pixels.setPixelColor(i, pixels.Color(0, 0, 0));  // Apaga todos os LEDs
  }
  pixels.show();  // Atualiza os LEDs
}
