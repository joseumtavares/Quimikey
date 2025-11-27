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

/* Definição do arquivo de cabeçalho para controle do display LCD via I2C */

// Prevenção de múltiplas inclusões do arquivo
#ifndef LCD_DISPLAY_H
#define LCD_DISPLAY_H

// Inclusão da biblioteca base do Arduino
#include <Arduino.h>

// Inclusão da biblioteca LiquidCrystal_I2C que permite controlar o display LCD via protocolo I2C
#include <LiquidCrystal_I2C.h>

// Declaração de um objeto global `lcd` que é utilizado para controlar o display LCD.
// O objeto é criado em outro arquivo, e essa declaração permite usá-lo globalmente.
extern LiquidCrystal_I2C lcd;  // 🔹 Declaração global (sem recriar o objeto)

// Função para inicializar o display LCD
// Esta função é responsável por configurar o display LCD, ligar a luz de fundo 
// e exibir as mensagens iniciais de boas-vindas e instruções.
void lcd_init();

// Função para exibir informações sobre o elemento selecionado
// Esta função recebe as coordenadas do elemento na tabela periódica (linha e coluna) 
// e o tipo de exibição desejado (informações básicas ou completas).
// O tipo 1 exibe o nome e símbolo do elemento, enquanto o tipo 2 exibe número atômico e massa atômica.
void mostrarElemento(int row, int col, int tipo);

// Função para limpar o display LCD
// A função `lcd_clear` é uma função simples para limpar o conteúdo exibido no display
// e preparar o LCD para a exibição de novas informações.
void lcd_clear();

// Função para imprimir um texto em uma linha específica do display LCD
// Essa função recebe como parâmetros o número da linha e o texto a ser exibido na linha.
// O texto é passado como uma referência constante para evitar cópias desnecessárias e melhorar a performance.
void lcd_printLine(int linha, const String &texto);

#endif  // Fim da proteção contra múltiplas inclusões do arquivo
