// Led simple + Boton + Zumbador + Tilt + Motor Vibración
// Naiara Gadea Rodriguez Gomez
// 

int led = 4; // Seleccion del pin del led (pin digital)
int  boton = 2; // Seleccion del pin del boton (pin digital)
int zum = 7;// Seleccion del pin del zumbador
int tilt = 12;// Seleccion del pin del sensor SW250D
int motor = 3; //Selección del pin del motor de vibración

int estado; // Estado del boton

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(led, OUTPUT); // inicialización del pin digital led.
  pinMode(boton, INPUT); // inicialización del pin digital del boton.
  pinMode(zum, OUTPUT); // inicialización del pin digital del zumbador
  pinMode(tilt, INPUT); // inicialización del pin digital del sensor tilt
  digitalWrite(tilt , HIGH); // Sensor tilt 
  pinMode(motor, OUTPUT);// inicialización del pin digital del motor de vibración
}

void loop() {
  // put your main code here, to run repeatedly:
  Serial.println(digitalRead(tilt));// Para comprobar en el Serial Monitor.
  if (estado == LOW && digitalRead(boton)){
    // Si se presiona el boton se enciende el dispositivo
    digitalWrite(led, HIGH); // Encendido
      delay(1000); // Durante 1 segundo (1000 ms)
      estado = HIGH; // Cambia el estado del boton a encendido.
    
  }
  if(estado == HIGH){
    // Si el sensor tilt hace contacto, el usuario tiene una mala postura y el dispositivo manda un aviso, musical o de vibración.
    if (digitalRead(tilt))  {
      // Vibración intermitente
      digitalWrite(motor, HIGH); //vibración
      delay(500);  // delay one second
      //digitalWrite(motor, LOW);  //stop vibrating
      //delay(500); //wait 50 seconds.
      // si vemos que durante la música no se enciende el motor
      
      melodia(); // En este caso es un aviso sonoro, pero teniendo un motor de vibracion se puede utilizar un aviso vibratorio.
      
    }  else  {
      // Si no hay contacto con el sensor tilt, no suena la melodía
      noTone(zum); // El zumbador ya no emite ruido
      //delay(3000);
      digitalWrite(motor, LOW);// Paramos el motor
    }

    // Si se presiona el boton se apaga el dispositivo
    if (digitalRead(boton)){
      digitalWrite(led, LOW); // Apagado
      delay(1000); // Durante 1 segundo (1000ms)
      estado = LOW; // Cambia el estado del boton a apagado.
    }
    
  }

}

// Definimos las notas
int Do = 261;
int Re = 293;
int Mi = 329;
int Fa = 349;
int Sol = 392;
int La = 440;
int Si = 493;

void melodia(){
  // Escala de musica con el zumbador
    tone(zum, Fa, 500);
    delay(700);
    tone(zum, Sol, 500);
    delay(700);
    tone(zum, Sol, 500);
    delay(700);
    tone(zum, La, 1000);
    delay(1700);
    tone(zum, Sol, 500);
    delay(700);
    tone(zum, Fa, 500);
    delay(700);
    tone(zum, Sol, 500);
    delay(700);
    //tone(zum, Do, 1000);
    //delay(1700);
    //tone(zum, Fa, 500);
    //delay(700);
    //tone(zum, La, 500);
    //delay(700);
    //tone(zum, Fa, 500);
    //delay(700);
    //tone(zum, Re, 1000);
    //delay(1700);
    
}
