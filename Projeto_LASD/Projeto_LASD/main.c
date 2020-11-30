/*
 * Projeto_LASD.c
 *
 * Created: 19/11/2020 10:30:13
 * Autores: João Victor Rodrigues Ramalho
			Matheus Cavalcante Rique 
 */ 

#include "biblioteca.h"

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
void USART_Init(unsigned int ubrr)
{
	UBRR0H = (unsigned char)(ubrr>>8); //Ajusta a taxa de transmissão
	UBRR0L = (unsigned char)ubrr;
	UCSR0B = (1<<RXCIE0)|(1<<RXEN0)|(1<<TXEN0); //Habilita o transmissor e o receptor
	UCSR0C = (1<<USBS0)|(3<<UCSZ00); //Ajusta o formato do frame: 8 bits de dados e 2 de parada
	
	DDRC = 0xFF; //Define a porta C como saída
}

int main(void)
{
	
			USART_Init(MYUBRR);
		
	// principal / interrupção
	DDRD = 0x00;
	PORTD = 0xff;
	DDRC = 0b11111111;
	DDRB = 0b11111111;
	
	EICRA = 0b00000011;
	EIMSK = 0b00000011;
	sei();

	// Timer 	
	TCCR0A = 0b00000010;
	TCCR0B = 0b00000011; // TC0 com prescaler=64
	OCR0A = 249; // ajusta o comparador do TC0 contar até 249
	TIMSK0 = 0b00000010; // Habilita a interrupcao na igualdade com OCR0A, sendo a cada 1ms = (64*(249+1)/16Mhz
	DDRD = (1<<6);
	
	  nokia_lcd_init(); //Inicia o LCD
	  nokia_lcd_clear(); //Limpa o LCD
	  nokia_lcd_render(); 
	  
	
		while (1)
	{
		game_running_display();
	}
}

