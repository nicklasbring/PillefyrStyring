# PillefyrStyring
## Temperaturovervågning med GSM alarm og kommandoer 

Jeg har lavet en styring til et fyr, som skal måle temperaturer fra fremløbsrøret på et pillefyr. 
Fyret har det nemlig med at gå ud, så med styringen kan man få en sms så snart det sker. 
Den indeholder også 2 kommandoer. Hvis man skriver 'status' til styringen, får man en besked med temperaturen.
Den anden kommando kan genstarte fyret og derved få det til at køre igen. Hvis man skriver 'genstart', vil en servo trykke off/on
på knappen.

**OBS. værdierne hvor styringen vil sende en besked er kun sat til 30 grader for at tjekke funktionanliteten inden installationen.
Det samme med servoen som selvfølgelig også skal have justeret dens endpoints.** 

#### Tilbehør brugt:
* Arduino Nano
* Breadboard
* GSM modul (SIM-900)
* High torque servo
* Temperaturmåler
* 5k resistor

#### Libraries brugt:
* OneWire.h
* DallasTemperature.h
* SoftwareSerial.h
* Servo.h




