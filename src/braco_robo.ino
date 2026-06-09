#include <Servo.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 20, 4);

Servo cotovelo;
Servo garra;

int pos_cotovelo = 90;
int pos_garra    = 0;
bool emergencia  = false;

byte icoBracoCima[8] = {
  0b00100, 0b01110, 0b11111, 0b00100,
  0b00100, 0b00100, 0b00100, 0b00000
};
// Ícone de braço (seta para baixo)
byte icoBracoBaixo[8] = {
  0b00100, 0b00100, 0b00100, 0b00100,
  0b11111, 0b01110, 0b00100, 0b00000
};
// Ícone de garra aberta
byte icoGarraAberta[8] = {
  0b10001, 0b10001, 0b01010, 0b00100,
  0b01010, 0b10001, 0b10001, 0b00000
};
// Ícone de garra fechada
byte icoGarraFechada[8] = {
  0b00000, 0b01110, 0b01110, 0b01110,
  0b01110, 0b01110, 0b00000, 0b00000
};
// Ícone de aviso (!)
byte icoAviso[8] = {
  0b00100, 0b00100, 0b00100, 0b00100,
  0b00100, 0b00000, 0b00100, 0b00000
};
// Quadrado cheio (para barra de progresso)
byte icoBloco[8] = {
  0b11111, 0b11111, 0b11111, 0b11111,
  0b11111, 0b11111, 0b11111, 0b00000
};

#define CHAR_SOBE   0
#define CHAR_DESCE  1
#define CHAR_ABERTA 2
#define CHAR_FECHA  3
#define CHAR_AVISO  4
#define CHAR_BLOCO  5


void barraProgresso(int val, int l, int c, int w) {
  int cheios = map(val, 0, 180, 0, w);
  lcd.setCursor(c, l);
  for (int i = 0; i < w; i++) {
    if (i < cheios)
      lcd.write(CHAR_BLOCO);
    else
      lcd.print('-');
  }
}

const char* estadoGarra() {
  if (pos_garra == 0)   return "FECHADA   ";
  if (pos_garra == 90)  return "SEMI-AB.  ";
  return                       "ABERTA    ";
}

void atualizarLCD() {
  if (emergencia) return; 

  lcd.setCursor(0, 0);
  lcd.print("== BRACO ROBOTICO ==");

  lcd.setCursor(0, 1);
  lcd.print("COTOV:");
  if (pos_cotovelo < 10)  lcd.print("00");
  else if (pos_cotovelo < 100) lcd.print("0");

  lcd.print(pos_cotovelo);
  lcd.print((char)0xDF); 
  lcd.print(" ");
  barraProgresso(pos_cotovelo, 1, 11, 8);

  lcd.setCursor(19, 1);
  if (pos_cotovelo == 0 || pos_cotovelo == 180)
    lcd.write(CHAR_AVISO);
  else
    lcd.print(" ");

  lcd.setCursor(0, 2);
  lcd.print("GARRA: ");
  lcd.print(estadoGarra());
  lcd.setCursor(19, 2);
  if (pos_garra == 0)
    lcd.write(CHAR_FECHA);
  else
    lcd.write(CHAR_ABERTA);

  lcd.setCursor(0, 3);
  lcd.print("U/D:Braco O/C:Garra ");
}

void telaInicio() {
  lcd.clear();
  lcd.setCursor(3, 0);
  lcd.print("BRACO ROBOTICO");
  lcd.setCursor(5, 1);
  lcd.print("INICIADO!");
  lcd.setCursor(0, 2);
  lcd.print("Aguardando comando..");
  lcd.setCursor(0, 3);
  lcd.print("Porta serial: 9600");
  delay(2500);
  lcd.clear();
  atualizarLCD();
}

void telaEmergencia() {
  lcd.clear();
  for (int i = 0; i < 3; i++) {
    lcd.setCursor(0, 0);
    lcd.print("!!!! EMERGENCIA !!!!"); 
    lcd.setCursor(0, 1);
    lcd.print("!! SERVOS PARADOS !!");
    lcd.setCursor(0, 2);
    lcd.print("!!!!!!!!!!!!!!!!!!!!"); 
    delay(400);
    lcd.clear();
    delay(200);
  }
  lcd.setCursor(0, 0);
  lcd.print("*** EMERGENCIA ***  ");
  lcd.setCursor(0, 1);
  lcd.print("  Servos parados    ");
  lcd.setCursor(0, 2);
  lcd.print("Pressione RESET para");
  lcd.setCursor(0, 3);
  lcd.print("    reiniciar       ");
}

void feedbackLinha3(const char* msg) {
  lcd.setCursor(0, 3);
  lcd.print("                    "); // limpa linha
  lcd.setCursor(0, 3);
  lcd.print(msg);
}

void limparMonitor() {
  for (int i = 0; i < 50; i++) Serial.println();
}

void setup() {
  lcd.init();
  lcd.backlight();
  lcd.createChar(CHAR_SOBE,   icoBracoCima);
  lcd.createChar(CHAR_DESCE,  icoBracoBaixo);
  lcd.createChar(CHAR_ABERTA, icoGarraAberta);
  lcd.createChar(CHAR_FECHA,  icoGarraFechada);
  lcd.createChar(CHAR_AVISO,  icoAviso);
  lcd.createChar(CHAR_BLOCO,  icoBloco);
  cotovelo.attach(5);
  garra.attach(6);
  cotovelo.write(pos_cotovelo);
  garra.write(pos_garra);
  Serial.begin(9600);
  limparMonitor();
  Serial.println("==============================");
  Serial.println("     BRACO ROBOTICO        ");
  Serial.println("==============================");
  Serial.println("[U] Subir  (+15) | [D] Descer (-15)");
  Serial.println("[O] Abrir garra  | [C] Fechar garra");
  Serial.println("[Q] Parada de Emergencia");
  Serial.println("==============================\n");

  telaInicio();
}

void loop() {
  char command;

  if (Serial.available() > 0) {
    command = Serial.read();
    command = toupper(command);

    if (command == '\n' || command == '\r') return;

    if (command == 'U') {
      pos_cotovelo = min(180, pos_cotovelo + 15);
      cotovelo.write(pos_cotovelo);
      atualizarLCD();

      if (pos_cotovelo < 180) {
        Serial.print("[BRACO] Subindo -> ");
        Serial.print(pos_cotovelo); Serial.println("°");
        feedbackLinha3("Braco subindo...    ");
      } else {
        Serial.print("[BRACO] Limite MAX -> ");
        Serial.print(pos_cotovelo); Serial.println("°");
        feedbackLinha3("! LIMITE MAXIMO !   ");
      }

    } else if (command == 'D') {
      pos_cotovelo = max(0, pos_cotovelo - 15);
      cotovelo.write(pos_cotovelo);
      atualizarLCD();

      if (pos_cotovelo > 0) {
        Serial.print("[BRACO] Descendo -> ");
        Serial.print(pos_cotovelo); Serial.println("°");
        feedbackLinha3("Braco descendo...   ");
      } else {
        Serial.print("[BRACO] Limite MIN -> ");
        Serial.print(pos_cotovelo); Serial.println("°");
        feedbackLinha3("! LIMITE MINIMO !   ");
      }

    } else if (command == 'O') {
      pos_garra = min(180, pos_garra + 90);
      garra.write(pos_garra);
      atualizarLCD();

      if (pos_garra == 90) {
        Serial.println("[GARRA] Semi-aberta -> 90°");
        feedbackLinha3("Garra semi-aberta   ");
      } else {
        Serial.println("[GARRA] Totalmente aberta -> 180°");
        feedbackLinha3("Garra aberta total  ");
      }

    } else if (command == 'C') {
      pos_garra = max(0, pos_garra - 90);
      garra.write(pos_garra);
      atualizarLCD();

      if (pos_garra == 90) {
        Serial.println("[GARRA] Semi-fechada -> 90°");
        feedbackLinha3("Garra semi-fechada  ");
      } else {
        Serial.println("[GARRA] Totalmente fechada -> 0°");
        feedbackLinha3("Garra fechada total ");
      }

    } else if (command == 'Q') {
      emergencia = true;

      Serial.println("\n!!! PARADA DE EMERGENCIA !!!");
      Serial.println("Servos desativados.");
      Serial.println("Pressione RESET no Arduino para reiniciar.");

      telaEmergencia();

      cotovelo.detach();
      garra.detach();

      while (true) { }
    }
  }
}