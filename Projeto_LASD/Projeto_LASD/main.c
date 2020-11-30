/*
* Projeto_LASD.c
*
* Created: 19/11/2020 10:30:13
* Autores: João Victor Rodrigues Ramalho
Matheus Cavalcante Rique
*/

#include "biblioteca.h"

uint8_t num_unidade=9, num_dezena=5; // Display será inicializado com 60 segundos
uint8_t start_end=0; // Start =1, end=0
uint8_t dificuldade=0;
uint8_t contador=99;
uint16_t cont=0;
uint8_t start_count=0;

//uint8_t V[10] = {0x7E , 0X30 , 0X6D , 0X79 , 0X33 ,  0X5B , 0X5F , 0X70 , 0X7F ,  0X7B}; // display 7 segmentos simulação

void USART_Transmit(unsigned char data)
{
	while(!( UCSR0A & (1<<UDRE0)));//Espera a limpeza do registr. de transmissão
	UDR0 = data; //Coloca o dado no registrador e o envia
}
void USART_Init(unsigned int ubrr)
{
	UBRR0H = (unsigned char)(ubrr>>8); //Ajusta a taxa de transmissão
	UBRR0L = (unsigned char)ubrr;
	UCSR0B = (1<<RXCIE0)|(1<<RXEN0)|(1<<TXEN0); //Habilita o transmissor e o receptor
	UCSR0C = (1<<USBS0)|(3<<UCSZ00); //Ajusta o formato do frame: 8 bits de dados e 2 de parada
	
	DDRC = 0xFF; //Define a porta C como saída
}
unsigned char USART_Receive(void)
{
	while(!(UCSR0A & (1<<RXC0))); //Espera o dado ser recebido
	return UDR0; //Le o dado recebido e retorna
}

ISR(INT0_vect) //Decrementar 10s
{
	if(dificuldade==1){
		contador-=5;
	}
	if(dificuldade==2){
		contador-=10;
	}
	if(dificuldade==3){
		contador-=15;
	}
}
ISR(INT1_vect) // Inicio do jogo
{
	if(start_end==0)
	start_end=1;
	_delay_ms(50);
}

ISR(TIMER0_COMPA_vect){
	
	if(start_count==2){
		cont++;
		if(cont==1000){
			contador--;
			cont=0;
			if(contador==0){ // Acaba o jogo
				start_count=3;
				contador=99;
				_delay_ms(100);
			}
		}
	}
}
ISR(USART_RX_vect)
{
	char recebido;
	recebido = UDR0;
	if(recebido=='1'){
		dificuldade=1;
	}
	if(recebido=='2'){
		dificuldade=2;
	}
	if(recebido=='3'){
		dificuldade =3;
	}
	USART_Transmit(recebido);
	start_count=1;
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
		
		if(start_count==0) // Contagem parada, com a contagem parada, existe a possibilidade de duas telas, a tela de inicio  e a tela de configuração
		{
			
			if(start_end==0) // Tela de inicio
			{
				game_running_display_init();
			}
				else if(start_end==1) // Tela de configuração
			{
				game_running_display_config();
			}
		}else if(start_count==1) // Contagem é sinalizada que irá começar 
		{
			start_count=game_running_display_transit_start(); // Retorna 2, obrigado a no proximo laço entrar na condição seguinte
		}else if(start_count==2) // Permanece por aqui até que o contador=0, condição imposta no timer 
		{
			game_running_display_countdwown(contador);
			
		}else if(start_count==3) // Tela de fim de jogo
		{	
		start_count=game_running_display_game_over(); // Retorna 0, obrigando a parar a contagem
		start_end=0; // Volta pra tela de inicio
		}
    }
  
  
}
