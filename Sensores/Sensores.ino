#include <LiquidCrystal.h>

LiquidCrystal lcd(2,3,4,5,6,7);

//Sensores
int s_Mov = 8;
int s_Puerta = 9;
//Variables de sensores
bool p_abierta = false;
int hay_mov = 0;
//Salidas al RELE
int RELE_Alarma = 10;
int RELE_Led = 11;
//Variables de referencia al tiempo 
unsigned long Tiempo_Transcurrido = 0;
unsigned long T_Refer_Ciclo = 0;
unsigned long T_Refer_Alarma = 0;

void setup()
{
  Serial.begin(9600); //Esta linea y todos los "Serial" se quitaran cuando ya no se hagan pruebas
  //Entradas
  pinMode(s_Mov, INPUT);
  pinMode(s_Puerta, INPUT);
  //Salidas
  pinMode(RELE_Alarma, OUTPUT);
  pinMode(RELE_Led, OUTPUT);
  lcd.begin(16,2);
}

void MostrarTiempo(unsigned long miliseg) //Muestra el tiempo del ciclo 
{
  float m, s;
  unsigned long terminado;
  m = int(miliseg / 60000);
  terminado = miliseg % 60000;
  s = int(terminado / 1000);
  
  lcd.setCursor(0,0);
  lcd.print("Tiempo transcurrido: ");
  lcd.setCursor(0,1);
  lcd.print(int(m));
  lcd.print(" m ");
  lcd.print(int(s));
  lcd.print(" s ");

  //Este bloque se quitara cuando ya no se necesiten pruebas
  //-------------------------------------
  Serial.print("Tiempo transcurrido: ");
  Serial.print(m, 0);
  Serial.print("m ");
  Serial.print(s, 0);
  Serial.println("s ");
  //-------------------------------------
}

void loop()
{
  
  
  T_Refer_Ciclo = millis(); //Se inicia el tiempo de referencia para cuando inicie el ciclo 

  if (digitalRead(s_Puerta) == HIGH) //Se revisa si la puerta se ha abierto 
  { 
    p_abierta = true;
    Serial.println("s_Puerta abierta"); 
  }
  else
  {
    digitalWrite(RELE_Led, LOW);
    p_abierta = false;
  }

  while (p_abierta) // Se inicia el ciclo 
  {
    Tiempo_Transcurrido = millis(); //Tiempo Transcurrido empieza a actualizarce 

    MostrarTiempo((Tiempo_Transcurrido - T_Refer_Ciclo));

    if ((Tiempo_Transcurrido - T_Refer_Ciclo) >= 7000) //Si han pasado 7 minutos
    {
      digitalWrite(RELE_Led, HIGH);
      if ((Tiempo_Transcurrido - T_Refer_Ciclo) >= 10000) //Si han pasado 10 minutos
      {
        hay_mov = digitalRead(s_Mov); //Sensor Movimiento
        if (hay_mov == HIGH) //Si se detecta movimiento 
        {
          Serial.println("Se detecto movimiento");
          T_Refer_Alarma = Tiempo_Transcurrido; // Se inicia el tiempo de referencia para sonar la alarma 
          digitalWrite(RELE_Alarma, HIGH); 
          while ((Tiempo_Transcurrido - T_Refer_Alarma) <= 2000) //Mientras no haya pasado 1 minuto 
          {
            lcd.clear();
            lcd.setCursor(0,0);
  			lcd.print("Sonando");
            lcd.setCursor(0,1);
            lcd.print("Alarma");
            Serial.println("Sonando alarma");
            Tiempo_Transcurrido = millis();
          }
          digitalWrite(RELE_Alarma, LOW); //Se apaga alarma y led antes de terminar el ciclo 
          digitalWrite(RELE_Led, LOW);
          lcd.clear();
          break;
        }
        else
        {
          digitalWrite(RELE_Led, LOW);
          lcd.clear();
          break;
        }
      }
    }
  }
}
