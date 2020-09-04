//ToDo: Cambiar if por while
//ToDo: Implementar MostrarTiempo()
int PIR = 2;
int RELE = 3;
int Puerta = 5;
bool isOpen = false;
int isMoving = 0;
int Alarma = 11;
unsigned long Time = 0;
//Variable para checar cuanto tiempo lleva corriendo
unsigned long TiempoTranscurrido = 0;
unsigned long TiempoTranscurrido2 = 0;

void setup(){
  Serial.begin(9600);
  pinMode(PIR, INPUT);
  pinMode(RELE, OUTPUT);
  pinMode(Puerta, INPUT);
  pinMode (Alarma, OUTPUT);
}

void MostrarTiempo(unsigned long seg){
  Serial.println(seg);
  //Aqui pondremos la mierda quee va al display
}

void loop(){
  TiempoTranscurrido = millis();

  if (digitalRead(Puerta) == HIGH){  //Sensor puerta
    isOpen = true;
    Serial.println("Puerta abierta");
  } 
  else{
    
    digitalWrite(RELE, LOW);
    //Se actualiza el tiempo si la puerta  no esta abierta

    isOpen = false;
  }

  while (isOpen){
    Time = millis(); //Tiempo Transcurrido deja de actualizarse
    MostrarTiempo((Time - TiempoTranscurrido));
    if((Time - TiempoTranscurrido) >= 7000){

      digitalWrite(RELE, HIGH);
      if ((Time - TiempoTranscurrido) >= 10000) {
        isMoving = digitalRead(PIR);   //Sensor Movimiento
        if(isMoving == HIGH){
          Serial.println("Se detecto movimiento");
          TiempoTranscurrido2 = Time;
          while((Time - TiempoTranscurrido2) <= 2000){
            Serial.println("Sonando alarma");
             digitalWrite(Alarma, HIGH);
             delay(200);
             digitalWrite(Alarma, LOW);
            Time = millis();
          }
          digitalWrite(RELE, LOW);
          break;
        }
        else{
          break;
        }
      }	
    }
  }
}
