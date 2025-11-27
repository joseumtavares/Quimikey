# Quimikey - Tabela Periódica Funcional

Quimikey é um projeto que faz parte do programa Maker da UFSC e apoio do Rexlab. Este projeto visa melhorar o ensino de Química nas escolas públicas utilizando a cultura Maker e tecnologias como Arduino, LEDs RGB e Impressoras 3D. O nome "Quimikey" foi criado como uma junção das palavras "Química" e "Teclado", e reflete o foco do projeto em proporcionar uma interação mais imersiva com a Tabela Periódica.

## Contexto

Durante o estágio, fui convidado por meu colega Laércio, um dos membros fundadores do projeto, a colaborar no desenvolvimento de uma ferramenta para melhorar a experiência de aprendizado de Química. A ideia inicial era criar um teclado funcional de Química, mas conforme fui me integrando após a minha entrada no grupo de WhatsApp do **Projeto Maker UFSC** em 24 de setembro de 2025, passei a entender melhor os detalhes do projeto e comecei a colaborar ativamente no desenvolvimento de uma simulação online na plataforma **Wowki** - [Veja o projeto no Wowki](https://wokwi.com/projects/447527832061171713). Posteriormente, passei a contribuir diretamente na programação e no protótipo físico.

Ao longo do desenvolvimento, o projeto passou por várias melhorias e ajustes, que foram aplicados tanto na parte de simulação quanto na implementação do protótipo real com Arduino. O nome "Quimikey" foi sugerido por mim e aceito pela equipe, e a partir daí, o projeto evoluiu, tornando-se mais robusto e com planos para futuras atualizações, incluindo modelos 3D, realidade aumentada (AR), áudio para deficientes visuais, e até mesmo a inclusão de braile nos keycaps.

## Membros da Equipe

- **Elvis Alex de Aguiar** – EEB Professora Maria Garcia Pessi
- **Laércio Luiz Teixeira** – EEB Apolônio Ireno Cardoso
- **Marcelo Sprícigo Peres** – EEB Araranguá
- **Maria Aparecida Jeremias** – EEB Apolônio Ireno Cardoso
- **José Ubirajara Moreira Tavares** - Cruzeiro do Sul : Desenvolvedor e responsável pela implementação da lógica de programação e protótipo na protoboard e montagem do primeiro protótipo

## Objetivo do Projeto

Quimikey visa tornar o ensino de Química mais acessível e interativo, especialmente para alunos com deficiências, proporcionando uma Tabela Periódica funcional, física e interativa. O projeto utiliza a Cultura Maker para envolver os estudantes na construção da própria ferramenta de aprendizado, incorporando tecnologias como Arduino, Impressão 3D e LEDs RGB para criar uma Tabela Periódica que se adapta a diferentes necessidades educacionais.

### Futuras Melhorias

- Implementação de modelos 3D para visualização dos elementos.
- Áudio e Libras para inclusão de alunos com deficiência visual e auditiva.
- Teclas com Braile e impressão 3D dos Keycaps.
- Software complementar para plataformas Web, Android e iOS.
- **Integração com Micro:bit e Scratch**: Facilitando a utilização em diferentes laboratórios Maker.
- **Desenvolvimento com ESP32 e Raspberry Pi**: Para integração com HDMI, áudio, e outras funcionalidades multimídia.

## Desenvolvimento Inicial

Na empolgação da equipe, optamos inicialmente pelo desenvolvimento do protótipo com **switch keys de teclados mecânicos**, no entanto, a ideia é criar protótipos utilizando **chaves táteis**, que são mais acessíveis e viáveis para reprodução em qualquer laboratório Maker.

Na primeira versão do protótipo, utilizamos o **Arduino Mega**, mas já estamos trabalhando em uma versão com **Arduino Uno** e **expansores de I/O PCF 8574**, o que torna o projeto mais acessível e facilita a reprodução nos **laboratórios Maker**, que, no Brasil, utilizam amplamente o Arduino Uno como plataforma de desenvolvimento.

### Integração com Micro:bit e Scratch

Além disso, estou trabalhando em uma integração com o **Micro:bit**, outro dispositivo popular em laboratórios Maker, e com a plataforma de programação **Scratch**. Essa integração permitirá que os alunos programem de forma simples e visual, ampliando o alcance do projeto.

### Planejamento de Modelos 3D e Conectividade

Estou também desenvolvendo um **layout de uma PCB** utilizando **ESP32**, o que permitirá uma **integração com Raspberry Pi ou Orange Pi**. Essa mudança facilitará implementações com software, conexão HDMI, áudio, e abrirá portas para novas funcionalidades, como **realidade aumentada (AR)** e **áudio interativo**. Com essas novas opções de conectividade, as possibilidades são praticamente infinitas para expandir o Quimikey.

## Contribuições e Aprendizado

Parte do código utilizado neste projeto foi inspirado no projeto [the-keyboard](https://github.com/dairequinlan/the-keyboard), no qual aprendemos e aplicamos a lógica de **debounce** para garantir a leitura precisa das teclas pressionadas e evitar múltiplos acionamentos de um mesmo botão. A contribuição de código, especialmente no controle das teclas de forma eficiente, foi fundamental para o desenvolvimento do Quimikey, melhorando a interação com o sistema.

## Como Participar

Este projeto está em constante evolução e gostaríamos de convidar outros educadores, desenvolvedores e entusiastas da área a colaborar. Se você tem interesse em ajudar a melhorar este projeto, seja com ideias, código ou melhorias no protótipo, entre em contato conosco através dos nossos canais de comunicação ou faça um **fork** no nosso repositório e contribua diretamente.

## Como Usar

1. **Clone o repositório**:
   ```bash
   git clone https://github.com/joseumtavares/Quimikey.git
