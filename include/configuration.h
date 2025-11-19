/* 
Parámetros generales del firmware: configuraciones del usuario, constantes de hardware, valores APRS/LoRa, 
composición del Beacon, display, batería, Wifi, telemetría, notificaciones, bluetooth.
 */

#ifndef CONFIGURATION_H_
#define CONFIGURATION_H_

#include <Arduino.h>
#include <vector>
#include <FS.h>

class WiFiAP {
public:
    bool    active;
    String  password;
};

class Beacon {
public:
    String  callsign;
    String  symbol;
    String  overlay;
    String  comment;
    bool    smartBeaconActive;
    byte    smartBeaconSetting;
    String  micE;
    bool    gpsEcoMode;
    String  profileLabel;
    // NUEVOS PARÁMETROS PARA MODO ESTÁTICO
    bool    staticMode;              // true = pecera fija, false = móvil GPS
    int     staticBeaconInterval;    // Minutos entre transmisiones en modo estático
};

class Display {
public:
    bool    showSymbol;
    bool    ecoMode;
    int     timeout;
    bool    turn180;
};

class Battery {
public:
    bool    sendVoltage;
    bool    voltageAsTelemetry;
    bool    sendVoltageAlways;
    bool    monitorVoltage;
    float   sleepVoltage;
};

class Winlink {
public:
    String  password;
};

class Telemetry {
public:
    bool    active;
    bool    sendTelemetry;
    float   temperatureCorrection;
};

class Notification {
public:
    bool    ledTx;
    int     ledTxPin;
    bool    ledMessage;
    int     ledMessagePin;
    bool    ledFlashlight;
    int     ledFlashlightPin;
    bool    buzzerActive;
    int     buzzerPinTone;
    int     buzzerPinVcc;
    bool    bootUpBeep;
    bool    txBeep;
    bool    messageRxBeep;
    bool    stationBeep;
    bool    lowBatteryBeep;
    bool    shutDownBeep;
};

class LoraType {
public:
    long    frequency;
    int     spreadingFactor;
    long    signalBandwidth;
    int     codingRate4;
    int     power;
};

class PTT {
public:
    bool    active;
    int     io_pin;
    int     preDelay;
    int     postDelay;
    bool    reverse;
};

class BLUETOOTH {
public:
    bool    active;
    String  deviceName;
    bool    useBLE;
    bool    useKISS;
};

// NUEVA CLASE PARA DEEPSLEEP
class DeepSleep {
public:
    bool    enabled;                 // Activar/desactivar DeepSleep
    int     sleepTimeMinutes;        // Minutos de sleep (predeterminado: 5)
    float   tempThresholdHigh;       // °C para alerta alta (predeterminado: 30.0)
    float   tempThresholdLow;        // °C para alerta baja (predeterminado: 18.0)
    float   waterLevelThreshold;     // % mínimo de agua (predeterminado: 30.0)
};


class Configuration {
public:

    WiFiAP                  wifiAP;
    std::vector<Beacon>     beacons;  
    Display                 display;
    Battery                 battery;
    Winlink                 winlink;
    Telemetry               telemetry;
    Notification            notification;
    std::vector<LoraType>   loraTypes;
    PTT                     ptt;
    BLUETOOTH               bluetooth;
    DeepSleep               deepSleep;  // NUEVO: Configuración de DeepSleep
    
    bool    simplifiedTrackerMode;
    int     sendCommentAfterXBeacons;
    String  path;
    String  email;
    int     nonSmartBeaconRate;
    int     rememberStationTime;
    int     standingUpdateTime;
    bool    sendAltitude;
    bool    disableGPS;
    bool    acceptOwnFrameFromTNC;

    void init();
    void writeFile();
    Configuration();
    bool validateConfigFile(const String& currentBeaconCallsign);
    bool validateMicE(const String& currentBeaconMicE);

private:
    bool readFile();
};

#endif