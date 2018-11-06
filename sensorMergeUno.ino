#include "Wire.h"
#include "SD.h"
#include "SPI.h"
//#include "Adafruit_BMP085.h"
//Adafruit_BMP085 MySensor;
//#include "DHT.h"
//#define DHTPIN 4
//#define DHTTYPE DHT22
//DHT dht(DHTPIN, DHTTYPE);


float tempC;
float tempF;
float pressure;
float humidity;
float CTemperature;
float FTemperature;
float FHeatindex;
float CHeatindex;
float altitude;
int pin = 8;
int pin2 = 9;
unsigned long duration;
unsigned long starttime;
unsigned long sampletime_ms = 1000;
unsigned long lowpulseoccupancy = 0;
float ratio = 0;
float concentration = 0;
int files = 0;
String filepre = "LOGFILE.TXT";
char filename[50];
char filenametempc[50];
String filenames, filenametemp;
const int chipSelect = 4;
const int interval = 0;
int alt;
int counts = 0;
int times = 0;
String fileprint, fileprint2, fileprint3, fileprint4, fileprintc;

File logfile;

void error(String str)
{
  Serial.print("error: ");
  Serial.println(str);

  while(1);
}

void setup() {
  filenames.toCharArray(filename, 50);
  filepre.toCharArray(filename, 50);
  Serial.begin(9600);
//  MySensor.begin();
//  dht.begin();
  starttime = millis();
  Serial.print("logging to:  ");
  Serial.println(filename);
  pinMode(10, OUTPUT);
  pinMode(pin, INPUT);
  pinMode(A1, INPUT);
  if(files == 0)
  {
  
//  If working without SD port, comment out from here  
//
    if (!SD.begin(chipSelect)) {
      error("Card failed, or not present");
    }
    else
    {
      Serial.println("Its working. SD detected.");
    }

//  To here

    if(SD.exists(filename))
    {
      SD.remove(filename);
    } 
    logfile = SD.open(filename, FILE_WRITE);
  }
  if(logfile or files > 0)
  {
    Serial.println("File exists\n");
  }

//  If working without SD port, comment out from here

  else
  {
    Serial.println("File couldn't be made.");
    while(1);
  }

  logfile.flush();

//  To here
}

void loop() {
  times = times + 1;
//  alt = 101940;
  delay(sampletime_ms);
//  tempC = MySensor.readTemperature();
//  tempF = tempC*1.8+32;
//  pressure = MySensor.readPressure();
//  altitude = MySensor.readAltitude(101940);
//  humidity = dht.readHumidity(true);
//  CTemperature = dht.readTemperature(false);
//  FTemperature = dht.readTemperature(true);
//  FHeatindex = dht.computeHeatIndex(FTemperature, humidity);
//  CHeatindex = dht.computeHeatIndex(CTemperature, humidity, false);

//  duration = pulseIn(pin, LOW);                                                        
  duration = analogRead(A1);
  lowpulseoccupancy += duration; 
  counts = counts + 1;
  ratio = lowpulseoccupancy/(sampletime_ms * 10);
  concentration = 1.1*pow(ratio,3)-3.8*pow(ratio,2)+520*ratio+0.62;
//    fileprint = "Barometric Pressure: " + String(pressure) + " Pa.\n";
//    fileprint2 = "Temperature: " + String(tempF) + " degrees F.\n";
//  fileprint3 = "Altitude: " + String(altitude) + " meters.\n";
  fileprint4 = String(lowpulseoccupancy) + ", " + String(ratio) + ", " + String(concentration) + "\n";
  fileprintc = "counts: " + String(counts);

// Makes new file every 150 loops:

//    if(counts % 150 == 0)
//    {
//      files = files + 1;
//      logfile.close();*+
//      setup();
//    }


  Serial.println(fileprintc);
//    Serial.print(fileprint);
//    Serial.print(fileprint2);
 // Serial.print(fileprint3);
  Serial.println(fileprint4);
//    Serial.println(duration);

//  Serial.println(analogRead(A1));
//  If working without SD port, comment out from here
  
  logfile.println(fileprintc);
//    logfile.print(fileprint);
//    logfile.print(fileprint2);
//    logfile.print(fileprint3);
  logfile.println(fileprint4);


//  To here

  lowpulseoccupancy = 0;
  starttime = millis();

//  If working without SD port, comment out from here
  
  logfile.flush();

//  To here
}
