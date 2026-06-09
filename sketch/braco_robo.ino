#include <Servo.h>

Servo cotovelo;
Servo garra;

int pos_cotovelo = 90;
int pos_garra = 0;

void limparMonitor() {
  for (int i = 0; i < 50; i++) {
    Serial.println();
  }
}



void setup()
{
  cotovelo.attach(5);
  garra.attach(6);
  Serial.begin(9600);
  limparMonitor();
  Serial.println("Robô foi iniciado!");
  Serial.println("Controle do braço robô 🦾:");
  Serial.println("[U] -> Subir braço (+15°) || [D] -> Descer braço (-15°)\n");
  Serial.println("Controle da garra ⑃:");
  Serial.println("[O] -> Abrir || [C] -> Fechar\n");
  Serial.println("[Q] -> Parada de Emergência\n");
  cotovelo.write(pos_cotovelo);
  garra.write(pos_garra);
}

void loop()
{
  char command;

  if (Serial.available() > 0){

    command = Serial.read();
    command = toupper(command);

    if (command == '\n' || command == '\r') return;

    if (command == 'U'){         //UP

      pos_cotovelo = min(180, pos_cotovelo + 15);
      cotovelo.write(pos_cotovelo);
      if (pos_cotovelo < 180) {
        Serial.print("Braço subindo. Posição = ");
        Serial.println(pos_cotovelo);
      } else {
        Serial.print("Braço já subiu até o seu limite! Posição = ");
        Serial.println(pos_cotovelo);
      }

    } else if (command == 'D'){      //DOWN

      pos_cotovelo = max(0, pos_cotovelo - 15);
      cotovelo.write(pos_cotovelo);
      if (pos_cotovelo > 0) {
        Serial.print("Braço descendo. Posição = ");
        Serial.println(pos_cotovelo);
      } else {
        Serial.print("Braço já desceu até o seu limite! Posição = ");
        Serial.println(pos_cotovelo);
      }
      

    } else if (command == 'O'){      //OPEN

      pos_garra = min(180, pos_garra + 90);
      garra.write(pos_garra);
      if (pos_garra < 180){
        Serial.print("Garra semi aberta. Posição = ");
        Serial.println(pos_garra);
      } else {
        Serial.print("Garra totalmente aberta. Posição = ");
        Serial.println(pos_garra);
      }
      

    } else if (command == 'C'){       //CLOSE

      pos_garra = max(0, pos_garra - 90);
      garra.write(pos_garra);
      if (pos_garra > 0){
        Serial.print("Garra semi-aberta. Posição = ");
        Serial.println(pos_garra);
      } else {
        Serial.print("Garra totalmente fechada. Posição = ");
        Serial.println(pos_garra);
      }
      

    } else if (command == 'Q'){
      Serial.println("\n[SISTEMA ENVIADO PARA PARADA DE EMERGENCIA]");
      Serial.println("Servos desativados. Para reiniciar, clique no botao vermelho de RESET do Arduino.");
      
      cotovelo.detach();
      garra.detach();

      while(true) {
        
      }

    }

  }

}