int leds[9]={2,3,4,5,6,7,8,9,10};
char  tecla = 0;
int index;
void setup() {
  Serial.begin(9600);
  for(int i=0; i<9; i++ ){
    pinMode(leds[i],OUTPUT);
  }
}

void loop() {
  if (Serial.available() > 0) {
    tecla=Serial.read();  
  }
  switch(tecla){
    case '1': 
              for(int i=0; i<2; i++){
                digitalWrite(leds[i],HIGH);  
              }
              delay(500);
              for(int i=0; i<2; i++){
                digitalWrite(leds[i],LOW);  
              }
              delay(500);
              for(int i=2; i<5; i++){
                digitalWrite(leds[i],HIGH);  
              }
              delay(500);
              for(int i=2; i<5; i++){
                digitalWrite(leds[i],LOW);  
              }
              delay(500);
              for(int i=5; i<9; i++){
                digitalWrite(leds[i],HIGH);  
              }
              delay(500);
              for(int i=5; i<9; i++){
                digitalWrite(leds[i],LOW);  
              }
              delay(500);
              break;
    case '2': 
              for(int i=0; i<2; i++){
                digitalWrite(leds[i],HIGH);  
              }
              delay(500);
              for(int i=2; i<5; i++){
                digitalWrite(leds[i],HIGH);  
              }
              delay(500);
              for(int i=5; i<9; i++){
                digitalWrite(leds[i],HIGH);  
              }
              delay(500);
              for(int i=0; i<9; i++){
                digitalWrite(leds[i],LOW);
              } 
              ;break;
    case '3':
              //Se encienden los diodos propuestos en el ejercicio y se mantiene
              //la espera de 0.5 segundos.
              index = 4;
              digitalWrite(leds[index],HIGH);
              delay(500);

              for(int i=0; i<4; i++){
                digitalWrite(leds[index-(i+1)],HIGH);
                digitalWrite(leds[index+(i+1)],HIGH);
                delay(500);
              }            

              ;break;
    case 'F': 
              for(int i=0; i<9; i++){
                digitalWrite(leds[i],LOW);
              }    
              ;break;
    }
}