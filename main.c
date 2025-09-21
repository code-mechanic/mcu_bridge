#include <xc.h>

// Configuration bits
#pragma config FOSC = HS    // Oscillator Selection bits (HS oscillator)
#pragma config WDTE = OFF   // Watchdog Timer Enable bit (WDT disabled)
#pragma config PWRTE = OFF  // Power-up Timer Enable bit (PWRT disabled)
#pragma config BOREN = OFF  // Brown-out Reset Enable bit (BOR disabled)
#pragma config LVP = OFF    // Low-Voltage Programming Enable bit (RB3 is digital I/O)
#pragma config CPD = OFF    // Data EEPROM Memory Code Protection (Data EEPROM is not code-protected)
#pragma config WRT = OFF    // Flash Program Memory Write Enable bits (Write protection off)
#pragma config CP = OFF     // Flash Program Memory Code Protection (Program memory is not code-protected)

#define _XTAL_FREQ 20000000  // Define system clock frequency (20 MHz)

void main() {
    TRISB = 0x00; // Set PORTB as output
    while (1) {
        PORTB = 0xFF; // Turn ON all PORTB LEDs
        __delay_ms(500);
        PORTB = 0x00; // Turn OFF all PORTB LEDs
        __delay_ms(500);
    }
}

