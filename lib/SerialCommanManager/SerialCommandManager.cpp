#include "SerialCommandManager.h"

SerialCommandManager::SerialCommandManager(DS3231Manager& rtc)
    : rtcRef(rtc) {}

void SerialCommandManager::begin() {
    Serial.begin(115200);
    while (!Serial); // Esperar a que el puerto esté listo
    buffer = "";
    Serial.println("Inicialización completa. Puedes ingresar:");
    Serial.println("  SET=DD/MM/YYYY HH:MM");
    Serial.println("  ALARM=HH:MM");
    printPrompt();
}

void SerialCommandManager::printPrompt() {
    Serial.print("> ");
}

void SerialCommandManager::setInputCallback(std::function<void(bool)> callback) {
    onUserInputStateChange = callback;
}

void SerialCommandManager::update() {
    while (Serial.available()) {
        char c = Serial.read();

        if (c == '\r') continue;
        if (c == '\n') {
            Serial.println();
            processCommand(buffer);
            buffer = ""; 
            return;
        }

        if (c == '\b' || c == 127) {
            if (buffer.length() > 0) {
                buffer.remove(buffer.length() - 1);
                Serial.print("\b \b");
            }
        } else {
            buffer += c;
            Serial.print(c);
        }
    }
    // Timeout: si no se escribe nada en X tiempo  salta
    if (userIsTyping && (millis() - lastInputTime > INPUT_TIMEOUT_MS)) {
        userIsTyping = false;
        buffer = "";
        if (onUserInputStateChange) {
            onUserInputStateChange(false);
        }
        printPrompt();
    }
}

void SerialCommandManager::processCommand(const String& command) {
    if (command.length() == 0) return;

    if (rtcRef.setDateTime(command)) {
        Serial.println("\nFecha y hora actualizadas.");
    } else {
        int h, m;
        if (sscanf(command.c_str(), "ALARM=%d:%d", &h, &m) == 2) {
            rtcRef.setAlarm(h, m);
            Serial.println("\nAlarma configurada.");
        } else {
            Serial.println("\nComando no reconocido o inválido.");
        }
    }

    printPrompt();
}
