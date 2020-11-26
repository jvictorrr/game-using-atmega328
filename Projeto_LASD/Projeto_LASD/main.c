/*
 * Projeto_LASD.c
 *
 * Created: 19/11/2020 10:30:13
 * Autores: João Victor Rodrigues Ramalho
			Matheus Cavalcante Rique 
 */ 

#define F_CPU 16000000UL
#define BAUD 9600
#define MYUBRR F_CPU/16/BAUD-1
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

uint8_t num_unidade=9, num_dezena=5; // Display será inicializado com 60 segundos 
uint16_t cont=0;
uint8_t V[10] = {0x7E , 0X30 , 0X6D , 0X79 , 0X33 ,  0X5B , 0X5F , 0X70 , 0X7F ,  0X7B}; // display 7 segmentos simulação


ISR(INT0_vect) //Decrementar 10s
{
	num_dezena= num_dezena- 1;
	PORTC = V[num_unidade];
	PORTB = V[num_dezena];
}

ISR(TIMER0_COMPA_vect){
	cont++; 
	if(cont==1000){ // Conta 1000 ms totalizando 1 segundo
		num_unidade--;
		if(num_unidade==0){
		num_unidade=9;
		num_dezena--;
		}

		cont=0;
	}
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
	//	TCCR0A = 0b10100011;
		//TCCR0B = 0b00000101;
	//	OCR0A = 0;
		//DDRD = (1<<6);
		
	// Timer 	
	TCCR0A = 0b00000010;
	TCCR0B = 0b00000011; // TC0 com prescaler=64
	OCR0A = 249; // ajusta o comparador do TC0 contar até 249
	TIMSK0 = 0b00000010; // Habilita a interrupcao na igualdade com OCR0A, sendo a cada 1ms = (64*(249+1)/16Mhz
	DDRD = (1<<6);
	
		while (1)
	{
		
		
	PORTC=V[num_unidade]; //
	PORTB=V[num_dezena]; //
	
	
/* pra quando acabar o tempo 


if ( (num_unidade ==0) && (num_dezena==0) )
{
nokia_lcd_set_cursor(0, 10);
nokia_lcd_write_string("Tempo",1);
nokia_lcd_set_cursor(0, 20);
nokia_lcd_write_string("Esgotado",1);
nokia_lcd_render();

{OCR0A=255;
}
else
{
	OCR0A = 0;
}

}
*/
	}
}



/* codigo display nokia 


	USART_Init(MYUBRR);
	
	nokia_lcd_clear(); //Limpa o LCD
	nokia_lcd_set_cursor(0, 20);
	nokia_lcd_write_string("Sala: 0%  ", 1);
	nokia_lcd_set_cursor(0, 10);
	nokia_lcd_write_string("Quarto: ON ",1);
	nokia_lcd_render();

*/