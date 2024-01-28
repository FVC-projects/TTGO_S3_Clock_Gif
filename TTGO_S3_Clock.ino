// FVC Nov 2022
// NOTA: antes de efetuar upload
// selecionar Partition Scheme: "Huge APP (3MB No OTA)

#include "Arduino.h"
#include "TFT_eSPI.h"/* Please use the TFT library provided in the library. */
#include "Clock.h"
#include <WiFi.h>
#include "time.h"

TFT_eSPI lcd = TFT_eSPI();

TFT_eSprite spriteClock1 = TFT_eSprite(&lcd);
TFT_eSprite spriteClock2 = TFT_eSprite(&lcd);
TFT_eSprite spriteClock3 = TFT_eSprite(&lcd);
TFT_eSprite spriteClock4 = TFT_eSprite(&lcd);
TFT_eSprite spriteClock5 = TFT_eSprite(&lcd);
TFT_eSprite spriteClock6 = TFT_eSprite(&lcd);


const char* ssid     = "CUB QUARTOS 2 ANDAR";
const char* password = "WCUBWCUB";

const char* ntpServer = "pool.ntp.org";
const long  gmtOffset_sec = 0; //GMT +0
const int   daylightOffset_sec = 3600;

int fr=0;
int counter=0;

int hor1=0;
int hor2=0;
int min1=0;
int min2=0;
int segund=0;

char timeHour[3]="00";
char timeMin[3]="00";
char timeSec[3];
char m[12];
char y[5];
char d[3];
char dw[12];

int framemin1[]={26,27,48,49};
int framehor2[]={16,17,48,49};
int framehor1[]={11,12,48,49};

boolean atualiza=false;
int numatualiza=0;
int hora=0;
int minut=0;

void setup() {
  Serial.begin(115200);

  pinMode(15,OUTPUT); // necessário para funcionar com a bateria
  digitalWrite(15,1);

  lcd.init();
  lcd.fillScreen(TFT_ORANGE);
  lcd.setSwapBytes(true);
  lcd.setRotation(1);


   WiFi.begin(ssid, password);
   while (WiFi.status() != WL_CONNECTED) {
    lcd.setTextColor(TFT_BLACK,TFT_ORANGE);
    lcd.setFreeFont(&FreeMono12pt7b); 
    lcd.drawString("Connecting WiFi...",10,20);
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  lcd.fillScreen(TFT_ORANGE);
  lcd.setTextColor(TFT_BLACK,TFT_ORANGE);
  lcd.setFreeFont(&FreeMono12pt7b); 
  lcd.drawString("Wifi Connected!",10,20);
//  lcd.drawString("IP: "+WiFi.localIP(),10,30);
  Serial.println("WiFi connected.");
  delay(500);
//  lcd.fillScreen(TFT_ORANGE);

  configTime(gmtOffset_sec, daylightOffset_sec, ntpServer);

  spriteClock1.createSprite(72,107);
  spriteClock1.setSwapBytes(true);
  spriteClock2.createSprite(72,107);
  spriteClock2.setSwapBytes(true);
  spriteClock3.createSprite(72,107);
  spriteClock3.setSwapBytes(true);
  spriteClock4.createSprite(72,107);
  spriteClock4.setSwapBytes(true);
  spriteClock5.createSprite(226,25);
  spriteClock5.fillSprite(TFT_ORANGE);
  spriteClock5.fillRoundRect(0,0,226,25,4,TFT_WHITE);
  spriteClock5.setTextColor(TFT_ORANGE,TFT_WHITE);
  spriteClock5.setFreeFont(&FreeMonoBold12pt7b);

  spriteClock6.createSprite(72,35);
  spriteClock6.fillSprite(TFT_ORANGE);
  spriteClock6.setTextColor(0x5269,TFT_ORANGE);
  spriteClock6.setFreeFont(&FreeMonoBold18pt7b);

printLocalTime();
ecraini();

}


void loop() {

if(counter==0) {
 printLocalTime();
 segund=String(timeSec).toInt();
 
 if (segund==59) {
  hora = String(timeHour).toInt();
  minut = String(timeMin).toInt();
 }

 if (segund==0 && numatualiza==0) atualiza=true; //só atualiza 1 vez no segundo 0
 else if (segund>0) numatualiza=0;
}

counter++;
if(counter==50)
 counter=0;

 spriteClock6.fillSprite(TFT_ORANGE);
 spriteClock6.setTextColor(0x5269,TFT_ORANGE);
 spriteClock6.setFreeFont(&FreeMonoBold18pt7b);
 spriteClock6.drawString(String(timeSec),15,5);
 spriteClock6.pushSprite(239,130);

 spriteClock5.fillRoundRect(0,0,226,25,4,TFT_WHITE);
 spriteClock5.setTextColor(TFT_ORANGE,TFT_WHITE);
 spriteClock5.setFreeFont(&FreeMonoBold12pt7b);
 spriteClock5.drawString(String(d)+"."+String(m)+"."+String(y),30,3);
 spriteClock5.pushSprite(8,135);

 if (atualiza) atualizar(); //atualiza horas e minutos

}

void printLocalTime(){
  struct tm timeinfo;
  if(!getLocalTime(&timeinfo)){
    Serial.println("Failed to obtain time");
    return;
  }
  
  //The strftime() function convert a time specification to a string, controlled by a format specification. 
  strftime(timeHour,3, "%H", &timeinfo); //is replaced by the hour in 24-hour format [00,23]
  strftime(timeMin,3, "%M", &timeinfo); //is replaced by the minute as a decimal number [00,59]
  strftime(timeSec,3, "%S", &timeinfo); //is replaced by the second as a decimal number [00,59]
  strftime(y,5, "%Y", &timeinfo); //is replaced by the year with century, as a decimal number.
  strftime(m,12, "%b", &timeinfo); //is replaced by the locale's full month name.
  strftime(dw,10, "%A", &timeinfo); //is replaced by the locale's full weekday name.
  strftime(d,3, "%d", &timeinfo); //is replaced by the day of month as a decimal number [01,31].

}

void ecraini() {
  lcd.fillScreen(TFT_ORANGE);

  hora = String(timeHour).toInt();
  minut = String(timeMin).toInt();

if(hora>9) {
  hor1=(hora/10)-((hora%10)/10);
  hor2=hora%10;
  }
else {
  hor1=0;
  hor2=hora%10;
}

if(minut>9) {
  min1=(minut/10)-((minut%10)/10);
  min2=minut%10;
  }
else {
  min1=0;
  min2=minut%10;
}

spriteClock1.pushImage(0,0,72,109,frame[hor1*5]);
spriteClock2.pushImage(0,0,72,109,frame[hor2*5]);
spriteClock3.pushImage(0,0,72,109,frame[min1*5]);
spriteClock4.pushImage(0,0,72,109,frame[min2*5]);
spriteClock5.drawString(String(d)+"."+String(m)+"."+String(y),30,3);
spriteClock6.drawString(String(timeSec),15,5);

spriteClock1.pushSprite(8,15);
spriteClock2.pushSprite(85,15);
spriteClock3.pushSprite(162,15);
spriteClock4.pushSprite(239,15);
spriteClock5.pushSprite(8,135);
spriteClock6.pushSprite(239,130);

lcd.fillRoundRect(158,30,3,30,4,TFT_BLACK);
lcd.fillRoundRect(158,77,3,30,4,TFT_BLACK);

}

void atualizar() {
//atualiza horas e minutos

if(hora>9) {
  hor1=(hora/10)-((hora%10)/10);
  hor2=hora%10;
  }
else {
  hor1=0;
  hor2=hora%10;
}

if(minut>9) {
  min1=(minut/10)-((minut%10)/10);
  min2=minut%10;
  }
else {
  min1=0;
  min2=minut%10;
}

 for(int b=1;b<5;b++)
 {
     spriteClock4.pushImage(0,0,72,109,frame[(b+5*min2)]);
     spriteClock4.pushSprite(239,15);
   
     if (min2==9) {
        if (min1==5) {
         spriteClock3.pushImage(0,0,72,109,frame[(framemin1[b-1])]);
         spriteClock3.pushSprite(162,15);

         if (hor2==3 && hor1==2) {
          spriteClock2.pushImage(0,0,72,109,frame[(framehor2[b-1])]);
          spriteClock2.pushSprite(85,15);  
          spriteClock1.pushImage(0,0,72,109,frame[(framehor1[b-1])]);
          spriteClock1.pushSprite(8,15);

         } else {
           spriteClock2.pushImage(0,0,72,109,frame[(b+5*hor2)]);
           spriteClock2.pushSprite(85,15);
           if (hor2==9) {
            spriteClock1.pushImage(0,0,72,109,frame[(b+5*hor1)]);
            spriteClock1.pushSprite(8,15);  
           }
         } 

        } else { //min1<>5
          spriteClock3.pushImage(0,0,72,109,frame[(b+5*min1)]);
          spriteClock3.pushSprite(162,15);
        }
      }
  delay(50);
 }

if (min2==9) {
 spriteClock4.pushImage(0,0,72,109,frame[0]);
 spriteClock4.pushSprite(239,15);

  if (min1==5) {
   spriteClock3.pushImage(0,0,72,109,frame[0]);
   spriteClock3.pushSprite(162,15);
   
    if (hor2==3 && hor1==2) {
     spriteClock2.pushImage(0,0,72,109,frame[0]);
     spriteClock2.pushSprite(85,15);  
     spriteClock1.pushImage(0,0,72,109,frame[0]);
     spriteClock1.pushSprite(8,15);
    } else if (hor2==9) {
       spriteClock1.pushImage(0,0,72,109,frame[(hor1*5)+5]);
       spriteClock1.pushSprite(8,15);
       spriteClock2.pushImage(0,0,72,109,frame[0]);
       spriteClock2.pushSprite(85,15);
    } else {
       spriteClock2.pushImage(0,0,72,109,frame[(hor2*5)+5]);
       spriteClock2.pushSprite(85,15);
    }
  } else { //min1<>5
     spriteClock3.pushImage(0,0,72,109,frame[(min1*5)+5]);
     spriteClock3.pushSprite(162,15);
  }
} else { //min2<>9
   spriteClock4.pushImage(0,0,72,109,frame[(min2*5)+5]);
   spriteClock4.pushSprite(239,15);
}

numatualiza=1;
atualiza=false;

}
