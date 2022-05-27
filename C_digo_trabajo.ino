//defines del controlador paso a paso
#define STEP 4//SALIDA A LA QUE CONECTEMOS
#define DIR 5 //SALIDA A LA QUE CONECTEMOS


//Declaración de los pines del sensor ultrasónico.
const int echo_izquierda=10; /*DONDE LO CONECTAMOS*/
const int echo_derecha=12; 
const int trig_izquierda=11; 
const int trig_derecha=13; 


//Declaración de las variables de duración y distancia.
int duracion_izquierda; 
int duracion_derecha;
int distancia_izquierda;
int distancia_derecha;

boolean debug = false;

void sigue();

//FUNCIÓN PRINCIPAL
void setup ()
{
  pinMode (STEP, OUTPUT);
  pinMode (DIR, OUTPUT);
  
  if (debug) 
    {
      Serial.begin(9600); //COMUNICACIÓN SERIAL (9600) cantidad de bits por segundo que se reciben //Serial.println(DISTANCIA); println distancia
    }
  
}

//FUNCIÓN QUE SE REPITE
void loop()
{

//Los sensores mandan y reciben una señal.
  pinMode(trig_derecha, OUTPUT); //Declaración como salida del trig_derecha
  digitalWrite(trig_derecha, LOW); 
  delayMicroseconds(2);
  digitalWrite(trig_derecha, HIGH); //Manda la señal
  delayMicroseconds(5);
  digitalWrite(trig_derecha, LOW); //Recibe la señal

//Aqui está recibiendo una señal.
  int duracion_derecha = pulseIn(echo_derecha, HIGH);
  
  
//Los sensores mandan y reciben una señal.
  pinMode(trig_izquierda, OUTPUT);//Declaración como salida del trig_izquierda
  digitalWrite(trig_izquierda, LOW); 
  delayMicroseconds(2);
  digitalWrite(trig_izquierda, HIGH); //Manda la señal
  delayMicroseconds(5);
  digitalWrite(trig_izquierda, LOW); //Recibe la señal
  
//Aquí está recibiendo una señal.
  int duracion_izquierda = pulseIn(echo_izquierda, HIGH);
  
//Convertir tiempo en distancia. Distancia del objeto al sensor.
  distancia_derecha   = microsegundosacm(duracion_derecha);
  distancia_izquierda = microsegundosacm(duracion_izquierda);
  
  if (debug) 
  {
    //Imprime la distancia a la izquierda.
    Serial.print("Izquierda: "); 
    Serial.print(distancia_izquierda);
    Serial.println("cm"); //¿POR QUÉ AQUÍ PONE LN? 
    //Imprime la distancia a la derecha.
    Serial.print("Derecha: ");
    Serial.print(distancia_derecha);
    Serial.println("cm");
  }
  sigue(); //Función que va a seguir al objeto que se mueve.
}

long microsegundosacm(long microsegundos)  
{
    return microsegundos /58.2; //Pasar de microsegundos a distancia

void sigue() 
{
  if (distancia_izquierda <= 14|| distancia_derecha <= 14) //Si la distancia entre el sensor de la izquierda y el objeto es más pequeña que el umbral...O si la distancia entre el sensor de la derecha y...
    {
      if(distancia_izquierda + 8 < distancia_derecha)
        {
          digitalWrite(DIR,HIGH); //DIRECCIÓN EN EL CONTROLADOR DEL MOTOR PASO A PASO HACIA UN LADO.
          for (int i=0;i<20;i++){ //MOTOR PASO A PASO CON 1,8 GRADOS DE GIRO.         
            digitalWrite(STEP,HIGH);
            delay(10); 
            digitalWrite(STEP,LOW);
            delay(10);
            }
        }
      if(distancia_derecha + 8 < distancia_izquierda)
        {
          digitalWrite(DIR,LOW); //DIRECCIÓN EN EL CONTROLADOR DEL MOTOR PASO A PASO HACIA EL OTRO LADO.
          for (int i=0;i<20;i++){           
            digitalWrite(STEP,HIGH);
            delay(10);
            digitalWrite(STEP,LOW);
            delay(10);
            }
        }
    } 

}
