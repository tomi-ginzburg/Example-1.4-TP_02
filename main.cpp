#+include "mbed.h"
#include "arm_book_lib.h"

/*
 * El programa se fija en cada ciclo el estado de los pines para determinar las acciones
 * si el pin D2(GAS) o D3(TEMPERATURA) estan en alto enciende la alarma(LED1)
 * Si se da la combinacion de los botones necesaria, se apaga la alarma
 * Para D2 y D3 puedo usar la clase PortIn
 * Para D4-D7 puedo usar la clase BusIn
 */

int main()
{
    /* Cambio los pines a D0 y D1 para que sean del mismo puerto (PORTG)
     * DigitalIn gasDetector(D2);       Pasa al D0=PG_9
     * DigitalIn overTempDetector(D3);  Pasa al D1=PG_14
     */
    PortIn detectors(PortG,0x00004200) //0x00004200 seria un 1 en P14 y 1 en P9

    /*
     * DigitalIn aButton(D4);
     * DigitalIn bButton(D5);
     * DigitalIn cButton(D6);
     * DigitalIn dButton(D7);
     */
    BusIn codeButtons(D4,D5,D6,D7);

    DigitalOut alarmLed(LED1);

    /*
     * gasDetector.mode(PullDown);
     * overTempDetector.mode(PullDown);
     */
    detectors.mode(PullDown);

    /*
     * aButton.mode(PullDown);
     * bButton.mode(PullDown);
     * cButton.mode(PullDown);
     * dButton.mode(PullDown);
     */
    codeButtons.mode(PullDown);
    
    alarmLed = OFF;

    bool alarmState = OFF;

    while (true) {

        /*
         * PortIn read() devuelve
         */
        if ( detectors ) { // if ( gasDetector || overTempDetector ) {
            alarmState = ON;
        }

        alarmLed = alarmState;

        /*
         * BusIn read() devuelve un entero en donde cada posicion tiene un 1 o 0 y corresponde al pin
         * de esa posicion. En este caso deberia tener un 1 en las posiciones primeras dos posiciones (D4 y D5)
         * y un 0 en las siguientes dos posiciones (D6 y D7) para que el codigo introducido sea correcto 
         */
        if (codeButtons == 0011) { //if ( aButton && bButton && !cButton && !dButton) {
            alarmState = OFF;
        }
    }
}