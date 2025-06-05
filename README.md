# ESP32 + DS3231 Terminal Time Manager

Este proyecto usa un ESP32 conectado a un módulo RTC DS3231. Muestra fecha y hora por la terminal cada minuto. Se puede cambiar la fecha y la hora a través del comando SET= y el horario de activación de una alarma luminosa (Led interno del ESP32) a través del comando ALARM=.

## 🔧 Características

- ✅ Lectura y visualización de la hora actual desde el DS3231.
- ✅ Actualización única de fecha y hora mediante consola serial.
- ✅ Configuración de alarmas mediante consola (simulada con el LED interno).
- ✅ Prompt interactivo con entrada tipo shell.
- ✅ Estructura modular orientada a objetos.
- ✅ Código preparado para futura integración con pantalla Nextion.
- ✅ Uso de clases para encapsular lógica de hardware.
- ✅ Manejo de entrada de comandos no bloqueante.
- ✅ Integración básica de tiempo real con ESP32.

## 💻 Comandos por consola

SET=DD/MM/YYYY HH:MM          # Establece nueva fecha y hora
ALARM=HH:MM                   # Establece hora de alarma (enciende LED)


> Al recibir entrada del usuario, el sistema pausa el refresco automático de hora para permitir la escritura del comando.

## 📂 Estructura del código

```text
ds3231_test
├── lib
│   ├── DS3231Manager
│   │   ├── DS3231Manager.cpp
│   │   └── DS3231Manager.h
│   └── SerialCommandManager
│       ├── SerialCommandManager.cpp
│       └── SerialCommandManager.h
├── platformio.ini
├── README.md
└── src
    └── main.cpp


## 🔌 Conexiones

---------------------------------------------------------
| Componente | ESP32 GPIO                               |
|------------|------------------------------------------|
| DS3231 SDA | GPIO21                                   |
| DS3231 SCL | GPIO22                                   |
| LED        | Interno (GPIO2 en la mayoría de módulos) |
---------------------------------------------------------

## 📦 Requisitos PlatformIO

- ESP32 Dev Module
- Biblioteca `RTClib` de Adafruit
- Frecuencia I2C: 100 kHz
- Terminal serial: 115200 baudios

## 🧱 Futuras mejoras

- Integración con display Nextion.
- Soporte de múltiples alarmas.
- Guardado de configuración en memoria no volátil (EEPROM/Preferences).

📁 Proyecto desarrollado en PlatformIO con Visual Studio Code