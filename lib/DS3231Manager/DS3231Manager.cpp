#include "DS3231Manager.h"

DS3231Manager::DS3231Manager() {}

void DS3231Manager::begin() {
    if (!rtc.begin()) {
        Serial.println("No se pudo encontrar el RTC");
        while (true); // Error crítico
    }

    if (rtc.lostPower()) {
        Serial.println("RTC sin alimentación, se ajusta la hora actual");
        rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
    }
}
void DS3231Manager::update() {
    // Por ahora puede estar vacío o tener lógica futura
}

DateTime DS3231Manager::now() {
    return rtc.now();
}

String DS3231Manager::formattedTime() {
    DateTime now = rtc.now();
    char buf[20];
    snprintf(buf, sizeof(buf), "%02d/%02d/%04d %02d:%02d",
             now.day(), now.month(), now.year(), now.hour(), now.minute());
    return String(buf);
}

bool DS3231Manager::setDateTime(const String& input) {
    if (!input.startsWith("SET=")) return false;

    String data = input.substring(4); // Salteamos "SET="
    int d, m, y, h, min;
    if (sscanf(data.c_str(), "%d/%d/%d %d:%d", &d, &m, &y, &h, &min) != 5) {
        Serial.println("Formato inválido. Usa SET=DD/MM/YYYY HH:MM");
        return false;
    }

    rtc.adjust(DateTime(y, m, d, h, min, 0));
    // Serial.println("Fecha y hora actualizadas.");
    return true;
}

void DS3231Manager::setAlarm(uint8_t hour, uint8_t minute) {
    alarmHour = hour;
    alarmMinute = minute;
    Serial.printf("Alarma programada a las %02d:%02d\n", alarmHour, alarmMinute);
}

bool DS3231Manager::checkAlarm() {
    DateTime now = rtc.now();
    return now.hour() == alarmHour && now.minute() == alarmMinute;
}
