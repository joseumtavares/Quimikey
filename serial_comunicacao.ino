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
  O código implementa a função `enviarDadosSerial`, que formata e envia dados sobre um elemento químico 
  via comunicação serial (em formato JSON). A função coleta dados do elemento (como nome, símbolo, número atômico, etc.)
  e os envia para o dispositivo serial para posterior análise ou visualização no PC. O formato JSON facilita 
  a integração com outros sistemas e a leitura dos dados.
*/

#include "serial_comunicacao.h"  // Inclui o arquivo de cabeçalho 'serial_comunicacao.h' que contém a declaração da função 'enviarDadosSerial'.
#include "elementos.h"           // Inclui 'elementos.h' onde são definidos os dados sobre os elementos químicos, incluindo a estrutura Elemento.
#include <Arduino.h>             // Biblioteca base do Arduino que fornece as funcionalidades básicas, como Serial.print(), delay(), etc.

// Função para enviar os dados de um elemento químico via comunicação serial, em formato JSON.
// O objetivo é enviar as propriedades de um elemento químico para um PC ou outro dispositivo conectado via Serial.
void enviarDadosSerial(const Elemento* elemento) {
  // Verifica se o ponteiro para o elemento é nulo. Caso o ponteiro seja inválido (nulo), a função termina sem fazer nada.
  if (elemento == NULL) return; // Evita o envio de dados inválidos, se não houver um elemento válido.

  // Inicia a construção do JSON com a chave '{' para abrir o objeto.
  Serial.print("{");  // Inicia o objeto JSON com o caractere '{'.

  // Envia o nome do elemento, com a chave "nome", e o valor sendo o nome do elemento, extraído da estrutura 'elemento'.
  Serial.print("\"nome\":\""); Serial.print(elemento->nome); Serial.print("\",");

  // Envia o símbolo do elemento, com a chave "simbolo", e o valor sendo o símbolo do elemento, extraído da estrutura 'elemento'.
  Serial.print("\"simbolo\":\""); Serial.print(elemento->simbolo); Serial.print("\",");

  // Envia o número atômico do elemento, com a chave "numeroAtomico", e o valor sendo o número atômico do elemento.
  // O número atômico é um valor inteiro.
  Serial.print("\"numeroAtomico\":"); Serial.print(elemento->numeroAtomico); Serial.print(",");

  // Envia a massa atômica do elemento, com a chave "massaAtomica", e o valor sendo a massa atômica do elemento.
  // A massa atômica é enviada com 5 casas decimais para maior precisão.
  Serial.print("\"massaAtomica\":"); Serial.print(elemento->massaAtomica, 5); Serial.print(",");

  // Envia a configuração eletrônica do elemento, com a chave "configuracao", e o valor sendo a configuração eletrônica.
  Serial.print("\"configuracao\":\""); Serial.print(elemento->configEletronica); Serial.print("\",");

  // Envia a família química do elemento, com a chave "familia", e o valor sendo o número da família química.
  // As famílias são representadas por um número de 1 a 9, conforme a definição no código.
  Serial.print("\"familia\":"); Serial.print(elemento->familia); Serial.print(",");

  // Envia a cor associada ao elemento, com a chave "cor", e o valor sendo o código da cor, representando a família química.
  Serial.print("\"cor\":"); Serial.print(elemento->cor);

  // Finaliza o objeto JSON com a chave '}', indicando o fim dos dados.
  Serial.println("}");  // Envia o caractere '}' para fechar o objeto JSON e completar a transmissão dos dados.
}
