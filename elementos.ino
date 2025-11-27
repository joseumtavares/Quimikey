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
  Este código faz parte do sistema Quimikey, que simula a interação com a tabela periódica 
  utilizando um display LCD, teclado matricial  para indicar a família química de 
  cada elemento. O sistema permite que os usuários selecionem elementos, exibam suas propriedades
  no LCD e comunicação Serial.
  
  O código realiza as seguintes funções:
  - Inicializa a comunicação Serial com o PC.
  - Prepara o display LCD para exibição.
  - Configura o teclado matricial para ler as teclas pressionadas.
  - Lê as teclas pressionadas e exibe as informações dos elementos na tela e na serial.
  - Utiliza LEDs RGB (NeoPixel) para mostrar a cor da família do elemento selecionado.

  Bibliotecas Utilizadas:
  - elementos.h: 
*/
#include "elementos.h" // Biblioteca para comunicação I2C (Wire protocol)
#include <Arduino.h>   // Inclui a biblioteca Arduino para reconhecer pinMode(), INPUT, OUTPUT


// =================================//
// Definições dos códigos numéricos //
// =================================//
// A seguir, as famílias químicas são definidas com números de 1 a 9 que representam as 
// famílias de elementos químicos na tabela periódica. Cada número está associado a uma cor
// que será utilizada para acionar os LEDs correspondentes ao pressionar um botão no teclado.
  
// Famílias químicas (códigos usados no projeto):
// 1 = Metais alcalinos (Vermelho)
// 2 = Metais alcalino-terrosos (Laranja)
// 3 = Metais de transição (Amarelo)
// 4 = Metais pós-transição (Verde)
// 5 = Semimetais (Azul)
// 6 = Não metais (Ciano)
// 7 = Gases nobres (Roxo)
// 8 = Lantanídeos (Rosa)
// 9 = Actinídeos (Magenta)

// Cada elemento é associado a um número específico, símbolo, nome, número atômico, 
// configuração eletrônica e família. Além disso, a cor da família também é armazenada
// para utilização no controle dos LEDs RGB e comunicação serial.


// ==================
// Linha 1 – H → He
// ==================
// Definição dos elementos da primeira linha da tabela periódica, H (Hidrogênio) e He (Hélio).
// Eles têm seus dados estruturados na estrutura Elemento, com valores como número atômico,
// símbolo, nome, massa atômica, configuração eletrônica e a família a qual pertencem.
const Elemento H  = {"1", "Hidrogenio", "H", 1, 1.0079, "1s^1", 6, 6};
const Elemento He = {"2", "Helio", "He", 2, 4.0026, "1s^2", 7, 7};

// ==================
// Linha 2 – Li → Ne
// ==================
const Elemento Li = {"3", "Litio", "Li", 3, 6.94, "[He] 2s^1", 1, 1};
const Elemento Be = {"4", "Berilio", "Be", 4, 9.0122, "[He] 2s^2", 2, 2};
const Elemento B  = {"5", "Boro", "B", 5, 10.81, "[He] 2s^2 2p^1", 5, 5};
const Elemento C  = {"6", "Carbono", "C", 6, 12.011, "[He] 2s^2 2p^2", 6, 6};
const Elemento N  = {"7", "Nitrogenio", "N", 7, 14.007, "[He] 2s^2 2p^3", 6, 6};
const Elemento O  = {"8", "Oxigenio", "O", 8, 15.999, "[He] 2s^2 2p^4", 6, 6};
const Elemento F  = {"9", "Fluor", "F", 9, 18.998, "[He] 2s^2 2p^5", 6, 6};
const Elemento Ne = {"10", "Neonio", "Ne", 10, 20.180, "[He] 2s^2 2p^6", 7, 7};

// ==================
// Linha 3 – Na → Ar
// ==================
const Elemento Na = {"11", "Sodio", "Na", 11, 22.989, "[Ne] 3s^1", 1, 1};
const Elemento Mg = {"12", "Magnesio", "Mg", 12, 24.305, "[Ne] 3s^2", 2, 2};
const Elemento Al = {"13", "Aluminio", "Al", 13, 26.982, "[Ne] 3s^2 3p^1", 4, 4};
const Elemento Si = {"14", "Silicio", "Si", 14, 28.085, "[Ne] 3s^2 3p^2", 5, 5};
const Elemento P  = {"15", "Fosforo", "P", 15, 30.974, "[Ne] 3s^2 3p^3", 6, 6};
const Elemento S  = {"16", "Enxofre", "S", 16, 32.06, "[Ne] 3s^2 3p^4", 6, 6};
const Elemento Cl = {"17", "Cloro", "Cl", 17, 35.45, "[Ne] 3s^2 3p^5", 6, 6};
const Elemento Ar = {"18", "Argonio", "Ar", 18, 39.948, "[Ne] 3s^2 3p^6", 7, 7};

// =================
// Linha 4 – K → Kr
// =================
const Elemento K  = {"19", "Potassio", "K", 19, 39.098, "[Ar] 4s^1", 1, 1};
const Elemento Ca = {"20", "Calcio", "Ca", 20, 40.078, "[Ar] 4s^2", 2, 2};
const Elemento Sc = {"21", "Escandio", "Sc", 21, 44.956, "[Ar] 3d^1 4s^2", 3, 3};
const Elemento Ti = {"22", "Titanio", "Ti", 22, 47.867, "[Ar] 3d^2 4s^2", 3, 3};
const Elemento V  = {"23", "Vanadio", "V", 23, 50.941, "[Ar] 3d^3 4s^2", 3, 3};
const Elemento Cr = {"24", "Cromo", "Cr", 24, 51.996, "[Ar] 3d^5 4s^1", 3, 3};
const Elemento Mn = {"25", "Manganes", "Mn", 25, 54.938, "[Ar] 3d^5 4s^2", 3, 3};
const Elemento Fe = {"26", "Ferro", "Fe", 26, 55.845, "[Ar] 3d^6 4s^2", 3, 3};
const Elemento Co = {"27", "Cobalto", "Co", 27, 58.933, "[Ar] 3d^7 4s^2", 3, 3};
const Elemento Ni = {"28", "Niquel", "Ni", 28, 58.693, "[Ar] 3d^8 4s^2", 3, 3};
const Elemento Cu = {"29", "Cobre", "Cu", 29, 63.546, "[Ar] 3d^10 4s^1", 3, 3};
const Elemento Zn = {"30", "Zinco", "Zn", 30, 65.38, "[Ar] 3d^10 4s^2", 3, 3};
const Elemento Ga = {"31", "Galio", "Ga", 31, 69.723, "[Ar] 3d^10 4s^2 4p^1", 4, 4};
const Elemento Ge = {"32", "Germanio", "Ge", 32, 72.630, "[Ar] 3d^10 4s^2 4p^2", 5, 5};
const Elemento As = {"33", "Arsenio", "As", 33, 74.922, "[Ar] 3d^10 4s^2 4p^3", 5, 5};
const Elemento Se = {"34", "Selenio", "Se", 34, 78.971, "[Ar] 3d^10 4s^2 4p^4", 6, 6};
const Elemento Br = {"35", "Bromo", "Br", 35, 79.904, "[Ar] 3d^10 4s^2 4p^5", 6, 6};
const Elemento Kr = {"36", "Kriptonio", "Kr", 36, 83.798, "[Ar] 3d^10 4s^2 4p^6", 7, 7};

// ==================
// Linha 5 – Rb → Xe
// ==================
const Elemento Rb = {"37", "Rubidio", "Rb", 37, 85.468, "[Kr] 5s^1", 1, 1};
const Elemento Sr = {"38", "Estroncio", "Sr", 38, 87.62, "[Kr] 5s^2", 2, 2};
const Elemento Y  = {"39", "Itrio", "Y", 39, 88.905, "[Kr] 4d^1 5s^2", 3, 3};
const Elemento Zr = {"40", "Zirconio", "Zr", 40, 91.224, "[Kr] 4d^2 5s^2", 3, 3};
const Elemento Nb = {"41", "Niobio", "Nb", 41, 92.906, "[Kr] 4d^4 5s^1", 3, 3};
const Elemento Mo = {"42", "Molibdenio", "Mo", 42, 95.95, "[Kr] 4d^5 5s^1", 3, 3};
const Elemento Tc = {"43", "Tecnecio", "Tc", 43, 98.0, "[Kr] 4d^5 5s^2", 3, 3};
const Elemento Ru = {"44", "Rutênio", "Ru", 44, 101.07, "[Kr] 4d^7 5s^1", 3, 3};
const Elemento Rh = {"45", "Rodio", "Rh", 45, 102.91, "[Kr] 4d^8 5s^1", 3, 3};
const Elemento Pd = {"46", "Paladio", "Pd", 46, 106.42, "[Kr] 4d^10", 3, 3};
const Elemento Ag = {"47", "Prata", "Ag", 47, 107.87, "[Kr] 4d^10 5s^1", 3, 3};
const Elemento Cd = {"48", "Cadmio", "Cd", 48, 112.41, "[Kr] 4d^10 5s^2", 3, 3};
const Elemento In = {"49", "Indio", "In", 49, 114.82, "[Kr] 4d^10 5s^2 5p^1", 4, 4};
const Elemento Sn = {"50", "Estanho", "Sn", 50, 118.71, "[Kr] 4d^10 5s^2 5p^2", 4, 4};
const Elemento Sb = {"51", "Antimonio", "Sb", 51, 121.76, "[Kr] 4d^10 5s^2 5p^3", 5, 5};
const Elemento Te = {"52", "Telurio", "Te", 52, 127.60, "[Kr] 4d^10 5s^2 5p^4", 5, 5};
const Elemento I  = {"53", "Iodo", "I", 53, 126.90, "[Kr] 4d^10 5s^2 5p^5", 6, 6};
const Elemento Xe = {"54", "Xenonio", "Xe", 54, 131.29, "[Kr] 4d^10 5s^2 5p^6", 7, 7};

// ==================
// Linha 6 – Cs → Rn
// ==================
const Elemento Cs = {"55", "Cesio", "Cs", 55, 132.91, "[Xe] 6s^1", 1, 1};
const Elemento Ba = {"56", "Bario", "Ba", 56, 137.33, "[Xe] 6s^2", 2, 2};
const Elemento Lu = {"57", "Lutecio", "Lu", 71, 174.97, "[Xe] 4f^14 5d^1 6s^2", 8, 8};
const Elemento Hf = {"58", "Hafnio", "Hf", 72, 178.49, "[Xe] 4f^14 5d^2 6s^2", 3, 3};
const Elemento Ta = {"59", "Tantalo", "Ta", 73, 180.95, "[Xe] 4f^14 5d^3 6s^2", 3, 3};
const Elemento W  = {"60", "Tungstenio", "W", 74, 183.84, "[Xe] 4f^14 5d^4 6s^2", 3, 3};
const Elemento Re = {"61", "Renio", "Re", 75, 186.21, "[Xe] 4f^14 5d^5 6s^2", 3, 3};
const Elemento Os = {"62", "Osmo", "Os", 76, 190.23, "[Xe] 4f^14 5d^6 6s^2", 3, 3};
const Elemento Ir = {"63", "Iridio", "Ir", 77, 192.22, "[Xe] 4f^14 5d^7 6s^2", 3, 3};
const Elemento Pt = {"64", "Platina", "Pt", 78, 195.08, "[Xe] 4f^14 5d^9 6s^1", 3, 3};
const Elemento Au = {"65", "Ouro", "Au", 79, 196.97, "[Xe] 4f^14 5d^10 6s^1", 3, 3};
const Elemento Hg = {"66", "Mercurio", "Hg", 80, 200.59, "[Xe] 4f^14 5d^10 6s^2", 3, 3};
const Elemento Tl = {"67", "Tali", "Tl", 81, 204.38, "[Xe] 4f^14 5d^10 6s^2 6p^1", 4, 4};
const Elemento Pb = {"68", "Chumbo", "Pb", 82, 207.2, "[Xe] 4f^14 5d^10 6s^2 6p^2", 4, 4};
const Elemento Bi = {"69", "Bismuto", "Bi", 83, 208.98, "[Xe] 4f^14 5d^10 6s^2 6p^3", 4, 4};
const Elemento Po = {"70", "Polonio", "Po", 84, 209, "[Xe] 4f^14 5d^10 6s^2 6p^4", 5, 5};
const Elemento At = {"71", "Astato", "At", 85, 210, "[Xe] 4f^14 5d^10 6s^2 6p^5", 6, 6};
const Elemento Rn = {"72", "Radonio", "Rn", 86, 222, "[Xe] 4f^14 5d^10 6s^2 6p^6", 7, 7};

// ==================
// Linha 7 – Fr → Og
// ==================
const Elemento Fr = {"73", "Francio", "Fr", 87, 223, "[Rn] 7s^1", 1, 1};
const Elemento Ra = {"74", "Radio", "Ra", 88, 226, "[Rn] 7s^2", 2, 2};
const Elemento Lr = {"75", "Laurencio", "Lr", 103, 262.11, "[Rn] 5f^14 7s^2 7p^1", 9, 9};
const Elemento Rf = {"76", "Rutherfordio", "Rf", 104, 267, "[Rn] 5f^14 6d^2 7s^2", 3, 3};
const Elemento Db = {"77", "Dubnio", "Db", 105, 270, "[Rn] 5f^14 6d^3 7s^2", 3, 3};
const Elemento Sg = {"78", "Seaborgio", "Sg", 106, 271, "[Rn] 5f^14 6d^4 7s^2", 3, 3};
const Elemento Bh = {"79", "Bohrium", "Bh", 107, 270, "[Rn] 5f^14 6d^5 7s^2", 3, 3};
const Elemento Hs = {"80", "Hassio", "Hs", 108, 277, "[Rn] 5f^14 6d^6 7s^2", 3, 3};
const Elemento Mt = {"81", "Meitnerio", "Mt", 109, 276, "[Rn] 5f^14 6d^7 7s^2", 3, 3};
const Elemento Ds = {"82", "Darmstadio", "Ds", 110, 281, "[Rn] 5f^14 6d^9 7s^1", 3, 3};
const Elemento Rg = {"83", "Roentgenio", "Rg", 111, 282, "[Rn] 5f^14 6d^10 7s^1", 3, 3};
const Elemento Cn = {"84", "Copernicio", "Cn", 112, 285, "[Rn] 5f^14 6d^10 7s^2", 3, 3};
const Elemento Nh = {"85", "Nihonio", "Nh", 113, 286, "[Rn] 5f^14 6d^10 7s^2 7p^1", 4, 4};
const Elemento Fl = {"86", "Flerovio", "Fl", 114, 289, "[Rn] 5f^14 6d^10 7s^2 7p^2", 4, 4};
const Elemento Mc = {"87", "Moscovio", "Mc", 115, 290, "[Rn] 5f^14 6d^10 7s^2 7p^3", 4, 4};
const Elemento Lv = {"88", "Livermorio", "Lv", 116, 293, "[Rn] 5f^14 6d^10 7s^2 7p^4", 5, 5};
const Elemento Ts = {"89", "Tenessino", "Ts", 117, 294, "[Rn] 5f^14 6d^10 7s^2 7p^5", 6, 6};
const Elemento Og = {"90", "Oganessonio", "Og", 118, 294, "[Rn] 5f^14 6d^10 7s^2 7p^6", 7, 7};

// ======================
// Linha 8 – Lantanídeos
// ======================
const Elemento La = {"91", "Lantanio", "La", 57, 138.91, "[Xe] 5d^1 6s^2", 8, 8};
const Elemento Ce = {"92", "Cerio", "Ce", 58, 140.12, "[Xe] 4f^1 5d^1 6s^2", 8, 8};
const Elemento Pr = {"93", "Praseodimio", "Pr", 59, 140.91, "[Xe] 4f^3 6s^2", 8, 8};
const Elemento Nd = {"94", "Neodimio", "Nd", 60, 144.24, "[Xe] 4f^4 6s^2", 8, 8};
const Elemento Pm = {"95", "Promecio", "Pm", 61, 145, "[Xe] 4f^5 6s^2", 8, 8};
const Elemento Sm = {"96", "Samario", "Sm", 62, 150.36, "[Xe] 4f^6 6s^2", 8, 8};
const Elemento Eu = {"97", "Europio", "Eu", 63, 151.96, "[Xe] 4f^7 6s^2", 8, 8};
const Elemento Gd = {"98", "Gadolinio", "Gd", 64, 157.25, "[Xe] 4f^7 5d^1 6s^2", 8, 8};
const Elemento Tb = {"99", "Terbio", "Tb", 65, 158.93, "[Xe] 4f^9 6s^2", 8, 8};
const Elemento Dy = {"100", "Disprosio", "Dy", 66, 162.50, "[Xe] 4f^10 6s^2", 8, 8};
const Elemento Ho = {"101", "Holmio", "Ho", 67, 164.93, "[Xe] 4f^11 6s^2", 8, 8};
const Elemento Er = {"102", "Erbio", "Er", 68, 167.26, "[Xe] 4f^12 6s^2", 8, 8};
const Elemento Tm = {"103", "Tulio", "Tm", 69, 168.93, "[Xe] 4f^13 6s^2", 8, 8};
const Elemento Yb = {"104", "Iterbio", "Yb", 70, 173.04, "[Xe] 4f^14 6s^2", 8, 8};
const Elemento Lu2 = {"105", "Lutecio", "Lu", 71, 174.97, "[Xe] 4f^14 5d^1 6s^2", 8, 8};

// =====================
// Linha 9 – Actinídeos
// =====================
const Elemento Ac = {"106", "Actinio", "Ac", 89, 227.03, "[Rn] 6d^1 7s^2", 9, 9};
const Elemento Th = {"107", "Torio", "Th", 90, 232.04, "[Rn] 6d^2 7s^2", 9, 9};
const Elemento Pa = {"108", "Protactinio", "Pa", 91, 231.04, "[Rn] 5f^2 6d^1 7s^2", 9, 9};
const Elemento U  = {"109", "Uranio", "U", 92, 238.03, "[Rn] 5f^3 6d^1 7s^2", 9, 9};
const Elemento Np = {"110", "Netunio", "Np", 93, 237.05, "[Rn] 5f^4 6d^1 7s^2", 9, 9};
const Elemento Pu = {"111", "Plutonio", "Pu", 94, 244.06, "[Rn] 5f^6 7s^2", 9, 9};
const Elemento Am = {"112", "Americio", "Am", 95, 243.06, "[Rn] 5f^7 7s^2", 9, 9};
const Elemento Cm = {"113", "Curio", "Cm", 96, 247.07, "[Rn] 5f^7 6d^1 7s^2", 9, 9};
const Elemento Bk = {"114", "Berquelio", "Bk", 97, 247.07, "[Rn] 5f^9 7s^2", 9, 9};
const Elemento Cf = {"115", "Californio", "Cf", 98, 251.08, "[Rn] 5f^10 7s^2", 9, 9};
const Elemento Es = {"116", "Einstinio", "Es", 99, 252.08, "[Rn] 5f^11 7s^2", 9, 9};
const Elemento Fm = {"117", "Fermio", "Fm", 100, 257.10, "[Rn] 5f^12 7s^2", 9, 9};
const Elemento Md = {"118", "Mendelevio", "Md", 101, 258.10, "[Rn] 5f^13 7s^2", 9, 9};
const Elemento No = {"119", "Nobelio", "No", 102, 259.10, "[Rn] 5f^14 7s^2", 9, 9};
const Elemento Lr2 = {"120", "Laurencio", "Lr", 103, 262.11, "[Rn] 5f^14 7s^2 7p^1", 9, 9};

/* 
=======================================
=MATRIZ PERIÓDICA 9x18 — LAYOUT FÍSICO= 
=======================================
A matriz matrizPeriodica é uma tabela 9x18 que associa as posições na tabela periódica
(linhas e colunas) aos elementos definidos acima. Cada posição na matriz é um ponteiro 
para o respectivo elemento (Elemento*) que é acessado quando a tecla correspondente é pressionada.
*/
const Elemento* matrizPeriodica[9][18] = {
  {&H, NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,&He},
  {&Li,&Be,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,&B,&C,&N,&O,&F,&Ne},
  {&Na,&Mg,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,&Al,&Si,&P,&S,&Cl,&Ar},
  {&K,&Ca,&Sc,&Ti,&V,&Cr,&Mn,&Fe,&Co,&Ni,&Cu,&Zn,&Ga,&Ge,&As,&Se,&Br,&Kr},
  {&Rb,&Sr,&Y,&Zr,&Nb,&Mo,&Tc,&Ru,&Rh,&Pd,&Ag,&Cd,&In,&Sn,&Sb,&Te,&I,&Xe},
  {&Cs,&Ba,&Lu,&Hf,&Ta,&W,&Re,&Os,&Ir,&Pt,&Au,&Hg,&Tl,&Pb,&Bi,&Po,&At,&Rn},
  {&Fr,&Ra,&Lr,&Rf,&Db,&Sg,&Bh,&Hs,&Mt,&Ds,&Rg,&Cn,&Nh,&Fl,&Mc,&Lv,&Ts,&Og},
  {NULL,NULL,NULL,&La,&Ce,&Pr,&Nd,&Pm,&Sm,&Eu,&Gd,&Tb,&Dy,&Ho,&Er,&Tm,&Yb,NULL},
  {NULL,NULL,NULL,&Ac,&Th,&Pa,&U,&Np,&Pu,&Am,&Cm,&Bk,&Cf,&Es,&Fm,&Md,&No,NULL}
};
