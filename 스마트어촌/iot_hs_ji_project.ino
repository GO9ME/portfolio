#include <SimpleDHT.h>
#include <MsTimer2.h>

#define DHTPIN 2
SimpleDHT11 dht11;

int water_pin = A5;
boolean sensor_read =0;
char msg[100];
int slope = 8;
int cnt = 0;
int old_water_slope;
int water_slope;
int cds = A0;
int led = 3; 
int new_water_level;
int new_cdsValue;

void setup() {
  pinMode(slope, INPUT);
  pinMode(led, OUTPUT);
  Serial.begin(9600);
  MsTimer2::set(1000,test);
  MsTimer2::start();
}

void loop() {
  
  water_slope = digitalRead(slope);
  
  if (sensor_read)
  {
    int water_level = analogRead(A5);
    new_water_level = map(water_level, 0, 950, 0, 100);
    byte temp, humi;
    int err = SimpleDHTErrSuccess;
    int cdsValue = analogRead(cds);
    new_cdsValue = map(cdsValue, 0, 1024, 0, 100);
    if (( err =dht11.read(DHTPIN, &temp, &humi, NULL)) != SimpleDHTErrSuccess)
    {   
      sprintf(msg, "%d:%d:%d:%d:%dL",(int)temp,(int)humi, new_water_level, cnt, new_cdsValue);
      Serial.print(msg);
      //Serial.write(msg);
    }
    sensor_read= 0;    
    cnt =0;
  }
    
    if(water_slope != old_water_slope)
    {
      cnt++;
      old_water_slope = water_slope;
    }
    
}

void test()
{
  sensor_read = !sensor_read;
}