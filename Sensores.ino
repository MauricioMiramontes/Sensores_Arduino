//ToDo: Cambiar if por while
//ToDo: Implementar MostrarTiempo()
int PIR = 2;
int RELE = 3;
int Puerta = 5;
int isOpen = 0;
int isMoving = 0;
unsigned long Time = 0;
//Variable para checar cuanto tiempo lleva corriendo
unsigned long TiempoTranscurrido = 0;

void setup(){
    pinMode(PIR, INPUT);
    pinMode(RELE, OUTPUT);
  	pinMode(Puerta, INPUT);
}

void MostrarTiempo(unsigned long seg){
	Serial.println(seg);
  	//Aqui pondremos la mierda quee va al display
}

void loop(){
    isOpen = digitalRead(Puerta); //Sensor puerta
  	isMoving =digitalRead(PIR);   //Sensor Movimiento
    if (isOpen == HIGH){
      	Serial.println("Puerta abierta");
      	MostrarTiempo((Time - TiempoTranscurrido));
      	Time = millis(); //Tiempo Transcurrido deja de actualizarse
    	if((Time - TiempoTranscurrido) >= 7000){
      	 	digitalWrite(RELE, HIGH);
          	if (((Time - TiempoTranscurrido) >= 10000) && ( isMoving == HIGH){
              	
            	 Serial.println("Suena Alarma");           	          
            }	
     	}
    }
    else{
        digitalWrite(RELE, LOW);
      	//Se actualiza el tiempo si la puerta  no esta abierta
      	TiempoTranscurrido = millis();	
    }
}