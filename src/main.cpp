#include <Arduino.h>
#include "DS3231Manager.h"
#include "SerialCommandManager.h"

#define LED_BUILTIN 2

bool alarmTriggered = false;
const unsigned long PRINT_INTERVAL_MS = 60000;

DS3231Manager rtc;
SerialCommandManager serialCmd(rtc);
bool allowPrint = true;

void setup() {
    serialCmd.begin();
    pinMode(LED_BUILTIN, OUTPUT);
    digitalWrite(LED_BUILTIN, LOW);
    rtc.begin();
    serialCmd.setInputCallback([](bool inputActive) {
        allowPrint = !inputActive;
    });
}

void loop() {

    rtc.update();
    rtc.checkAlarm();
    serialCmd.update();

    static unsigned long lastPrint = 0;

    if (allowPrint && millis() - lastPrint >= PRINT_INTERVAL_MS) {
        lastPrint = millis();
        Serial.println(rtc.formattedTime());
        serialCmd.printPrompt();

        if (rtc.checkAlarm()) {
            digitalWrite(LED_BUILTIN, HIGH);
        } else {
            digitalWrite(LED_BUILTIN, LOW);
        }
    }
}
