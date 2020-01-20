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

enum States {start, s0, s0_p, s0_r} state;


void tick() {
	switch(state) { //transitions
		case start:
			state = s0;
			PORTB = 0x00;
			break;
		case s0:
			if((PINA & 0x0F) == 0x04) {
				state = s0_p;
			} else {
				state = s0;
				if ((PINA & 0xF0) == 0x80) {
					PORTB = 0x00;
				}
			}
			break;
		case s0_p:
			if((PINA & 0x0F) == 0x00) {
				state = s0_r;
			} else if((PINA & 0x0F) == 0x04) {
				state = s0_p;
			} else {
				state = s0;
				if ((PINA & 0xF0) == 0x80) {
					PORTB = 0x00;
				}

			}
			break;
		case s0_r:
			if((PINA & 0x0F) == 0x02) {
				state = s0;
				PORTB = (PORTB & 0x0F) == 0x00 ?  0x01 : 0x00;
			} else if((PINA & 0x0F) == 0x00) {
				state = s0_r;	
			} else {
				state = s0;
				if ((PINA & 0xF0) == 0x80) {
					PORTB = 0x00;
				}
			}
			break;
		default:
			state = s0;
			PORTB = 0x00;
			break;
		break;
	}
	switch(state) { //actions (empty)
		case start:
		case s0:
		case s0_p:
		case s0_r:
		default:
			break;
	}
}


int main(void) {
    /* Insert DDR and PORT initializations */
	DDRA = 0x00; PORTA = 0xFF;
	DDRB = 0xFF; PORTB = 0x00;
	state = start;
	while(1) {
		tick();
	};	
    return 1;
}
