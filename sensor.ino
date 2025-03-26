#include <PulseSensorPlayground.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
const int PulseWire = 0;
const int LED = LED_BUILTIN;
int Threshold = 512;

PulseSensorPlayground pulseSensor;
LiquidCrystal_I2C lcd(0x27, 16, 2);
void setup() {
 Serial.begin(115200);
 lcd.init(); // Initialize the LCD
 lcd.backlight(); // Turn on the backlight
 lcd.setCursor(0, 0);
 lcd.print("Initializing...");
 pulseSensor.analogInput(PulseWire);
 pulseSensor.blinkOnPulse(LED);
 pulseSensor.setThreshold(Threshold);
 if (pulseSensor.begin()) {
 Serial.println("PulseSensor initialized!");
 lcd.setCursor(0, 0);
 lcd.print("Pulse Sensor Ready");
 } else {
 Serial.println("PulseSensor initialization failed!");
 lcd.setCursor(0, 0);
 lcd.print("Sensor Error!");
 }
 delay(2000); // Display message for 2 seconds
 lcd.clear();
}
void loop() {
 if (pulseSensor.sawStartOfBeat()) {
 int myBPM = pulseSensor.getBeatsPerMinute();

 lcd.setCursor(0, 0);
 lcd.print("Heart Rate: "); // Clear previous data with spaces
 lcd.setCursor(0, 1);
 lcd.print("BPM: ");
 lcd.print(myBPM);
 lcd.print(" "); // Clear trailing digits
 }
 delay(20);
}