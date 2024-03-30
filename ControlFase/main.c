/*************************************
 * main.c                            *
 *                                   *
 * Created: 3/29/2024 3:36:20 PM     *
 * Author: Gerson Yaser              *
 * Fase Control						 *
 *                                   *
 * Device: ATmega328P				 *
 * Frequency: 8 MHz to 5V            *
 * Test: Make on Breadboard			 *
 *************************************/ 

/* Directives */
#define F_CPU 8000000UL
#include <xc.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

/* Statements */
uint8_t fase_control = 9;
uint8_t counter = 0;

/* Main function */
int main(void)
{
    cli(); /* Global interruption clear */
	
	/* PCICR – Pin Change Interrupt Control Register */
	PCICR |= (1 << PCIE2);
	/* PCMSK2 – Pin Change Mask Register 2 */
	PCMSK2 |= (1 << PCINT16); /* Pin D0 */
	
	/* EICRA – External Interrupt Control Register A */
	EICRA |= ((1 << ISC11) | (1 << ISC01)); /* The falling edge of INT1 and INT0 generates an interrupt request */
	/* EIMSK – External Interrupt Mask Register */
	EIMSK |= ((1 << INT1) | (1 << INT0)); /* PIN D2 & PIN D3 */
	
	DDRC |= (1 << DDC5); /* Trigger in Pin C5 */
	
	sei (); /* Global interruption enable */
	
	while(1)
    {
        //TODO:: Please write your application code 
    }
}

/* Push button UP */
ISR (INT0_vect)
{
	fase_control--;
	if (fase_control <= 1)
	{
		fase_control = 1;
	}
}
/* Push button DOW */
ISR (INT1_vect)
{
	fase_control++;
	if (fase_control >= 9)
	{
		fase_control = 9;
	}
}

/* Zero crossing */
ISR (PCINT2_vect)
{
	for (counter = 0; counter < fase_control; counter++)
	{
		_delay_us(925);
	}
	
	/* Trigger */
	PORTC |= (1 << PORTC5);
	_delay_us(50);
	PORTC &= ~(1 << PORTC5);
}