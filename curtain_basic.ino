#ifdef __cplusplus
extern "C" {
#endif
  uint8_t temprature_sens_read();
#ifdef __cplusplus
}
#endif
uint8_t temprature_sens_read();

#define BLYNK_TEMPLATE_ID "TMPL3PXJLz5So"
#define BLYNK_TEMPLATE_NAME "Smart Curtain"
#define BLYNK_AUTH_TOKEN "eyWj3htdEYNt0uS-qXlLpHlVFEPkOT_Q"

#define BLYNK_PRINT Serial
#define touch 12
#define motorPin1 27
#define motorPin2 26
#define enablePin 14

#include <WiFi.h>
#include <WiFiClient.h>
#include <BlynkSimpleEsp32.h>

char ssid[] = "SHUBHAM";
char pass[] = "shubhamskg";

BlynkTimer timer;
BLYNK_WRITE(V9) {
  int value = param.asInt();
 analogWrite(enablePin, 255);
 
  if (value >= 10 && value <= 35) {
    Serial.println("Curtain Up");
    digitalWrite(motorPin1, HIGH);
    digitalWrite(motorPin2, LOW);
    delay(17400);
    Blynk.virtualWrite(V5, 0);
    Blynk.virtualWrite(V4, 1);
    // Stop the DC motor
    Serial.println("Motor stopped");
    digitalWrite(motorPin1, LOW);
    digitalWrite(motorPin2, LOW);

  } else {
    Serial.println("Curtain Down");
    digitalWrite(motorPin1, LOW);
    digitalWrite(motorPin2, HIGH);
    delay(17400);
    Blynk.virtualWrite(V4, 0);
    Blynk.virtualWrite(V5, 1);
    // Stop the DC motor
    Serial.println("Motor stopped");
    digitalWrite(motorPin1, LOW);
    digitalWrite(motorPin2, LOW);
  }
}
BLYNK_WRITE(V0) {
  int value = param.asInt();
  analogWrite(enablePin, 255);

  if (value == 1) {
    Serial.println("Curtain Up");
    digitalWrite(motorPin1, HIGH);
    digitalWrite(motorPin2, LOW);
    delay(17400);
    Blynk.virtualWrite(V5, 0);
    Blynk.virtualWrite(V4, 1);
    // Stop the DC motor
    Serial.println("Motor stopped");
    digitalWrite(motorPin1, LOW);
    digitalWrite(motorPin2, LOW);
    Blynk.virtualWrite(V0, 0);
  }
}
BLYNK_WRITE(V1) {
  int value = param.asInt();
  analogWrite(enablePin, 255);
  if (value == 1) {
    Serial.println("Curtain Down");
    digitalWrite(motorPin1, LOW);
    digitalWrite(motorPin2, HIGH);
    delay(17400);
    Blynk.virtualWrite(V4, 0);
    Blynk.virtualWrite(V5, 1);
    // Stop the DC motor
    Serial.println("Motor stopped");
    digitalWrite(motorPin1, LOW);
    digitalWrite(motorPin2, LOW);
    Blynk.virtualWrite(V1, 0);
  }
}

BLYNK_CONNECTED() {
  // Change Web Link Button message to "Congratulations!"
  Blynk.setProperty(V3, "offImageUrl", "https://img.fruugo.com/product/8/67/160436678_max.jpg");
  Blynk.setProperty(V3, "onImageUrl", "https://www.ovio.io/wp-content/uploads/2018/10/controller-en.jpg");
  Blynk.setProperty(V3, "url", "#");
}

void myTimerEvent() {
  int h = 0;
  float t = 0;
  motor();
  Blynk.virtualWrite(V2, millis() / 1000);
  h = hallRead();
  t = ((temprature_sens_read() - 32) / 1.8);
  Blynk.virtualWrite(V8, h);
  Blynk.virtualWrite(V7, t);
  motor();
  Blynk.virtualWrite(V2, millis() / 1000);
}

void setup() {
  // Debug console
  Serial.begin(115200);

  Blynk.begin(BLYNK_AUTH_TOKEN, ssid, pass);

  // Setup a function to be called every second
  timer.setInterval(1000L, myTimerEvent);
  pinMode(touch, INPUT);
  pinMode(motorPin1, OUTPUT);
  pinMode(motorPin2, OUTPUT);
  pinMode(enablePin, OUTPUT);
  digitalWrite(motorPin1, LOW);
  digitalWrite(motorPin2, LOW);
}
void motor() {
  int a = digitalRead(touch);
  Blynk.virtualWrite(V6, digitalRead(touch));
  if (a == 1) {
    Blynk.virtualWrite(V9, "touched");

    if (V4 == 1) {
      digitalWrite(motorPin1, HIGH);
      digitalWrite(motorPin2, LOW);
    } else {
      digitalWrite(motorPin1, LOW);
      digitalWrite(motorPin2, HIGH);
    }
  } else {
    // Serial.println("untouched");
    digitalWrite(motorPin1, LOW);
    digitalWrite(motorPin2, LOW);
  }
}
void loop() {
  Blynk.run();
  timer.run();
  Blynk.virtualWrite(V9, "Connected");
}
