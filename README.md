# Garra Robotica com Arduino

Projeto de controle de um braco robotico articulado utilizando a plataforma Arduino, servomotores, display LCD I2C e pecas modeladas em 3D.

---

## Conexoes de Hardware

As ligacoes no Arduino Uno devem ser feitas seguindo o esquema abaixo:

| Pino Arduino | Componente      | Descricao                                           |
| :----------: | :-------------- | :-------------------------------------------------- |
| **D5**       | Servo 1         | Controle de articulacao do braco (cotovelo)         |
| **D6**       | Servo 2         | Controle de abertura/fechamento da garra            |
| **A4 (SDA)** | LCD I2C - SDA   | Linha de dados do barramento I2C                    |
| **A5 (SCL)** | LCD I2C - SCL   | Linha de clock do barramento I2C                    |
| **5V**       | VCC             | Alimentacao de energia do sistema                   |
| **GND**      | GND             | Terra / Ponto de referencia de tensao (0V)          |

---

## Display LCD 20x4 I2C

O projeto utiliza um display LCD 20x4 com modulo I2C para exibir o status do robo em tempo real, eliminando a necessidade de acompanhar o Monitor Serial durante a operacao.

### Layout da tela

```
Linha 0: == BRACO ROBOTICO ==
Linha 1: COTOV:090°  [######--] !
Linha 2: GARRA: ABERTA        [ico]
Linha 3: <feedback da ultima acao>
```

| Linha | Conteudo                                                                 |
| :---: | :----------------------------------------------------------------------- |
| **0** | Titulo fixo do sistema                                                   |
| **1** | Angulo atual do cotovelo (0-180°) com barra de progresso visual e aviso de limite |
| **2** | Estado atual da garra (FECHADA / SEMI-AB. / ABERTA) com icone           |
| **3** | Feedback dinamico da ultima acao executada                               |

Quando a parada de emergencia e ativada, a tela exibe uma contagem regressiva piscante seguida da mensagem de travamento de seguranca.

### Biblioteca necessaria

Instale a biblioteca `LiquidCrystal_I2C` by Frank de Brabander pelo Library Manager do Arduino IDE (`Sketch > Include Library > Manage Libraries`).

### Endereco I2C

O endereco padrao configurado no codigo e `0x27`. Caso o display nao inicialize, tente `0x3F`. Para identificar o endereco correto, execute um sketch de escaneamento I2C no Arduino antes de rodar o projeto.

---

## Guia de Operacao

O controle do robo e feito via **Monitor Serial**. Digite as teclas abaixo para acionar os movimentos:

| Comando | Acao no Robo                 |
| :-----: | :--------------------------- |
| `[ U ]` | Sobe o braco                 |
| `[ D ]` | Desce o braco                |
| `[ O ]` | Abre a garra                 |
| `[ C ]` | Fecha a garra                |
| `[ Q ]` | **Parada de emergencia** (Desliga os motores) |

> **Atencao:** Se a parada de emergencia (`Q`) for ativada, o sistema entra em travamento de seguranca. Para voltar a operar, e necessario apertar o botao fisico de **RESET** na placa do Arduino.

---

## Modelagem 3D

A modelagem estrutural das pecas que compoem o braco robotico e que se conectam aos hardwares foi desenvolvida utilizando o **Autodesk Fusion**. O software permitiu a criacao de encaixes precisos e a exportacao direta dos arquivos (`.stl` / `.obj`) prontos para **impressao 3D**.

---

## Simulacao

O circuito e o codigo fonte podem ser testados diretamente pelo navegador.

**[Acessar Simulacao no Wokwi](https://wokwi.com/projects/466380384604735489)**

---

## Integrantes do Grupo

| Nome                                  | RM        |
| :------------------------------------ | :-------- |
| **Victor Kenzo Toma**                 | RM551649  |
| **Arthur Baldissera Claumann Marcos** | RM550219  |
| **Ricardo Ramos Vergani**             | RM550166  |