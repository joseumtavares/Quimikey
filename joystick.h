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
  Este arquivo contém a interface para controlar a navegação na tabela periódica usando um joystick.
  O sistema permite navegar entre os elementos da tabela periódica, utilizando o joystick para 
  mover as seleções e exibir as informações dos elementos no LCD.
  
  Funções principais:
  - Inicializa o joystick e configura os pinos para controle.
  - Permite navegar pela tabela periódica usando o joystick.
*/

#ifndef JOYSTICK_H 
#define JOYSTICK_H

#include <Arduino.h>
#include "elementos.h"   // Para acessar os dados dos elementos químicos
#include "lcd_display.h"  // Para exibir os elementos no LCD

  // Declaração das funções utilizadas no joystick.ino

  /*
    Função para inicializar o joystick:
    Configura os pinos necessários para o controle do joystick, 
    inicializa as variáveis associadas à leitura do joystick e 
    prepara o sistema para o uso do joystick na navegação pela tabela periódica.
  */
  void joystick_init();

  /*
    Função para navegar pela tabela periódica usando o joystick:
    A função recebe referências de linha (row) e coluna (col) e permite 
    ao usuário navegar entre os elementos da tabela periódica, atualizando 
    as variáveis de posição conforme a direção do joystick.
    O joystick será utilizado para selecionar um elemento, e a função 
    atualizará a posição na tabela e exibirá o novo elemento no LCD.
  */
  void navegarTabelaPeriodic(int &row, int &col);

#endif  // JOYSTICK_H
