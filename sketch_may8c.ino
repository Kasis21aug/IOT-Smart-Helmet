#define BLYNK_TEMPLATE_ID "TMPL3JsxgokyV"
#define BLYNK_TEMPLATE_NAME "temp"
#define BLYNK_AUTH_TOKEN "VYXaOFFBi9CRHp-ZnIIb787LDSUpdEyi"

#define BLYNK_PRINT Serial
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>

/* Fill-in your Template ID (only if using Blynk.Cloud) */
#define BLYNK_TEMPLATE_ID   "TMPL3JsxgokyV"
#define gas A0
#define r1 D0
#define r2 D1
#define r3 D2
#define r4 D3
#define r5 D6
#define r6 D7
String data1;
#include "DHT.h"

#define DHTPIN D5     // Digital pin connected to the DHT sensor
#define DHTTYPE DHT11   // DHT 11

DHT dht(DHTPIN, DHTTYPE);

// You should get Auth Token in the Blynk App.
// Go to the Project Settings (nut icon).
char auth[] = "VYXaOFFBi9CRHp-ZnIIb787LDSUpdEyi";

// Your WiFi credentials.
// Set password to "" for open networks.
char ssid[] = "Iot2023";
char pass[] = "testing2023";

void setup()
{
  // Debug console
  Serial.begin(9600);
  pinMode(gas,INPUT);
    pinMode(r1,OUTPUT);
  pinMode(r2,OUTPUT);
      pinMode(r3,OUTPUT);
  pinMode(r4,OUTPUT);
   pinMode(r5,OUTPUT);
    pinMode(r6,OUTPUT);
   digitalWrite(r2,1);  
  digitalWrite(r1,1);
  digitalWrite(r3,1);  
  digitalWrite(r4,1);
  digitalWrite(r5,1);  
  digitalWrite(r6,1);
   dht.begin();
  Blynk.begin(auth, ssid, pass);
}

void loop()
{
int gassen1 = analogRead(gas);
float h = dht.readHumidity();
  float t = dht.readTemperature();
  float f = dht.readTemperature(true);
  if (isnan(h) || isnan(t) || isnan(f)) {
    Serial.println(F("Failed to read from DHT sensor!"));
    return;
  }
 
int gassen = map(gassen1,0,1023,0,100);
  // Compute heat index in Fahrenheit (the default)
  float hif = dht.computeHeatIndex(f, h);
  // Compute heat index in Celsius (isFahreheit = false)
  float hic = dht.computeHeatIndex(t, h, false);

   if ( t<38)
{
  digitalWrite(r1,0);
  digitalWrite(r2,1);
  digitalWrite(r3,1);
  Blynk.virtualWrite(V3,"Good");
  }
 if (t>38 && t<40)
{
  digitalWrite(r1,1);
  digitalWrite(r2,0);
  digitalWrite(r3,1);
  Blynk.virtualWrite(V3,"Modurate");
  }
   if (t>40 )
{
  digitalWrite(r1,1);
  digitalWrite(r2,1);
  digitalWrite(r3,0);
  Blynk.virtualWrite(V3,"High");
  }
 
  Serial.print("gas=");
  Serial.println(gassen);
  delay(200);


     if (gassen<=30)
{
  digitalWrite(r4,0);
  digitalWrite(r5,1);
  digitalWrite(r6,1);
  Blynk.virtualWrite(V2,"Good");
  }
 if (gassen>31 && gassen<50)
{
  digitalWrite(r4,1);
  digitalWrite(r5,0);
  digitalWrite(r6,1);
  Blynk.virtualWrite(V2,"Moderate");
  }
   if (gassen>51 && gassen<100 )
{
  digitalWrite(r4,1);
  digitalWrite(r5,1);
  digitalWrite(r6,0);
   Blynk.virtualWrite(V2,"high");
  }

 Blynk.virtualWrite(V0,t);
 Blynk.virtualWrite(V1,gassen);
 
 Blynk.run();
}
