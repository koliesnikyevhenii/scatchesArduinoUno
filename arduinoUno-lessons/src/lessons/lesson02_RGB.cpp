#include <Arduino.h>

#define R 3
#define G 5
#define B 6

void setColor(int r,int g,int b){ analogWrite(R,r); analogWrite(G,g); analogWrite(B,b); }

void setup() {
 pinMode(R, OUTPUT);
 pinMode(G, OUTPUT);
 pinMode(B, OUTPUT);
}

void loop() {
  setColor(255, 0, 0); delay(1000); // Red
  setColor(0, 255, 0); delay(1000); // Green
  setColor(0, 0, 255); delay(1000); // Blue
}

