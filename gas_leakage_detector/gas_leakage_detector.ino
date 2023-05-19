#define BLYNK_TEMPLATE_ID "TMPLsrSR_Saf"
#define BLYNK_DEVICE_NAME "Gas Leakage Detector"
#define BLYNK_AUTH_TOKEN "hl7JhuiZEIBHNRMfG-v1MG5eHsbaDydW"

#define BLYNK_PRINT Serial
#include <ESP8266Wifi.h>
#include <BlynkSimpleEsp8266.h>

// Auth Token
char auth[] = BLYNK_AUTH_TOKEN;

char ssid[] = "RAPTOR";
char pass[] = "ms960rnl";

int buzzer = D2;
int sensor = A0;
int led_green = D7;
int led_red = D6;

double sensor_limit = 600;

void setup() {
  pinMode(buzzer, OUTPUT);
  pinMode(sensor, INPUT);
  pinMode(led_green, OUTPUT);
  pinMode(led_red, OUTPUT);
  digitalWrite(led_green, LOW);
  digitalWrite(led_red, LOW);
  Serial.begin(115200);
  Blynk.begin(auth, ssid, pass);
}

void loop() {
  double sensor_value = analogRead(sensor);
  Serial.print("Gas Level: ");
  Serial.println(sensor_value);
  Blynk.virtualWrite(V1, sensor_value);

  if (sensor_value > sensor_limit) {
    digitalWrite(led_green, LOW);
    digitalWrite(led_red, HIGH);
    digitalWrite(buzzer, HIGH);
    delay(500);
    digitalWrite(buzzer, LOW);
    Blynk.notify("Alert!!! Gas Leakage Detected!!!");
	Blynk.email("****@gmail.com", "Alert!!! Gas Leakage Detected!!!");
    Blynk.logEvent("Alert!!! Gas Leakage Detected!!!");
  } else {
    digitalWrite(buzzer, LOW);
    digitalWrite(led_green, HIGH);
    digitalWrite(led_red, LOW);
  }
  delay(100);
  Blynk.run();
}
