/*	Author: vshuk003
 *  Partner(s) Name: Nicole Nguyen
 *	Lab Section:
 *	Assignment: Lab #  Exercise #
 *	Exercise Description: [optional - include for your own benefit]
 *
 *	I acknowledge all content contained herein, excluding template or example
 *	code, is my own original work.
 */
#include <avr/io.h>
#ifdef _SIMULATE_
#include "simAVRHeader.h"
#endif

enum States { start, s0, increment, decrement} state;


void tick() {
	switch(state) { //transitions
		case start:
			state = s0;
			PORTC = 0x07;
			break;
		case s0:
			if((PINA & 0x0F) == 0x01) {
				state = increment;
				if(PORTC < 9) PORTC++;
			} else if((PINA & 0x0F) == 0x02){
				state = decrement;
				if(PORTC != 0) PORTC--;
			} else if((PINA & 0x0F) == 0x03){
				state = s0;
				PORTC = 0;
			} else {
				state = s0;
			}
			break;
		case increment:
			if((PINA & 0x0F) == 0x01) {
				state = increment;
			} else if((PINA & 0x0F) == 0x00){
				state = s0;
			} else if((PINA & 0x0F) == 0x03) {
				state = s0;
				PORTC = 0;
			}
			break;
		case decrement:
			if((PINA & 0x0F) == 0x02) {
				state = decrement;
			} else if((PINA & 0x00F) == 0x00){
				state = s0;	
			} else if((PINA & 0x0F) == 0x03){
				state = s0;
				PORTC = 0;
			}
			break;
		break;
	}
	switch(state) { //actions (empty)
		case start:
		case s0:
		case decrement:
		case increment:
		default:
			break;
	}
}


int main(void) {
    /* Insert DDR and PORT initializations */
	DDRA = 0x00; PORTA = 0xFF;
	DDRC = 0xFF; PORTC = 0x07;
	state = start;
	while(1) {
		tick();
	};	
    return 1;
}
