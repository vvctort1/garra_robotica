
# Garra Robótica com Arduino

Projeto de controle de um braço robótico articulado utilizando a plataforma Arduino, servomotores e peças modeladas em 3D. 

---

## Conexões de Hardware

As ligações no Arduino Uno devem ser feitas seguindo o esquema abaixo:

| Pino Arduino | Componente | Descrição |
| :---: | :--- | :--- |
| **D5** | Servo 1 | Controle de articulação do braço (cotovelo) |
| **D6** | Servo 2 | Controle de abertura/fechamento da garra |
| **5V** | VCC | Alimentação de energia do sistema |
| **GND** | GND | Terra / Ponto de referência de tensão (0V) |

---

## Guia de Operação

O controle do robô é feito via **Monitor Serial**. Digite as teclas abaixo para acionar os movimentos:

| Comando | Ação no Robô |
| :---: | :--- |
| `[ U ]` | Sobe o braço |
| `[ D ]` | Desce o braço |
| `[ O ]` | Abre a garra |
| `[ C ]` | Fecha a garra |
| `[ Q ]` | **Parada de emergência** (Desliga os motores) |

> ⚠️ **Atenção:** Se a parada de emergência (`Q`) for ativada, o sistema entra em travamento de segurança. Para voltar a operar, é necessário apertar o botão físico de **RESET** na placa do Arduino.

---

## Modelagem 3D

A modelagem estrutural das peças que compõem o braço robótico e que se conectam aos hardwares foi desenvolvida utilizando o **Autodesk Fusion**. O software permitiu a criação de encaixes precisos e a exportação direta dos arquivos (`.stl` / `.obj`) prontos para **impressão 3D**.

---

## Simulação

O circuito e o código fonte podem ser testados diretamente pelo navegador. 

**[Acessar Simulação no Wokwi](https://wokwi.com/projects/466380384604735489)**

---

## Integrantes do Grupo

| Nome | RM |
| :--- | :--- |
| **Victor Kenzo Toma** | RM551649 |
| **Arthur Baldissera Claumann Marcos** | RM550219 |
| **Ricardo Ramos Vergani** | RM550166 |
=======
