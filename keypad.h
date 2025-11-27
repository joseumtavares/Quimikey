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
  Este arquivo contém a definição das funções necessárias para a leitura de um teclado matricial
  utilizado para interagir com o sistema Quimikey. Ele permite a interação com os elementos da tabela periódica,
  acionando LEDs e exibindo informações no display LCD.
  As funções permitem inicializar o teclado, ler teclas pressionadas e processar comandos via Serial.
*/

/* Prevenção de múltiplas inclusões do arquivo
   Garante que o conteúdo do arquivo será incluído apenas uma vez, evitando conflitos de definição */
#ifndef KEYPAD_H
#define KEYPAD_H

// Inclusão do arquivo lcd_display.h, que é necessário para controlar o display LCD
// As funções de mostrar informações no LCD, como `mostrarElemento()`, são usadas após a leitura do teclado
#include "lcd_display.h"  // Inclui lcd_display.h para usar lcd, mostrarElemento()

// Inclusão da biblioteca do Arduino que fornece funções e tipos essenciais para o funcionamento do código
#include <Arduino.h>

/* Definição das matrizes de pinos do teclado:
   - Linhas (9): O teclado possui 9 linhas, que são configuradas como saídas.
   - Colunas (18): O teclado possui 18 colunas, que são configuradas como entradas com pull-up interno.
   Essas matrizes são usadas para mapear as conexões físicas do teclado ao Arduino. */
extern const int linhas[9];  // Matrizes de pinos para as 9 linhas do teclado matricial
extern const int colunas[18];  // Matrizes de pinos para as 18 colunas do teclado matricial

/* Função: keypad_init
   Descrição:
   Inicializa o teclado matricial, configurando os pinos das linhas como saídas e as colunas como entradas com pull-up.
   Além disso, garante que os pinos do teclado estejam prontos para leitura. 
   O estado inicial das linhas será desativado (HIGH), e as colunas usarão o pull-up interno do Arduino.
*/
void keypad_init();

/* Função: lerTeclado
   Descrição:
   Realiza a leitura do teclado matricial. Para isso, a função varre as linhas, ativando uma linha por vez (definindo-a como LOW) 
   e verifica as colunas para identificar se algum botão foi pressionado. Caso um botão seja pressionado, 
   a função toma as ações necessárias, como exibir as informações do elemento na tela LCD e atualizar os LEDs.
   A leitura é feita com um debounce simples para garantir que múltiplos eventos de pressionamento não sejam registrados.
*/
void lerTeclado();

/* Função: lerSerial
   Descrição:
   Permite que o sistema leia comandos recebidos pela comunicação Serial. 
   Essa função pode ser usada para processar entradas via monitor serial, como comandos de controle ou ajustes no sistema.
*/
void lerSerial();

#endif  // Fim da proteção contra múltiplas inclusões do arquivo
