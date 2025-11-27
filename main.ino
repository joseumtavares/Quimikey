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
  Técnico em Eletrônica Faculdade de Técnologia do SENAI-RS - 2015
  Projetista Eletrônico Sinbrax Técnologia em Leds - Lagoa de Fora - Sombrio-SC
  Data: 19 de Novembro de 2025
  Descrição: 
  Este código é a base do sistema Quimikey, que simula a interação com uma tabela periódica em um display LCD. 
  O sistema utiliza um teclado matricial para selecionar elementos químicos, exibindo informações sobre 
  o elemento selecionado no LCD e enviando dados pela comunicação serial. Este projeto também incorpora 
  LEDs RGB (NeoPixel) para indicar a família química de cada elemento.

  O código realiza as seguintes funções:
  - Inicializa a comunicação Serial com o PC.
  - Prepara o display LCD para exibição.
  - Configura o teclado matricial para leitura das teclas.
  - Lê as teclas pressionadas e exibe as informações dos elementos.
*/

// Inclusão das bibliotecas necessárias
#include <Wire.h>               // Biblioteca I2C (comunicação no barramento Wire)
#include <LiquidCrystal_I2C.h>  // Driver do LCD via I2C (mostra texto no display)
#include "lcd_display.h"        // Funções do display
#include "keypad.h"             // Funções do teclado matricial
#include "elementos.h"          // Estruturas e dados do sistema
#include "serial_comunicacao.h" // Envio e recebimento via Serial
#include "joystick.h"           // Inclui o cabeçalho do joystick

//int row = 0, col = 0;  // Posições iniciais na tabela periódica

// Função de inicialização
void setup() {
   /*
    A função setup() é chamada uma vez, no início do código. 
    Ela configura as funções essenciais e inicializa os dispositivos.
    
    - Serial.begin(9600): Inicializa a comunicação serial com o PC na velocidade de 9600 bps. 
    A comunicação serial será utilizada para enviar dados ao PC.
    
    - lcd_init(): Inicializa o display LCD e exibe mensagens iniciais de boas-vindas e instruções.
    
    - keypad_init(): Inicializa o teclado matricial para permitir que o sistema leia as teclas pressionadas.
    
    - joystick_init(): Inicializa o joystick, configurando os pinos necessários para sua leitura.
  */
  Serial.begin(9600);  // Inicia a comunicação serial com o PC
  lcd_init();          // Inicializa o display LCD
  keypad_init();       // Inicializa o teclado matricial
  joystick_init();     // Inicializa o joystick (configura os pinos)

}

// Função loop
void loop() {
  static int row = 0, col = 0;  // Posições iniciais na tabela periódica
  /*
    A função loop() é chamada repetidamente. 
    Ela realiza a leitura do teclado e toma ações com base nas teclas pressionadas.
    
    - navegarTabelaPeriodic(): Chama a função para navegar pela tabela periódica com o joystick.
    
    - lerTeclado(): Essa função verifica as teclas pressionadas no teclado matricial e, 
    quando uma tecla é pressionada, exibe as informações do elemento correspondente 
    no display LCD e envia os dados pela comunicação serial.
  */
  navegarTabelaPeriodic(row, col);  // Navega pela tabela com o joystick

  lerTeclado();  // Lê o teclado e exibe informações no LCD e serial

  delay(50);  // Atraso para evitar leitura excessiva e problemas no display
}

