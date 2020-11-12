#include <LiquidCrystal.h>

LiquidCrystal lcd(12,11,10,9,8,7);

int alt = 0;

int tanquegas = 0;

int pulsos;

int rpm;

float volts = 0.0;

long freq, tempo;

boolean pulso;

byte batesq[8]={B00000,B01100,B11111,B10000,B10110,B10000,B10000,B11111};

byte batdir[8]={B00000,B00110,B11111,B00101,B01111,B00101,B00001,B11111};

byte batdirlig[8]={B00000,B00110,B11111,B11011,B10001,B11011,B11111,B11111};

byte batesqlig[8]={B00000,B01100,B11111,B11111,B11001,B11111,B11111,B11111};

byte tanque[8]={B11111,B10001,B10111,B10101,B10001,B11111,B01110,B11111};

byte preto[8]={B11111,B11111,B11111,B11111,B11111,B11111,B11111,B11111};

void setup()
{
  pinMode(A0, INPUT);
  pinMode(A1, INPUT);
  Serial.begin(9600);
  
  pulso = HIGH;
  
  lcd.createChar(2,batesq);
  lcd.createChar(3,batdir);
  lcd.createChar(4,batesqlig);
  lcd.createChar(5,batdirlig);
  lcd.createChar(6,tanque);
  lcd.createChar(7,preto);

  lcd.begin(16,2);
  lcd.print("    L2M Soft    ");
  delay(2000);
  lcd.clear();
  lcd.print("  Iniciando...  ");
  delay(4000);
  lcd.clear();

  pinMode(13, OUTPUT);
  pinMode(2, INPUT);
  pinMode(4, INPUT);
}

void loop()
{
  tanquegas = analogRead(A0);
  alt = digitalRead(2);
  Serial.println(tanquegas);
  lcd.setCursor(0,1);
  lcd.write(6);
 
  if (alt == 0)
  {
    batlig();
    delay(500);
    batdesl();
    delay(500);
  }
  else {
    batdesl();
  }
  
  voltimetro();
  tacometro();
  
  if (tanquegas <= 140)
  {
    tanquevazio();
    lcd.setCursor(0,1);
    lcd.write(6);
    delay(500);
    lcd.setCursor(0,1);
    lcd.print(" ");
    delay(500);  
  } else {
    if (tanquegas <= 220)
    {
      tanquereserva();
    } else {
      if (tanquegas <= 390)
      {
        tanque1_4();
      } else {
        if (tanquegas <= 500)
        {
          tanquemeio();
        } else {
          if (tanquegas <= 620)
          {
            tanque3_4();
          } else {
            if (tanquegas <= 680)
            {
              tanquecheio();
            }
          }
        }
      }
    }
  }
}

void batlig()
{
  lcd.setCursor(8,1);
  lcd.write(4);
  lcd.setCursor(9,1);
  lcd.write(5);
}

void batdesl()
{
  lcd.setCursor(8,1);
  lcd.write(2);
  lcd.setCursor(9,1);
  lcd.write(3);
}

void tanquecheio()
{
  lcd.setCursor(1,1);
  lcd.print("v|||c");

}

void tanque3_4()
{
  lcd.setCursor(1,1);
  lcd.print("v||| ");
}

void tanquemeio()
{
  lcd.setCursor(1,1);
  lcd.print("v||  ");  
}

void tanque1_4()
{
  lcd.setCursor(1,1);
  lcd.print("v|   ");
}

void tanquereserva()
{
  lcd.setCursor(1,1);
  lcd.print("v    ");  
}

void tanquevazio()
{
  lcd.setCursor(1,1);
  lcd.print("     ");  
}

void voltimetro()
{
  volts = analogRead(1)*(5.0/1023.0);
  volts = volts*4.9;
  
  lcd.setCursor(10,1);
  lcd.print(volts);
  lcd.setCursor(15,1);
  lcd.print("V");
}

void tacometro()
{
  lcd.setCursor(0,0);
  lcd.print("RPM:");
  tempo = millis();
  if(digitalRead(4) == HIGH)
  {
    if(pulso == HIGH)
    {
      pulsos = pulsos + 1;
    }

    pulso=LOW;

  }
  else{
    pulso=HIGH;
  }

  if(tempo%500==0){
    freq = pulsos/0.5;

    rpm = freq * 20 ;
    
    lcd.setCursor(4,0);
    lcd.print("            ");   
    lcd.setCursor(4,0);
    lcd.print(rpm);
       
    pulsos=0;
  }
}
