#pragma once
#include <Arduino.h>
#include "DS3231Manager.h"

class SerialCommandManager {
public:
    SerialCommandManager(DS3231Manager& rtc);
    void begin();
    void update();
    void setInputCallback(std::function<void(bool)> callback);
    void printPrompt();
private : DS3231Manager &rtcRef;
    String buffer;
    bool userIsTyping = false;
    unsigned long lastInputTime = 0;
    const unsigned long INPUT_TIMEOUT_MS = 10000;
    std::function<void(bool)> onUserInputStateChange;
    void processCommand(const String& command);
};
