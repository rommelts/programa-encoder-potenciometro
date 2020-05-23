#define potenciometro A0  // definicion de la lectura del potenciometro
int ena=9;  //pin donde se conecta la señal PWM del L298
#define in1 8  //pin +o- del motor
#define in2 7  //pin +o- del motor

#define encoder_pin 2
int val_nuevo, val_antiguo, clicks, vuelta;


/*
  p= lectura de potenciometro
  gd=mapeo de valores lado derecho de giro
  gi=mapeo de valores lado izquierdo de giro
  
*/
int p,m;  

void setup() {
  Serial.begin(9600);
  pinMode(in1, OUTPUT);  //entrada 1
  pinMode(in2, OUTPUT);  //entrada 2
  pinMode(ena, OUTPUT);
  pinMode(potenciometro, INPUT);
  pinMode(encoder_pin, INPUT);  //Definir el pin del encoder como entrada
    val_nuevo = digitalRead(encoder_pin);
    val_antiguo = val_nuevo;
}

void loop() {
  digitalWrite(in1,HIGH);
  digitalWrite(in2,LOW);
  p=analogRead(potenciometro);  //lectura de potenciometro
  //Serial.println(p);  
  m=map(p, 0, 1023, 0, 255);  //transformar valores de potenciometro a pwm
  Serial.println(m);
  //delay(100);
  analogWrite(ena, m);
  val_nuevo = digitalRead(encoder_pin);
   
    if(val_nuevo != val_antiguo) {  //Si valor antiguo es distinto a nuevo porque va dando los clicks deespacio
        if(clicks == 20) {  //porque la cantidad de espacios es 20
            clicks = 1;  //Como son 20 y si cumple esta condicion debo reiniciar el cuenteo
            vuelta++;  
            Serial.print("TURNS: ");
            Serial.println(vuelta);  
        }
        else{ 
          clicks++;  //como aun no hay 20 clicks entonces a un no termina la vuelta
        }
        Serial.print("CLICKS: ");
        Serial.println(clicks);

        val_antiguo = val_nuevo;  //para que no leea el mismo bajo o alto que se de ya que al ir avanzando debe contar un click o un no click
    }
}
/*
 * programa pwm del motor
 * 
int IN3 = 9;    // Input3 conectada al pin 5
int IN4 = 10;    // Input4 conectada al pin 4 
int ENB = 11;    // ENB conectada al pin 3 de Arduino
void setup()
{
 pinMode (ENB, OUTPUT); 
 pinMode (IN3, OUTPUT);
 pinMode (IN4, OUTPUT);
}
void loop()
{
  //Preparamos la salida para que el motor gire en un sentido
  digitalWrite (IN3, HIGH);
  digitalWrite (IN4, LOW);
  // Aplicamos PWM al pin ENB, haciendo girar el motor, cada 2 seg aumenta la velocidad
  analogWrite(ENB,55);
  delay(2000);
  analogWrite(ENB,105);
  delay(2000);
  analogWrite(ENB,255);
  delay(2000);
  // Apagamos el motor y esperamos 5 seg
  analogWrite(ENB,0);
  delay(5000);
}
*/
