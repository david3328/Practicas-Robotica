#include <DHT.h>
#include <Keypad.h>
#include <LiquidCrystal.h>

#define DHTPIN 7
#define DHTTYPE DHT11

DHT dht(DHTPIN, DHTTYPE);


char ukey;
String temp;
String hum;


const byte rowsCount = 4;
const byte columsCount = 4;
 
char keys[rowsCount][columsCount] = {
   { '1','2','3', 'A' },
   { '4','5','6', 'B' },
   { '7','8','9', 'C' },
   { '.','0','#', 'D' }
};
 
const byte rowPins[rowsCount] = { A0, A1, A2, A3 };
const byte columnPins[columsCount] = { 13, 10, 9, 8 };
 
Keypad keypad = Keypad(makeKeymap(keys), rowPins, columnPins, rowsCount, columsCount);

const int rs = 12,
          en = 11,
          d4 = 5, 
          d5 = 4, 
          d6 = 3, 
          d7 = 2;

          
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);
boolean itemperatura=false;
boolean ihumedad=false;
float lh;
float lt;
float h;
float t;

int op=5;

int ledamarillo=A4;
int ledrojo=A5;


void setup() { 
  pinMode(ledamarillo,OUTPUT);
  pinMode(ledrojo,OUTPUT);

  digitalWrite(ledamarillo,LOW);
  digitalWrite(ledrojo,LOW);
  
  lcd.begin(16,2);
  dht.begin();

}

void loop() {

 
    do{
      h = dht.readHumidity(); //Leemos la Humedad
      t = dht.readTemperature(); //Leemos la temperatura en grados Celsius
      if(ihumedad && h>lh){
        lcd.setCursor(0,0);
        lcd.print("ALERTA!!!       ");
        lcd.setCursor(0,1);
        lcd.print("HUMED: "),
        lcd.print(h);
        lcd.print("           ");
        digitalWrite(ledrojo,HIGH);
        delay(100);
        digitalWrite(ledrojo,LOW);
        delay(100);
        tone(6, 200, 300); 
      }
      if(itemperatura && t>lt){
        lcd.setCursor(0,0);
        lcd.print("ALERTA!!!       ");
        lcd.setCursor(0,1);
        lcd.print("TEMP: "),
        lcd.print(t);
        lcd.print("           ");
        digitalWrite(ledamarillo,HIGH);
        delay(100);
        digitalWrite(ledamarillo,LOW);
        delay(100);  
        tone(6, 200, 300); 
      }
    }while((ihumedad && h>lh) || (itemperatura && t>lt));
      
  
  char key = keypad.getKey();
  if (key) {
      switch(key){
        case '1': op=1;break;
        case '2': op=2;break;  
        case '3': op=3;break;  
        case '4': op=4;break;
        case '5': op=5;break;      
      }
   }

  switch(op){
    default:
          lcd.setCursor(0,0);
          lcd.print(" OPC 1 -- OPC 2 ");
          lcd.setCursor(0,1);
          lcd.print(" OPC 3 -- OPC 4 ");      
    break;

    case 1:
          lcd.setCursor(0,0);
          lcd.print("TEMP: ");
          lcd.print(t);
          lcd.print(" C       ");
          lcd.setCursor(0,1);
          lcd.print(" OPC 5 REGRESAR ");
    break;
    case 2:
          lcd.setCursor(0,0);
          lcd.print("HUMD: ");
          lcd.print(h);
          lcd.print("           ");
          lcd.setCursor(0,1);
          lcd.print(" OPC 5 REGRESAR ");
    break;
    case 3:          
          temp="";
          lcd.setCursor(0,1);
          lcd.print("ACEPTAR(A)  *(.)");
          do{            
            ukey = keypad.getKey();
            lcd.setCursor(0,0);
            lcd.print("INGRESE T: ");
            lcd.print(temp);
            lcd.print("           ");
            if(ukey and ukey!='A'){
              temp = temp + ukey;  
            }
          }while(ukey!='A');
          lt = temp.toFloat();
          itemperatura=true;
          op=5;
    break;
    case 4:
          hum="";
          lcd.setCursor(0,1);
          lcd.print("ACEPTAR(A)  *(.)");
          do{
            ukey = keypad.getKey();
            lcd.setCursor(0,0);
            lcd.print("INGRESE H: ");
            lcd.print(hum);
            lcd.print("           ");
            if(ukey and ukey!='A'){
              hum = hum + ukey;  
            }
          }while(ukey!='A');
          lh = hum.toFloat();
          ihumedad=true;
          op=5;          
    break;
  }

  
}
