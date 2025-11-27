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
  Este código é responsável pelo controle do LCD, exibindo informações dos elementos químicos 
  com base nas posições da tabela periódica. Ele também envia dados em formato JSON para a comunicação serial.
  */

// Inclusão das bibliotecas necessárias para controlar o LCD e comunicar via I2C
#include <Arduino.h>  // Biblioteca principal do Arduino
#include <Wire.h>     // Para comunicação I2C
#include <LiquidCrystal_I2C.h>  // Para controlar o LCD via I2C
#include "lcd_display.h"  // Funções específicas para o controle do LCD
#include "elementos.h"  // Contém os dados dos elementos químicos
#include "serial_comunicacao.h"  // Para enviar dados JSON via serial

// Definindo o objeto LCD com o endereço I2C, e 16 colunas e 2 linhas
LiquidCrystal_I2C lcd(0x27, 16, 2);  // O endereço I2C 0x27 e a configuração de 16x2

/*
  Função: lcd_init
  Descrição: 
    Esta função inicializa o display LCD, acende o backlight, limpa a tela e exibe as mensagens de boas-vindas.
    A função é chamada apenas uma vez no início do programa para configurar o display.
  Lógica:
    - Inicializa o LCD e o backlight.
    - Exibe uma mensagem inicial "Bem-vindo!" e aguarda por 2 segundos.
    - Após isso, limpa a tela e exibe "Quimikey!" e "Tecle um elemento" na segunda linha.
*/
void lcd_init() {
  lcd.init();  // Inicializa o display LCD
  lcd.backlight();  // Liga o backlight (luz de fundo) do LCD
  lcd.clear();  // Limpa qualquer informação na tela

  lcd.setCursor(0, 0);  // Move o cursor para a primeira linha, primeira coluna
  lcd.print("Bem-vindo!");  // Exibe "Bem-vindo!" na tela
  delay(2000);  // Aguarda 2 segundos para que o usuário veja a mensagem

  lcd.clear();  // Limpa a tela novamente
  lcd.setCursor(0, 0);  // Volta o cursor para a primeira linha, primeira coluna
  lcd.print("Quimikey!");  // Exibe "Quimikey!" na tela
  lcd.setCursor(0, 1);  // Muda para a segunda linha
  lcd.print("Tecle um elemento");  // Exibe instruções
  delay(2000);  // Aguarda 2 segundos antes de continuar
}

/*
  Função: mostrarElemento
  Descrição: 
    Exibe as informações do elemento selecionado no display LCD. Dependendo do tipo, exibe diferentes informações.
    Tipo 1: Exibe nome e símbolo do elemento.
    Tipo 2: Exibe número atômico e massa atômica.
  Lógica:
    - Verifica se o elemento existe na posição dada.
    - Exibe as informações do elemento no LCD.
    - Envia os dados via comunicação serial em formato JSON.
    - Caso o elemento não seja encontrado, exibe uma mensagem de erro.
  Parâmetros:
    - row: Linha da tabela periódica (índice da linha)
    - col: Coluna da tabela periódica (índice da coluna)
    - tipo: Tipo de informação a ser exibida (1 ou 2)
*/
void mostrarElemento(int row, int col, int tipo) {
  const Elemento* e = matrizPeriodica[row][col];  // Acessa o elemento na posição row, col

  if (e == NULL) {  // Se o elemento for nulo (não existe na posição)
    lcd.clear();  // Limpa o display
    lcd.setCursor(0, 0);  // Define o cursor para a primeira linha, primeira coluna
    lcd.print("Posicao vazia");  // Exibe mensagem de erro
    Serial.println("{\"erro\":\"Posicao vazia\"}");  // Envia erro via serial
    return;  // Retorna para não continuar a execução
  }

  lcd.clear();  // Limpa a tela antes de exibir as novas informações
  lcd.setCursor(0, 0);  // Define o cursor para a primeira linha, primeira coluna

  if (tipo == 1) {  // Tipo 1: Exibe nome e símbolo
    lcd.print("Nome: ");  // Exibe a palavra "Nome: "
    lcd.print(e->nome);  // Exibe o nome do elemento (ex: Hidrogênio)
    lcd.setCursor(0, 1);  // Muda o cursor para a segunda linha
    lcd.print("Simbolo: ");  // Exibe a palavra "Simbolo: "
    lcd.print(e->simbolo);  // Exibe o símbolo do elemento (ex: H)

    // Envia os dados do elemento como JSON pela comunicação serial
    enviarDadosSerial(e);
  } 
  else if (tipo == 2) {  // Tipo 2: Exibe número atômico e massa atômica
    lcd.print("Num: ");  // Exibe a palavra "Num: "
    lcd.print(e->numeroAtomico);  // Exibe o número atômico do elemento
    lcd.setCursor(0, 1);  // Muda para a segunda linha
    lcd.print("Massa: ");  // Exibe a palavra "Massa: "
    lcd.print(e->massaAtomica, 3);  // Exibe a massa atômica com 3 casas decimais

    // Envia os dados do elemento como JSON pela comunicação serial
    enviarDadosSerial(e);
  }
}
