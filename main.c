// *********************************************************************
// A5_lm75.c									Version 05.01.2025  hpw
// Frostwarner
// Dokumentation bcm2835:
// https://www.airspayce.com/mikem/bcm2835/index.html
// *********************************************************************
#include <stdio.h>					// Header fuer Ein-/Ausgaben
#include "bcm2835.h"					    // Header fuer Broadcom

#define		PIN				RPI_BPLUS_GPIO_J8_12						// LED-Pin
#define		I2C_ADR			0x48										// Adresse LM75

int main(void){
    if(bcm2835_init()==0) return 1;										// Library initalisieren

    // Pin als output einstellen

    // I2C initalisieren
    if (bcm2835_i2c_begin()==0) return 1;

    // I2C Adresse einstellen
    bcm2835_i2c_setSlaveAddress(I2C_ADR);

    // I2C Mode einstellen
    bcm2835_i2c_setClockDivider(BCM2835_SPI_CLOCK_DIVIDER_4096);


    printf("Temperatursensor LM75 wird ausgelesen...\n");
    // In Schleife
    for(int i = 0; i < 20; i++){
        uint8_t buf[2] = {0};

        // Daten lesen und ausgeben
        bcm2835_i2c_read(buf, 2);

        int temp = (buf[0] << 8) + buf[1];

        temp >>= 5;
        double temperature = temp * 0.125;
        printf("Aktuelle Temperatur: %.2f°C\n", temperature);

        // LED an- bzw. ausschalten
        if (temperature < 0){
            bcm2835_gpio_set(PIN);}
        else{
            bcm2835_gpio_clr(PIN);}

        // Pause
        bcm2835_delay(1000);
    }

    // I2C-Pins auf Standard
    bcm2835_i2c_end();

    if(bcm2835_close()==0) return 1;									// Library schließen
    return 0;							// Programmende
}
