// Led simple + Boton + Zumbador + MPU6050 + (Motor de vibracion)
// Naiara Gadea Rodriguez Gomez
// 
// Nota Si se tiene motor de vibracion descomentar las lineas de codigo correspondientes.

// Librerias I2C para controlar el sensor mpu6050 
// La libreria MPU6050.h necesita I2Cdev.h y la libreria I2Cdev.h necesita Wire.h 
#include "I2Cdev.h" 
#include "MPU6050.h" 
#include "Wire.h" 


// La direccion del MPU6050 puede ser 0x68 o 0x69, dependiendo del estado de AD0. Si no se especifica, 0x68 estara implicito.
// Se crea la variable del sensor. En este caso se esta trabajando con 0x68. Si se quiere trabajar con 0x69 hay que poner MPU6050 sensor(0x69) 
MPU6050 sensor(0x68); 

// Valores en crudo del acelerometro y giroscopio en los ejes x,y,z 
int ax, ay, az; // acelerometro 
int gx, gy, gz; // giroscopio 

float accel_ang_x, accel_ang_y, accel_ang_z; // Variables correspondientes a los angulos de inclinacion. Son los que nos interesan principalmente.

int  boton1 = 2; // Seleccion del pin del boton (pin digital)
int estado1; // Estado del boton ON/OFF
int led = 4; // Seleccion del pin del led (pin digital)
int zum = 7;// Seleccion del pin del zumbador
// int motor = 3; //Seleccion del pin del motor -Cuando se tenga el motor-
int boton2 = 12; //Boton de calibrado
int estado2;//Estado del boton de calibrado

// Otras variables
bool calibrar = false; // Variable que indica cuando seguir o no calibrando.
bool origen = true; // Para guardar los datos del primer valor tras la calibracion y comparar la diferencia de angulo de inclinacion.

// Variables usadas para filtro y promedio durante la calibracion. 
long f_ax,f_ay, f_az; 
int p_ax, p_ay, p_az; 
long f_gx,f_gy, f_gz; 
int p_gx, p_gy, p_gz; 
int counter=0;

//Valor de los offsets.
int ax_o,ay_o,az_o; 
int gx_o,gy_o,gz_o; 

float first_x, first_y, first_z; // Si no funciona correctamente desde el principio, hay que calibrar, o inicializar desde el principio.


// Variables para obtener los valores medios cada cierto tiempo.
float sum_ax, sum_ay, sum_az;
float sum_gx, sum_gy, sum_gz;
float media_ax, media_ay, media_az;
float media_gx, media_gy, media_gz;
int cont = 0;

// Angulo umbral y tiempo de aviso
int ang_aviso = 15;
int t_aviso = 5;

// Definimos las notas que se emplearan para la melodia de aviso del zumbador pasivo.
int Do = 261;
int Re = 293;
int Mi = 329;
int Fa = 349;
int Sol = 392;
int La = 440;
int Si = 493;


void setup() {
  Serial.begin(9600); // Inicializacion del monitor.
  pinMode(led, OUTPUT); // Inicializacion del pin digital led.
  pinMode(boton1, INPUT); // Inicializacion del pin digital del boton.
  pinMode(boton2,INPUT); // Inicializacion del pin boton de calibrado.
  pinMode(zum, OUTPUT); // Inicializacion del pin digital del zumbador.
  //pinMode(motor, OUTPUT);// Inicializacion del pin digital del motor de vibracion.

  Wire.begin(); // Inicializacion de la comunicacion I2C
  sensor.initialize(); // Inicializacion del sensor MPU6050

  // Al inicializar el sensor los rangos seran: 
  // Acelerometro: -2g a +2g 
  // Giroscopio: -250deg/sec a +250deg/sec 

  // Se comprueba que se ha inicializado correctamente el sensor.   
  if (sensor.testConnection()) Serial.println("Sensor iniciado correctamente"); 
  else Serial.println("Error al iniciar el sensor"); 

  // Definicion de offsets iniciales iniciales
  ax_o=sensor.getXAccelOffset(); 
  ay_o=sensor.getYAccelOffset(); 
  az_o=sensor.getZAccelOffset(); 
  gx_o=sensor.getXGyroOffset(); 
  gy_o=sensor.getYGyroOffset(); 
  gz_o=sensor.getZGyroOffset(); 
  
  Serial.println("Offsets iniciales:"); 
  Serial.print(ax_o); Serial.print("\t");  
  Serial.print(ay_o); Serial.print("\t");  
  Serial.print(az_o); Serial.print("\t");  
  Serial.print(gx_o); Serial.print("\t");  
  Serial.print(gy_o); Serial.print("\t"); 
  Serial.print(gz_o); Serial.println("\t"); 
  
  
  Serial.println("Introduce un angulo umbral(deg). "); 
  while (Serial.available()==0){
  }
  int num = Serial.parseInt();

  if (num!=0){
    Serial.println("Entra");
    ang_aviso = num;
  }
  Serial.println("Angulo umbral: "); Serial.println(ang_aviso);
  Serial.println("Introduce un tiempo de respuesta(sec). "); 
  delay(5000);
  while (Serial.available()==1){
  }

  int num2 = Serial.parseInt();

  if (num2!=0){
    t_aviso = num2;
  }
  Serial.println("Tiempo de espera para aviso: "); Serial.println(t_aviso);

}

void loop() {
  if (estado1 == LOW && digitalRead(boton1)){
    // Si se presiona el boton se ENCIENDE EL DISPOSITIVO y por lo tanto se enciende el led.
    digitalWrite(led, HIGH); // Encendido
    //delay(1000); // Durante 1 segundo (1000 ms)
    estado1 = HIGH; // Cambia el estado del boton a encendido.
    
  }
  if(estado1 == HIGH){
    // Si el dispositivo se encuentra encendido
    // Lectura de las aceleraciones y velocidades angulares y guardado en sus variables correspondientes.
    sensor.getAcceleration(&ax, &ay, &az); 
    sensor.getRotation(&gx, &gy, &gz);

    if (digitalRead(boton2) && estado2==LOW){
      // Si se presiona el boton de calibracion, cambia el estado para indicar que hay que calibrar.
      calibrar = true;
    }

    if (calibrar){
      // Si se quiere calibrar se calibra.
      calibracion();
      origen = true; // Se modifican los angulos iniciales de inclinacion.
    }else{
      
      if (cont < t_aviso/0.5){
        lecturas(); // Se realiza la lectura de los valores cada t_aviso tiempo de aviso)
        sum_ax = sum_ax + accel_ang_x;
        sum_ay = sum_ay + accel_ang_y; 
        sum_az = sum_az + accel_ang_z;

        cont++;

      } else{
        media_ax = sum_ax/(t_aviso/0.5);
        Serial.print("Valor medio de inclinacion en X: "); Serial.println(media_ax);
        media_ay = sum_ay/(t_aviso/0.5);
        Serial.print("Valor medio de inclinacion en Y: "); Serial.println(media_ay);
        media_az = sum_az/(t_aviso/0.5);
        

        // reestablecemos los sumatorios
        sum_ax = 0; 
        sum_ay = 0; 
        sum_az = 0; 
        cont = 0;

        if(abs(first_x - media_ax)<ang_aviso & abs(first_y - media_ay)<ang_aviso){// & abs(first_z - media_az)<15){
          Serial.println("Buena postura");
          noTone(zum); // NO se produce alerta
          //digitalWrite(motor, LOW);// Paramos el motor -Cuando se tenga motor.
        }else{
          Serial.println("Mala postura, ponte recto");
          //digitalWrite(motor, HIGH); //vibracion -Cuando se tenga motor.
          //delay(500);  // -Cuando se tenga motor.
          melodia(); // Se produce alerta
          
        }

      }
      if(origen){
        first_x = accel_ang_x;
        first_y = accel_ang_y;
        first_z = accel_ang_z;
        Serial.print("Valor primera medida en eje X: "); Serial.println(first_x);
        Serial.print("Valor primera medida en eje Y: "); Serial.println(first_y);
        Serial.print("Valor primera medida en eje Z: "); Serial.println(first_z);

        origen = false;
      }

    } 

    // Si se presiona el boton se apaga el dispositivo
    if (digitalRead(boton1)){
      digitalWrite(led, LOW); // Apagado
      delay(1000); // Durante 1 segundo (1000ms)
      estado1 = LOW; // Cambia el estado del boton a apagado.
    }
    
  }

}

void lecturas(){
  // Si queremos pasar las lecturas del acelerometro a m/s^2 hay que multiplicar las lecturas por (9.81/16384.0). 
  // En la componente Z se deben encontrar mediciones aproximadas a los 9.8 m/s^2 
  // Si queremos pasar las lecturas del giroscopio a deg/s (grados/s) hay que multiplicar las lecturas por (250.0/32768.0) 
  Serial.print("a[x y z]   Incl X   Incl Y  g[x y z]:\t"); 
  Serial.print(ax*(9.81/16384.0)); Serial.print("\t"); // En m/s^2
  Serial.print(ay*(9.81/16384.0)); Serial.print("\t"); // En m/s^2
  Serial.print(az*(9.81/16384.0)/2); Serial.print("\t"); // En m/s^2

  accel_ang_x=atan(ax/sqrt(pow(ay,2) + pow(az,2)))*(360.0/3.14); // En angulos de inclinacion
  Serial.print(accel_ang_x); Serial.print("\t"); 
  accel_ang_y=atan(ay/sqrt(pow(ax,2) + pow(az,2)))*(360.0/3.14); // En angulos de inclinacion
  Serial.print(accel_ang_y); Serial.print("\t"); 
  accel_ang_z=atan(az/sqrt(pow(ax,2) + pow(ay,2)))*(360.0/3.14); // En angulos de inclinacion
  Serial.print(accel_ang_z); Serial.print("\t"); 
  
  // Esto no es necesario
  Serial.print(gx*(250.0/32768.0)); Serial.print("\t"); // En grados/s
  Serial.print(gy*(250.0/32768.0)); Serial.print("\t"); // En grados/s 
  Serial.println(gz*(250.0/32768.0)); // En grados/s

  delay(500); // Mide cada 0,5 segundos. Cuando se calcule la media para comprobar que la buena postura sera cada t_aviso*2

}

void calibracion(){
  // Primero se filtran las lecturas
  f_ax = f_ax-(f_ax>>5)+ax; 
  p_ax = f_ax>>5; 

  f_ay = f_ay-(f_ay>>5)+ay; 
  p_ay = f_ay>>5; 

  f_az = f_az-(f_az>>5)+az; 
  p_az = f_az>>5; 

  f_gx = f_gx-(f_gx>>3)+gx; 
  p_gx = f_gx>>3; 

  f_gy = f_gy-(f_gy>>3)+gy; 
  p_gy = f_gy>>3; 

  f_gz = f_gz-(f_gz>>3)+gz; 
  p_gz = f_gz>>3; 
  
  // Cada 100 lecturas se corrige el offset 
  if (counter==100){ 
    // Mostramos las lecturas promedio para ver como va con la calibracion 
    Serial.print("promedio:"); Serial.print("\t"); 
    Serial.print(p_ax); Serial.print("\t"); 
    Serial.print(p_ay); Serial.print("\t"); 
    Serial.print(p_az); Serial.print("\t"); 
    Serial.print(p_gx); Serial.print("\t"); 
    Serial.print(p_gy); Serial.print("\t"); 
    Serial.println(p_gz); 
    // Basicamente se modifica constantemente el offset para que sea 0, como medida real. 
    // Se ajusta el Offset del acelerometro
    if (p_ax>0) ax_o--; 
    else {ax_o++;} 
    
    if (p_ay>0) ay_o--; 
    else {ay_o++;} 
    
    if (p_az-16384>0) az_o--; 
    else {az_o++;} 
    
    sensor.setXAccelOffset(ax_o); 
    sensor.setYAccelOffset(ay_o); 
    sensor.setZAccelOffset(az_o); 
    
    // Se ajusta el Offset del giroscopio
    if (p_gx>0) gx_o--; 
    else {gx_o++;} 
    
    if (p_gy>0) gy_o--; 
    else {gy_o++;} 
    
    if (p_gz>0) gz_o--; 
    else {gz_o++;} 

    sensor.setXGyroOffset(gx_o); 
    sensor.setYGyroOffset(gy_o); 
    sensor.setZGyroOffset(gz_o);
    
    counter=0; 

    if (p_ax>-10 & p_ax<10 & p_ay>-10 & p_ay<10 & p_az>32757 & p_az<32777 & p_gx>-10 & p_gx<10 & p_gy>-10 & p_gy<10 & p_gz>-10 & p_gz<10){
    //if (p_ax>-10 & p_ax<10 & p_ay>-10 & p_ay<10 & p_az>16374 & p_az<16394 & p_gx>-10 & p_gx<10 & p_gy>-10 & p_gy<10 & p_gz>-10 & p_gz<10){
      Serial.println("DISPOSITIVO CALIBRADO!!!");
      // El dispositivo Pita 3 veces ara indicar que se ha calibrado correctamente.
      tone(zum, Sol, 500);
      delay(200);
      noTone(zum);
      delay(200);
      tone(zum, Sol, 500);
      delay(200);
      noTone(zum);
      delay(200);
      tone(zum, Sol, 500);
      delay(200);
      noTone(zum);
      calibrar = false;
    }else{
      Serial.println("Calibrando...");
    }
  } 
  counter++;

}




void melodia(){
  // Escala de musica con el zumbador
    tone(zum, Fa, 500);
    delay(700);
    tone(zum, Sol, 500);
    delay(700);
    // Si se quiere realizar una melodia mas larga.
    //tone(zum, Sol, 500);
    //delay(700);
    //tone(zum, La, 1000);
    //delay(1700);
    //tone(zum, Sol, 500);
    //delay(700);
    //tone(zum, Fa, 500);
    //delay(700);
    //tone(zum, Sol, 500);
    //delay(700);
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
