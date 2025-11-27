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
  Este arquivo define a função responsável por enviar dados sobre o elemento químico
  selecionado pela comunicação serial. A função utiliza o protocolo serial para enviar
  os dados em formato JSON.
*/

#ifndef SERIAL_COMUNICACAO_H
#define SERIAL_COMUNICACAO_H

// Inclusão do arquivo de dados dos elementos químicos
#include "elementos.h"

// A função 'enviarDadosSerial' é usada para enviar as informações do elemento químico
// para a comunicação serial em formato JSON. Ela é chamada quando um elemento
// é selecionado no teclado matricial e exibe os dados na tela LCD.
// A função recebe um ponteiro para um elemento do tipo Elemento e envia as informações
// de nome, símbolo, número atômico, massa atômica, configuração eletrônica, família 
// e cor via serial, permitindo que o PC receba essas informações para processamento adicional.
void enviarDadosSerial(const Elemento* elemento);

#endif
