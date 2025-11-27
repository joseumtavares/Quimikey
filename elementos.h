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
  Técnico em Eletrônica Faculdade de Tecnolgia do SENAI-RS - 2015
  Projetista Eletrônico Sinbrax Tecnologia em Leds - Lagoa de Fora - Sombrio-SC
  Data: 19 de Novembro de 2025
  Descrição: 
    Este arquivo contém a definição da estrutura de dados que representa 
    cada elemento químico, bem como os códigos de suas famílias químicas, 
    associados à exibição de cores nos LEDs NeoPixel e as propriedades dos 
    elementos para uso em um projeto interativo baseado na tabela periódica.
*/

// Prevenção de múltiplas inclusões do arquivo para evitar redefinições
#ifndef ELEMENTOS_H
#define ELEMENTOS_H

// Inclusão da biblioteca do Arduino para tipos e funções essenciais
#include <Arduino.h>  // Biblioteca base do Arduino que fornece tipos e funções essenciais

// Definição das cores associadas às famílias químicas dos elementos
// Cada família corresponde a uma cor específica para o LED (RGB) que é associada ao elemento.


// Famílias químicas (códigos usados no projeto) e suas respectivas cores para LEDs
// Abaixo, o código da cor é configurado para cada família de elementos químicos.

// 1 = Metais alcalinos (Vermelho)
#define VERMELHO    pixels.Color(255, 0, 0)       // Cor para Metais alcalinos
// 2 = Metais alcalino-terrosos (Laranja)
#define LARANJA     pixels.Color(255, 165, 0)     // Cor para Metais alcalino-terrosos
// 3 = Metais de transição (Amarelo)
#define AMARELO     pixels.Color(255, 255, 0)     // Cor para Metais de transição
// 4 = Metais pós-transição (Verde)
#define VERDE       pixels.Color(0, 255, 0)       // Cor para Metais pós-transição
// 5 = Semimetais (Azul)
#define AZUL        pixels.Color(0, 0, 255)       // Cor para Semimetais
// 6 = Não metais (Ciano)
#define CIANO       pixels.Color(0, 255, 255)     // Cor para Não metais
// 7 = Gases nobres (Roxo)
#define ROXO         pixels.Color(255, 0, 255)     // Cor para Gases nobres
// 8 = Lantanídeos (Rosa)
#define ROSA        pixels.Color(255, 192, 203)   // Cor para Lantanídeos
// 9 = Actinídeos (Magenta)
#define MAGENTA     pixels.Color(255, 105, 180)   // Cor para Actinídeos


// Estrutura de dados que representa cada elemento químico
// Esta estrutura é utilizada para armazenar as propriedades de cada elemento 
// e facilitar o acesso aos dados no programa. Cada elemento é caracterizado por:
// - Número: O número do elemento na tabela periódica (como "1", "2", etc.)
// - Nome: O nome completo do elemento químico (como "Hidrogênio", "Oxigênio", etc.)
// - Símbolo: O símbolo do elemento (como "H", "He", "O", etc.)
// - Número Atômico: O número atômico do elemento (ex: 1 para Hidrogênio)
// - Massa Atômica: A massa atômica do elemento, que é um valor aproximado (ex: 1.0079 para Hidrogênio)
// - Configuração Eletrônica: A configuração dos elétrons no átomo do elemento (ex: "1s^1")
// - Família: A família química do elemento (de 1 a 9, de acordo com as famílias definidas acima)
// - Cor: A cor associada à família do elemento, usada para exibir no LED NeoPixel

struct Elemento {
  const char* numero;           // Número do elemento (ex: "1", "2", etc.)
  const char* nome;             // Nome do elemento (ex: "Hidrogênio", "Oxigênio", etc.)
  const char* simbolo;          // Símbolo do elemento (ex: "H", "He", "O", etc.)
  int numeroAtomico;            // Número atômico do elemento (ex: 1 para Hidrogênio)
  float massaAtomica;           // Massa atômica do elemento (ex: 1.0079 para Hidrogênio)
  const char* configEletronica; // Configuração eletrônica do elemento (ex: "1s^1")
  uint8_t familia;              // Família química do elemento (1 a 9, conforme as definições de famílias)
  uint8_t cor;                  // Cor associada à família do elemento (utilizada para LEDs NeoPixel)
};

// Declaração de uma matriz 9x18 que representa a tabela periódica dos elementos
// Cada posição da matriz contém um ponteiro para um objeto Elemento que representa um elemento químico.
// O índice da matriz é usado para acessar um elemento específico na tabela periódica.

extern const Elemento* matrizPeriodica[9][18];  // A tabela periódica contém 9 linhas e 18 colunas de elementos

#endif  // Fim da definição do arquivo para prevenir múltiplas inclusões
