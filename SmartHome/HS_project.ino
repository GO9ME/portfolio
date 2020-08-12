
/*
  WiFiEsp test: ClientTest
  http://www.kccistc.net/
  작성일 : 2019.12.17
  작성자 : IoT 임베디드 KSH
*/
#define DEBUG
//#define DEBUG_WIFI
#define AP_SSID "embsystem"
#define AP_PASS "embsystem0"
#define SERVER_NAME "192.168.1.41"
#define SERVER_PORT 5000
#define LOGID "HS_ARD"
#define PASSWD "PASSWD"

#define CDS_PIN A0
#define WIFITX 7  //7:TX -->ESP8266 RX
#define WIFIRX 6 //6:RX-->ESP8266 TX
#define DHTPIN 11 //온습도
//#define LED_TEST_PIN 12
//#define LED_BUILTIN_PIN 13

#define DHTTYPE DHT11   // DHT11,DHT21, DHT22

#define CMD_SIZE 50
#define ARR_CNT 5

#include "DHT.h"
#include "WiFiEsp.h"
#include "SoftwareSerial.h"
//#include <TimerOne.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <Servo.h>
#include <MsTimer2.h> // Timerone 대신에 사용

LiquidCrystal_I2C lcd(0x27, 16, 2);

typedef struct {
  int year;
  int month;
  int day;
  int hour;
  int min;
  int sec;
} DATETIME;
DATETIME dateTime = {0};

Servo motor;
char sendBuf[CMD_SIZE];

bool timerIsrFlag = false;
bool updateTimeFlag = false;
bool motorFlag = false;
bool flameFlag = false;
bool moodFlag = false;

int safeMode = 0; // 0일경우 안전상태, 1일경우 위험

unsigned int secCount;
char getSensorId[10];
int sensorTime;
int cdsValue;
DHT dht(DHTPIN, DHTTYPE);
float temp = 0.0;
float humi = 0.0;

SoftwareSerial wifiSerial(WIFIRX, WIFITX);
WiFiEspClient client;

char lcdLine1[17] = "Smart Home By HS";
char lcdLine2[17] = "WiFi Connecting!";

int redPin = 9;
int greenPin = 5;
int bluePin = 3;
int motorPin = 10;
int angle = 0;
int flameSensor = A2;
int led = 4; // 불꽃센서 상태알리는 led
int sensorVal = 0;

int moodstate = 0;

void setup()
{
  // put your setup code here, to run once:
  lcd.init();
  lcd.backlight();
  lcdDisplay(0, 0, lcdLine1);
  lcdDisplay(0, 1, lcdLine2);

  //  pinMode(LED_TEST_PIN, OUTPUT);    //D12
  //  pinMode(LED_BUILTIN_PIN, OUTPUT); //D13
  pinMode(redPin, OUTPUT); //빨강
  pinMode(greenPin, OUTPUT); //초록
  pinMode(bluePin, OUTPUT); //파랑
  pinMode(flameSensor, INPUT);
  pinMode(4, OUTPUT); // 불꽃센서 상태알리는 led

  Serial.begin(115200); //DEBUG

  dht.begin();
  wifi_Setup();
  motor.attach(motorPin);
  motor.write(0);

  //Timer1.initialize(1000000);
  //Timer1.attachInterrupt(timerIsr); // timerIsr to run every 1 seconds
  MsTimer2::set(1000, timerIsr);
  MsTimer2::start();
  motor.detach();
}

void loop() {
  // put your main code here, to run repeatedly:
  sensorVal = analogRead(flameSensor);
  if (sensorVal > 500 )
  {
    //lcdDisplay(0, 0, "Fire!");
    //digitalWrite(4, HIGH);
    flameFlag = true;
#ifdef DEBUG
    Serial.print("Sensor: ");
    Serial.print(sensorVal);
#endif
    safeMode = 1;
    sprintf(sendBuf, "[%s]HOMEMODE@%s\r\n", "[ALLMSG]", "WARNING");
    client.write(sendBuf, strlen(sendBuf));
    client.flush();
  } //sensorval
  else
  {
    digitalWrite(4, LOW);
    flameFlag = false; //flase  일때 safe  mode
    safeMode = 0;
  }

  if (client.available()) { // 데이터 받는게 있을 경우
    socketEvent();
  }

  if (timerIsrFlag)
  {
    
    if ( !flameFlag ) // 불이 안 날 경우
    {
      timerIsrFlag = false;

      if (!(secCount % 5))
      {
        if (!client.connected()) {
          lcdDisplay(0, 1, "Server Down");
          server_Connect();
        }
      }

      cdsValue = map(analogRead(CDS_PIN), 0, 1023, 0, 100); //조도 값

      if (!(secCount % 5))

      {
        humi = dht.readHumidity();
        temp = dht.readTemperature();
        sprintf(lcdLine2, "C:%02d T:%02d H:%02d", cdsValue, (int)temp, (int)humi);
        lcdDisplay(0, 1, lcdLine2);
#ifdef DEBUG
        Serial.print("Cds: ");
        Serial.print(cdsValue);
        Serial.print(" Humidity: ");
        Serial.print(humi);
        Serial.print(" Temperature: ");
        Serial.println(temp);
#endif
        moodstate = moodstate+1;  //1초마다 무드상태 증가
        if(moodstate == 7)  // 7초마다 리셋
        {
          moodstate = 0;
        }
        
      }

      lcd.print("Welcome to Smart Home");

      lcdDisplay(0, 0, lcdLine1);
      
    ///////////////////////////////////////////////////////////////////
    // 무드등 모드
    ///////////////////////////////////////////////////////////////////
      if ( moodFlag)
      {
        if ( moodstate == 1 )
        {
          setColor(255, 0, 0);
        
        }
        else if ( moodstate == 2 )
        {
          setColor(255, 50, 0);
        }
        else if ( moodstate == 3 )
        {
          setColor(255, 255, 0);
        }
        else if ( moodstate == 4 )
        {
          setColor(0, 255, 0);
        }
        else if ( moodstate == 5 )
        {
          setColor(0, 0, 255);
        }
        else if ( moodstate == 6 )
        {
          setColor(0, 5, 70);
        }
        else if ( moodstate == 7 )
        {
          setColor(100, 0, 255);
        }
      }
      else
      {
        setColor(0, 0, 0);
      }
    ///////////////////////////////////////////////////////////////////
    // sensor Time 마다 출력
    ///////////////////////////////////////////////////////////////////
      if (sensorTime != 0 && !(secCount % sensorTime ))
      {
        sprintf(sendBuf, "[%s]GETSENSOR@%d@%d@%d\r\n", getSensorId, cdsValue, (int)temp, (int)humi);
        /*
        char tempStr[5];
        char humiStr[5];
        dtostrf(humi, 4, 1, humiStr);  //50.0 4:전체자리수,1:소수이하 자리수
        dtostrf(temp, 4, 1, tempStr);  //25.1
        
        sprintf(sendBuf, "[%s]GETSENSOR@%d@%s@%s\r\n", getSensorId, cdsValue, tempStr, humiStr);
        */
        client.write(sendBuf, strlen(sendBuf));
        client.flush();
      }
      
      sprintf(lcdLine1, "%02d.%02d  %02d:%02d:%02d", dateTime.month, dateTime.day, dateTime.hour, dateTime.min, dateTime.sec );
      //lcd.print("Welcome to Smart Home");
      lcdDisplay(0, 0, lcdLine1);

    ///////////////////////////////////////////////////////////////////
    // 모터 작동 
    ///////////////////////////////////////////////////////////////////
      if ( motorFlag )  
      {
        motor.detach();
        motorFlag = false;
      }
    }
    ///////////////////////////////////////////////////////////////////
    // 불이 났을 경우
    ///////////////////////////////////////////////////////////////////
    else if ( flameFlag ) 
    {
      digitalWrite(4, HIGH); // LED ON
      lcdDisplay(0, 1, "WARNING!!WARNING");
      client.print("[ALLMSG]WARNING\n");
    }
    ///////////////////////////////////////////////////////////////////
    // 첫 접속시 시간값 뱉어내
    ///////////////////////////////////////////////////////////////////
    if (updateTimeFlag) 
    {
      client.print("[GETTIME]\n");
      updateTimeFlag = false;
    }
  }
}
void socketEvent()
{
  int i = 0;
  char * pToken;
  char * pArray[ARR_CNT] = {0};
  char recvBuf[CMD_SIZE] = {0};
  int len;

  len = client.readBytesUntil('\n', recvBuf, CMD_SIZE);
  client.flush();
  //  recvBuf[len-1] = '\0';

#ifdef DEBUG
  Serial.print("recv : ");
  //  Serial.write(recvBuf,len);
  Serial.println(recvBuf);
#endif
  pToken = strtok(recvBuf, "[@]");

  while (pToken != NULL)
  {
    pArray[i] =  pToken;
    if (++i >= ARR_CNT)
      break;
    pToken = strtok(NULL, "[@]");
  }
  /*
    if (strcmp(pArray[0], "GETTIME"))
    {
    sprintf(lcdLine2, "%s %s", pArray[1], (len - strlen(pArray[0]) - 3) < 17 ? pArray[2] : "");
    lcdDisplay(0, 1, lcdLine2);
    }
  */
  if (!strncmp(pArray[1], " New", 4)) // New Connected
  {
    updateTimeFlag = true;
    return ;
  }
  else if (!strncmp(pArray[1], " Alr", 4)) //Already logged
  {
    client.stop();
    server_Connect();
    return ;
  }
  /*
  else if (!strcmp(pArray[1], "LIGHT"))
  {
    if (!strcmp(pArray[2], "ON")) {
      digitalWrite(5, HIGH);
    }
    else if (!strcmp(pArray[2], "OFF")) {
      digitalWrite(9, LOW);
      digitalWrite(5, LOW);
      digitalWrite(3, LOW);
    }
  }
  */
  ///////////////////////////////////////////////////////////////////
  // HOMEMODE SAFE
  ///////////////////////////////////////////////////////////////////
  else if (!strcmp(pArray[1], "HOMEMODE"))
  {
    if (!strcmp(pArray[2], "SAFE"))
    {
      flameFlag = false;
      safeMode = 0;
    }
    sprintf(sendBuf, "[%s]%s@%s\n","[HS_AVR]", pArray[1], pArray[2]);
  }
  ///////////////////////////////////////////////////////////////////
  // 현관문 제어
  ///////////////////////////////////////////////////////////////////
  else if (!strcmp(pArray[1], "DOOR"))
  {
    motorFlag = true;
    motor.attach(motorPin);
    if (!strcmp(pArray[2], "OPEN"))
    {
      angle = 0;
      motor.write(angle);
    }
    else if ( !strcmp(pArray[2], "CLOSE"))
    {
      angle = 90;
      motor.write(angle);
    }
    sprintf(sendBuf, "[%s]%s@%s\n", pArray[0], pArray[1], pArray[2]);
  }
  ///////////////////////////////////////////////////////////////////
  // 무드등 모드
  ///////////////////////////////////////////////////////////////////
  else if (!strcmp(pArray[1], "MOOD"))
  {
    if (!strcmp(pArray[2], "ON")) {
      moodFlag = true;
    }
    else if (!strcmp(pArray[2], "OFF")) {
      moodFlag = false;
    }
    sprintf(sendBuf, "[%s]%s@%s\n", pArray[0], pArray[1], pArray[2]);
  }
  ///////////////////////////////////////////////////////////////////
  // 조도, 온도, 습도 측정 값
  ///////////////////////////////////////////////////////////////////
  else if (!strncmp(pArray[1], "GETSENSOR", 9))
  {
    if (pArray[2] != NULL) {
      sensorTime = atoi(pArray[2]);
      strcpy(getSensorId, pArray[0]);
      return;
    } else {
      sensorTime = 0;
      sprintf(sendBuf, "[%s]%s@%d@%d@%d\n", pArray[0], "GETSENSOR", cdsValue, (int)temp, (int)humi);
    }
  }
  ///////////////////////////////////////////////////////////////////
  // 시간 값
  ///////////////////////////////////////////////////////////////////
  else if (!strcmp(pArray[0], "GETTIME"))
  { //GETTIME
    dateTime.year = (pArray[1][0] - 0x30) * 10 + pArray[1][1] - 0x30 ;
    dateTime.month =  (pArray[1][3] - 0x30) * 10 + pArray[1][4] - 0x30 ;
    dateTime.day =  (pArray[1][6] - 0x30) * 10 + pArray[1][7] - 0x30 ;
    dateTime.hour = (pArray[1][9] - 0x30) * 10 + pArray[1][10] - 0x30 ;
    dateTime.min =  (pArray[1][12] - 0x30) * 10 + pArray[1][13] - 0x30 ;
    dateTime.sec =  (pArray[1][15] - 0x30) * 10 + pArray[1][16] - 0x30 ;
#ifdef DEBUG
    sprintf(sendBuf, "Time %02d.%02d.%02d %02d:%02d:%02d\n\r", dateTime.year, dateTime.month, dateTime.day, dateTime.hour, dateTime.min, dateTime.sec );
    Serial.println(sendBuf);
#endif
    return;
  }
  ///////////////////////////////////////////////////////////////////
  // 서버에 데이터 전송
  ///////////////////////////////////////////////////////////////////
  client.write(sendBuf, strlen(sendBuf));
  client.flush();

#ifdef DEBUG
  Serial.print(", send : ");
  Serial.print(sendBuf);
#endif
}// SocketEvent

void timerIsr()
{
  //  digitalWrite(LED_BUILTIN_PIN,!digitalRead(LED_BUILTIN_PIN));
  timerIsrFlag = true;
  secCount++;
  clock_calc(&dateTime);
}

void clock_calc(DATETIME * dateTime)
{
  int ret = 0;
  dateTime->sec++;          // increment second

  if (dateTime->sec >= 60)                             // if second = 60, second = 0
  {
    dateTime->sec = 0;
    dateTime->min++;

    if (dateTime->min >= 60)                         // if minute = 60, minute = 0
    {
      dateTime->min = 0;
      dateTime->hour++;                               // increment hour
      if (dateTime->hour == 24)
      {
        dateTime->hour = 0;
        updateTimeFlag = true;
      }
    }
  }
}

void wifi_Setup()
{
  wifiSerial.begin(9600);
  wifi_Init();
  server_Connect();
}

void wifi_Init()
{
  do {
    WiFi.init(&wifiSerial);
    if (WiFi.status() == WL_NO_SHIELD) {
#ifdef DEBUG_WIFI
      Serial.println("WiFi shield not present");
#endif
    }
    else
      break;
  } while (1);

#ifdef DEBUG_WIFI
  Serial.print("Attempting to connect to WPA SSID: ");
  Serial.println(AP_SSID);
#endif
  while (WiFi.begin(AP_SSID, AP_PASS) != WL_CONNECTED) {
#ifdef DEBUG_WIFI
    Serial.print("Attempting to connect to WPA SSID: ");
    Serial.println(AP_SSID);
#endif
  }
  sprintf(lcdLine1, "ID:%s", LOGID);
  lcdDisplay(0, 0, lcdLine1);
  sprintf(lcdLine2, "IP:%d.%d.%d.%d", WiFi.localIP()[0], WiFi.localIP()[1], WiFi.localIP()[2], WiFi.localIP()[3]);
  lcdDisplay(0, 1, lcdLine2);

#ifdef DEBUG_WIFI
  Serial.println("You're connected to the network");
  printWifiStatus();
#endif
}

int server_Connect()
{
#ifdef DEBUG_WIFI
  Serial.println("Starting connection to server...");
#endif

  if (client.connect(SERVER_NAME, SERVER_PORT)) {
#ifdef DEBUG_WIFI
    Serial.println("Connected to server");
#endif
    client.print("["LOGID":"PASSWD"]");
  }
  else
  {
#ifdef DEBUG_WIFI
    Serial.println("server connection failure");
#endif
  }
}



void printWifiStatus()
{
  // print the SSID of the network you're attached to
  Serial.print("SSID: ");
  Serial.println(WiFi.SSID());

  // print your WiFi shield's IP address
  IPAddress ip = WiFi.localIP();
  Serial.print("IP Address: ");
  Serial.println(ip);

  // print the received signal strength
  long rssi = WiFi.RSSI();
  Serial.print("Signal strength (RSSI):");
  Serial.print(rssi);
  Serial.println(" dBm");
}

void lcdDisplay(int x, int y, char * str)
{
  int len = 16 - strlen(str);
  lcd.setCursor(x, y);
  lcd.print(str);
  for (int i = len; i > 0; i--)
    lcd.write(' ');
}
// 모터 구동
void servoAct(int angle)
{
  motor.write(angle);
}

//RGB 색깔 
void setColor(int red, int green, int blue)
{
  digitalWrite(redPin, red);
  digitalWrite(greenPin, green);
  digitalWrite(bluePin, blue);
}