#include "mbed.h"
#include "arm_book_lib.h"

/*
 * El programa se fija en cada ciclo el estado de los pines para determinar las acciones
 * si el pin D2(GAS) o D3(TEMPERATURA) estan en alto enciende la alarma(LED1)
 * Si se da la combinacion de los botones necesaria, se apaga la alarma
 * Voy a crear los objetos detectors y codeButton de la clase BusIn ya que D2-D3 y D4-D5-D6-D7 no comparten
 * los mismos puertos entre si respectivamente
 * Para BusIn puedo seleccionar con que pines puedo armar el bus de pines y no necesariamente tienen que ser del mismo puerto
 */


void mostrarIO(int detectors, int buttons){
    
        printf("Gas/Temperatura: ");
        switch(detectors){
            case 0b00: printf("OFF/OFF\n"); break;
            case 0b01: printf("ON/OFF\n"); break;
            case 0b10: printf("OFF/ON\n"); break;
            case 0b11: printf("ON/ON\n"); break;
            default: printf("-\n");
        }

        printf("Codigo: %d\n",buttons);
        
}

int main()
{
    /*
     * DigitalIn gasDetector(D2);       
     * DigitalIn overTempDetector(D3); 
     */
    BusIn detectors(D2,D3) ;

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
        if ( detectors == 0b01 || detectors == 0b10 ) { // if ( gasDetector || overTempDetector ) {
            alarmState = ON;
        }

        alarmLed = alarmState;

        /*
         * BusIn read() devuelve un entero en donde cada posicion tiene un 1 o 0 y corresponde al pin
         * de esa posicion. En este caso deberia tener un 1 en las posiciones primeras dos posiciones (D4 y D5)
         * y un 0 en las siguientes dos posiciones (D6 y D7) para que el codigo introducido sea correcto 
         */
        if (codeButtons == 0b0011) { //if ( aButton && bButton && !cButton && !dButton) {
            alarmState = OFF;
        }

        // Muestro estado de salidas digitale y entradas digitales
        mostrarIO(detectors.read(),codeButtons.read());
        delay(50);
    }
}
