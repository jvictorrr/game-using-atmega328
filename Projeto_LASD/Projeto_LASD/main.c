/*
 * Projeto_LASD.c
 *
 * Created: 19/11/2020 10:30:13
 * Autores: João Victor Rodrigues Ramalho
	Matheus Cavalcante Rique 
 */ 

#include <avr/io.h>
#define F_CPU 16000000UL
#include <avr/interrupt.h>
#include <util/delay.h>

uint8_t i , j ;
uint8_t V[10] = {0x7E , 0X30 , 0X6D , 0X79 , 0X33 ,  0X5B , 0X5F , 0X70 , 0X7F ,  0X7B}; // display 7 segmentos


ISR(INT0_vect) //Decrementar 10s
{
	i = i - 1;
	PORTC = V[j];
	PORTB = V[i];
}

int main(void)
{
	// principal / interrupção

	DDRD = 0x00;
	PORTD = 0xff;
	DDRC = 0b11111111;
	DDRB = 0b11111111;
	
	EICRA = 0b00000011;
	EIMSK = 0b00000011;
	sei();

	// pwm
	TCCR0A = 0b10100011;
	TCCR0B = 0b00000101;
	OCR0A = 0;
	DDRD = (1<<6);
	
	
	while (1)
	{
		
		
		for (i=9; i>0; i--) //  display da dezena
		{
			PORTB =	V[i];
			for (j=9; j>0; j--) //display da unidade
			{
				PORTC =	V[j];
				_delay_ms(1000);
			}
		}
		if(i<=5 & j<=5) //buzzer pra quando perder
		{OCR0A=255;
		}
		else
		{
			OCR0A = 0;
		}
	}
}