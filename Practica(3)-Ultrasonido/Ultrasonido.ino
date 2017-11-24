#include <Keypad.h>

//Sensor Ultrasónico
const int trigPin = 28;
const int echoPin = 29;
long duration;
int distance;

//Teclado Matricial
const byte filas = 4;
const byte columnas = 4;
char teclas[filas][columnas] = {
  { '1', '2', '3', 'A' },
  { '4', '5', '6', 'B' },
  { '7', '8', '9', 'C' },
  { '#', '0', '*', 'D' }
};
byte filasPins[filas] = { 11, 10, 9, 8 };
byte columnasPins[columnas] = { 7, 6, 5, 4 };
Keypad keypad = Keypad(makeKeymap(teclas), filasPins, columnasPins, filas, columnas);
char tecla;

int leds[5] = {22, 23, 24, 25, 26};
char pass[4] = {0, 0, 0, 0};
int tpass;
int contador = 0;
int a = 0;
bool seg = false;

void setup() {
  Serial.begin(9600);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  for (int i = 0; i < 5; i++ ) {
    pinMode(leds[i], OUTPUT);
  }
  Serial.println("Bienvenido");
  Serial.println("Cree una contraseña");
}

void loop() {
  char key = keypad.getKey();

  if (key) {
    if (seg) {
      if (contador == 5) {

      }
      if (key == pass[contador]) {
        Serial.print("*");
        contador++;
      } else {
        Serial.println("Números no coinciden");
        contador = 0;
        Serial.println("Ingrese contraseña");
        return;
      }
    } else {
      if (contador < 4) {
        Serial.print("*");
        pass[contador] = key;
        contador++;
      }

      if (contador == 5) {
        if  (a < 4) {
          if (key == pass[a]) {
            Serial.print("*");
            a++;
          } else {
            Serial.println("Números no coinciden");
            for (int i = 0; i < 4; i++) {
              pass[i] = 0;
            }
            contador = 0;
            a = 0;
            Serial.println("Cree una contraseña");
            return;
          }
        }
        if (a == 4) {
          Serial.println("");
          Serial.println("Contraseña creada");
          seg = true;
          contador = 0;
          key = NULL;
          Serial.println("Ingrese contraseña");
        }
      }
    }
  }

  if (contador == 4) {
    key = NULL;
    if (!seg) {
      contador = 5;
    }

    if (seg) {
      Serial.println("");
      Serial.println("Bienvenido");
      Serial.println("Pulse # para iniciar apertura de valvulas");

      //Mide cantidad de agua.
      digitalWrite(trigPin, LOW);
      delayMicroseconds(2);
      digitalWrite(trigPin, HIGH);
      delayMicroseconds(10);
      digitalWrite(trigPin, LOW);
      duration = pulseIn(echoPin, HIGH);
      distance = duration * 0.034 / 2;
      Serial.print("Distance: ");
      Serial.println(distance);
      if (distance > 110) {
        for (int j = 1; j < 5; j++) {
          digitalWrite(leds[j], LOW);
        }
        digitalWrite(leds[0], HIGH);
      } else if (distance < 100 && distance > 50) {
        digitalWrite(leds[0], LOW);
        digitalWrite(leds[2], LOW);
        digitalWrite(leds[3], LOW);
        digitalWrite(leds[4], LOW);
        digitalWrite(leds[1], HIGH);
      } else if (distance < 50 && distance > 25) {
        digitalWrite(leds[0], LOW);
        digitalWrite(leds[1], LOW);
        digitalWrite(leds[3], LOW);
        digitalWrite(leds[4], LOW);        
        digitalWrite(leds[2], HIGH);
      } else if (distance < 25 && distance > 10) {
        digitalWrite(leds[0], LOW);
        digitalWrite(leds[1], LOW);
        digitalWrite(leds[2], LOW);
        digitalWrite(leds[4], LOW);
        digitalWrite(leds[3], HIGH);
      } else if (distance < 10) {
        digitalWrite(leds[0], LOW);
        digitalWrite(leds[1], LOW);
        digitalWrite(leds[2], LOW);
        digitalWrite(leds[3], LOW);
        digitalWrite(leds[4], HIGH);
      }
    } else {
      Serial.println("");
      Serial.println("Repita contraseña");
    }
    delay(1000);
  }
}
