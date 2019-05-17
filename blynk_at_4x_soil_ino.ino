// AT+UART_DEF=9600,8,1,0,0

//#define BLYNK_PRINT Serial
#include <ESP8266_Lib.h>
#include <BlynkSimpleShieldEsp8266.h>
#include <SimpleTimer.h>
#include <DHT.h>
#include <Adafruit_Sensor.h>


#define DHTPIN 9
#define DHTTYPE DHT22

DHT dht(DHTPIN, DHTTYPE);


char auth[] = "you code here";
char ssid[] = "your wifi SSID here";
char pass[] = "Wifi password here";

SimpleTimer timer;

#define EspSerial Serial1

#define ESP8266_BAUD 9600

ESP8266 wifi(&EspSerial);

const int soilPin1 = A0;
const int soilPowerPin1 = 5;
int soilVal1;

const int soilPin2 = A1;
const int soilPowerPin2 = 4;
int soilVal2;

const int soilPin3 = A2;
const int soilPowerPin3 = 3;
int soilVal3;

const int soilPin4 = A3;
const int soilPowerPin4 = 2;
int soilVal4;



const int boardLed = 17;

const int numReadings = 6;

int readings[numReadings];      // the readings from the analog input
int readIndex = 0;              // the index of the current reading
int total = 0;                  // the running total
int average = 70;                // the average


int notifyMe = 0;

void setup()
{

	EspSerial.begin(ESP8266_BAUD);
	delay(10);

	Blynk.begin(auth, wifi, ssid, pass);
	timer.setInterval(10000, check);
	dht.begin();
	pinMode(soilPin1, INPUT);
	pinMode(soilPin2, INPUT);
	pinMode(soilPin3, INPUT);
	pinMode(soilPin4, INPUT);
	pinMode(soilPowerPin1, OUTPUT);
	pinMode(soilPowerPin2, OUTPUT);
	pinMode(soilPowerPin3, OUTPUT);
	pinMode(soilPowerPin4, OUTPUT);

	pinMode(boardLed, OUTPUT);

//  digitalWrite(boardLed, HIGH);
}





void check()
{

	total = total - readings[readIndex];

	readings[readIndex] = (dht.readTemperature(true));

	total = total + readings[readIndex];

	readIndex = readIndex + 1;


	if (readIndex >= numReadings)
		{
			readIndex = 0;
		}

	average = total / numReadings;

	Blynk.virtualWrite(V10,average);

	Blynk.virtualWrite(V12,(dht.readHumidity()));
	delay(500);

	digitalWrite(soilPowerPin1, HIGH);
	delay(500);
	soilVal1 = (1024 - analogRead(soilPin1));
	Blynk.virtualWrite(V0, soilVal1);
	digitalWrite(soilPowerPin1, LOW);

	digitalWrite(soilPowerPin2, HIGH);
	delay(500);
	soilVal2 = (1024 - analogRead(soilPin2));
	Blynk.virtualWrite(V1, soilVal2);
	digitalWrite(soilPowerPin2, LOW);

	digitalWrite(soilPowerPin3, HIGH);
	delay(500);
	soilVal3 = (1024 - analogRead(soilPin3));
	Blynk.virtualWrite(V2, soilVal3);
	digitalWrite(soilPowerPin3, LOW);

	digitalWrite(soilPowerPin4, HIGH);
	delay(500);
	soilVal4 = (1024 - analogRead(soilPin4));
	Blynk.virtualWrite(V3, soilVal4);
	digitalWrite(soilPowerPin4, LOW);



//  uncomment if you want push notifications

//    if (soilVal < 150)
//      {
//        if (notifyMe = 0)
//          {
//             Blynk.notify("Dry Plants");
//             notifyMe = 1;
//          }
//      }
//    else
//      {
//        notifyMe = 0;
//      }

}




void loop()
{
	Blynk.run();
	timer.run();
}
