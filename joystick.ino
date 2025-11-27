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
  Este código é responsável pelo controle do joystick, permitindo navegar pela tabela periódica 
  e exibir os elementos no display LCD. O joystick é utilizado para mover pelas colunas e linhas da 
  tabela, e ao pressionar o botão do joystick, são exibidas informações adicionais sobre o elemento.
  
  Funções principais:
  - Inicializa o joystick e configura os pinos.
  - Permite a navegação pela tabela periódica com o joystick (movimentação horizontal e vertical).
  - Exibe informações do elemento no LCD com base na posição selecionada.
  - Mostra informações adicionais como o número atômico e massa ao pressionar o botão do joystick.
*/

#include <Arduino.h>            // Fornece funções essenciais para o funcionamento do código
#include "lcd_display.h"        // Funções do display
#include "elementos.h"          // Estruturas e dados do sistema
#include "joystick.h"           // Inclui o cabeçalho do joystick


// Pinos para o joystick
const int joystickX = A1;  // Pino VRX do joystick (eixo X - horizontal)
const int joystickY = A2;  // Pino VRY do joystick (eixo Y - vertical)
const int joystickButton = 52;  // Pino do botão do joystick (switch)

// Limites para os eixos X e Y
const int MIN_VAL = 350;  // Valor mínimo para ativar o movimento (ajuste conforme necessário)
const int MAX_VAL = 600;  // Valor máximo para ativar o movimento (ajuste conforme necessário)

// Variáveis para controlar o tempo de navegação
unsigned long lastMoveTime = 0;  // Armazena o tempo do último movimento
const unsigned long moveDelay = 500;  // Intervalo de segundos entre os movimentos (ms)

// Função para inicializar o joystick
void joystick_init() {
  /*
    A função joystick_init() é chamada uma vez, durante a inicialização do código. 
    Ela configura o botão do joystick como entrada com pull-up, permitindo detectar quando o botão é pressionado.
  */
  pinMode(joystickButton, INPUT_PULLUP);  // Configura o botão como entrada com pull-up
}

// Função para navegar pela tabela periódica usando o joystick
void navegarTabelaPeriodic(int &row, int &col) {
  /*
    A função navegarTabelaPeriodic() é chamada a cada iteração do loop e permite a navegação na tabela periódica 
    usando o joystick. As variáveis 'row' e 'col' são passadas por referência para atualizar as posições na tabela.
    
    - A leitura dos eixos X e Y do joystick é realizada utilizando analogRead().
    - A navegação é realizada de acordo com o valor de cada eixo, e o movimento é limitado pelos valores definidos de MIN_VAL e MAX_VAL.
    - A função também realiza a verificação de teclas "nulas" (NULL) e avança para o próximo elemento válido na tabela.
    - O tempo de movimento é controlado pela variável 'lastMoveTime' para garantir que a navegação não seja muito rápida.
  */
  int vrx = analogRead(joystickX);  // Leitura do eixo X (horizontal)
  int vry = analogRead(joystickY);  // Leitura do eixo Y (vertical)

  unsigned long currentMillis = millis();  // Tempo atual em milissegundos

  // Se o tempo desde o último movimento for superior ao delay (500 ms), mover
  if (currentMillis - lastMoveTime >= moveDelay) {
    // Se o eixo X for maior que o valor máximo, move para a direita
    if (vrx > MAX_VAL) {
      col++;  // Move para a próxima coluna
      if (col >= 18) col = 0;  // Volta para a primeira coluna se ultrapassar o número de colunas
      while (matrizPeriodica[row][col] == NULL) {  // Pula posições NULL
        col++;
        if (col >= 18) col = 0;  // Ajusta para o limite
      }
      mostrarElemento(row, col, 1);  // Exibe automaticamente nome e símbolo
    }
    // Se o eixo X for menor que o valor mínimo, move para a esquerda
    else if (vrx < MIN_VAL) {
      col--;  // Move para a coluna anterior
      if (col < 0) col = 17;  // Volta para a última coluna se ultrapassar o limite da coluna
      while (matrizPeriodica[row][col] == NULL) {  // Pula posições NULL
        col--;
        if (col < 0) col = 17;  // Ajusta para o limite
      }
      mostrarElemento(row, col, 1);  // Exibe automaticamente nome e símbolo
    }

    // Se o eixo Y for maior que o valor máximo, move para baixo
    if (vry > MAX_VAL) {
      row++;  // Move para a próxima linha
      if (row >= 9) row = 0;  // Volta para a primeira linha se ultrapassar o número de linhas
      while (matrizPeriodica[row][col] == NULL) {  // Pula posições NULL
        row++;
        if (row >= 9) row = 0;  // Ajusta para o limite
      }
      mostrarElemento(row, col, 1);  // Exibe automaticamente nome e símbolo
    }
    // Se o eixo Y for menor que o valor mínimo, move para cima
    else if (vry < MIN_VAL) {
      row--;  // Move para a linha anterior
      if (row < 0) row = 8;  // Volta para a última linha se ultrapassar o limite
      while (matrizPeriodica[row][col] == NULL) {  // Pula posições NULL
        row--;
        if (row < 0) row = 8;  // Ajusta para o limite
      }
      mostrarElemento(row, col, 1);  // Exibe automaticamente nome e símbolo
    }

    // Atualiza o tempo do último movimento
    lastMoveTime = currentMillis;
  }

  // Se o botão de seleção do joystick for pressionado, exibe número atômico e massa atômica
  if (digitalRead(joystickButton) == LOW) {
    mostrarElemento(row, col, 2);  // Exibe número atômico e massa atômica
  }
}
