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

enum States {start, s0, s1} state;
unsigned char combo[3];
unsigned char curr;

void tick() {
	switch(state) { //transitions
		case start:
			curr = 0x00;
			state = s0;
			PORTB = 0x00;
			break;
		case s0:
			if((PINA & 0x0F) == combo[curr]) {
				if(curr == 3) {
					PORTB = ((PORTB & 0x0F)) ? 0x00 : 0x01;
					curr = 0;	
				} else {
					state = s1;
				}
			} else if ((PINA & 0xFF) == 0x00) {
				state = s0;
			} else {
				curr = 0;
				state = s0;
				if ((PINA & 0xF0) == 0x80) {
					PORTB = 0x00;
				}
			}
			break;
		case s1:
			if((PINA & 0x0F) == 0x00) {
				state = s0;
				curr++;
			} else if((PINA & 0x0F) == combo[curr]) {
				state = s1;
			} else {
				state = s0;
				curr = 0;
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
		case s1:
		default:
			break;
	}
}


int main(void) {
    /* Insert DDR and PORT initializations */
	DDRA = 0x00; PORTA = 0xFF;
	DDRB = 0xFF; PORTB = 0x00;
	state = start;
	combo[0] = 0x04;
	combo[1] = 0x01;
	combo[2] = 0x02;
	combo[3] = 0x01;

	while(1) {
		tick();
	};	
    return 1;
}
