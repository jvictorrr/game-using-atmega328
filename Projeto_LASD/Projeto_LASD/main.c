/*
* Projeto_LASD.c
*
* Created: 19/11/2020 10:30:13
* Autores: João Victor Rodrigues Ramalho
Matheus Cavalcante Rique
*/

#include "biblioteca.h"

uint8_t start_end=0; //  Variável que inicia o jogo
uint8_t dificuldade=0; // Variável que irá armazenar o nível de dificuldade
uint8_t contador=99; // Variável que armazena o valor inicial da contagem
uint16_t cont=0; // Variável auxiliar parar ser utilizada para ajustar o timer para 1s
uint8_t start_count=0;  // Variável que transita entre os estados do jogo

unsigned int Inicio_Sinal, Distancia;

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

ISR(INT0_vect) //Interrupção no pino PD2 responsável por decrementar a contagem de acordo com o nível 
{
if(start_count==2){ // Só interfere no funcionamento do brinquedo após o funcionamento 
set_bit(PORTC,BUZZ); 
_delay_ms(100); // Set bit e Clear bit com gerando um pulso de 100ms no pino PC6 conectado na base do transistor, que ativa o buzzer 
clr_bit(PORTC,BUZZ);
// Seleciona o nivel de dificuldade e decrementa no contador
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

}
	ISR(INT1_vect) // Inicio do jogo
	{
		if(start_end==0)
		start_end=1;
		_delay_ms(50);
	}

	ISR(TIMER0_COMPA_vect){
		
		if(start_count==2){ // Ativa a contagem 
			cont++;
			if(cont==1000){ // Conta 1000ms= 1s 
				contador--;
				cont=0;
				if(contador==0){ // Game Over 
					start_count=3;
					contador=99;
					_delay_us(1000);
				}
			}
		}
	}
	ISR(USART_RX_vect)
	{
		// Recebe o char via usart 
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
	ISR(TIMER1_CAPT_vect) //interrupção por captura do valor do TCNT1- Sensor Ultrassom 
	{
		cpl_bit(TCCR1B,ICES1); //troca a borda de captura do sinal
		if(!tst_bit(TCCR1B,ICES1)){
			Inicio_Sinal = ICR1;
		}
		else {//lê o valor de contagem do TC1 na borda de descida do sinal
			Distancia = (ICR1 - Inicio_Sinal)/58;// Cálculo da DIstância
		}
	}
	int main(void)
	{
	USART_Init(MYUBRR);
	
	// COnfigurações porta D 
	DDRD = 0x00;
	PORTD = 0xff;
	DDRD = (1<<5);
	
// Configurações porta C
	DDRC |= (1<<BUZZ);
	
// COnfigurações porta B
	DDRB = 0b00000010;//somente pino de disparo como saída (PB1), captura no PB0 (ICP1)
	PORTB =0b11111101;
	
	//Configuração para o sensor Ultrassom 
	
	TCCR1B = (1<<ICES1)|(1<<CS11); //TC1 com prescaler = 8, captura na borda de subida
	TIMSK1 = 1<<ICIE1; //habilita a interrupção por captura
	
	////////////////////////////////////////////////////////////////////
	
	EICRA = 0b00000011;
	EIMSK = 0b00000011;
	sei();
	

	// Timer
	TCCR0A = 0b10100010;
	TCCR0B = 0b00000011; // TC0 com prescaler=64
	OCR0A = 249; // ajusta o comparador do TC0 contar até 249
	OCR0B=200; // Duty do PWM no pino PD5
	TIMSK0 = 0b00000010; // Habilita a interrupcao na igualdade com OCR0A, sendo a cada 1ms = (64*(249+1)/16Mhz

	
	nokia_lcd_init(); //Inicia o LCD
	nokia_lcd_clear(); //Limpa o LCD
	nokia_lcd_render();
	
		
		
		while (1)
		{
			//pulso de disparo
			set_bit(PORTB,DISPARO);
			_delay_us(10);
			clr_bit(PORTB,DISPARO);
			
			clr_bit(PORTC,BUZZ); // Deixa como padrão o nivel lógico do pino PD6
			
			switch (start_count)
			{
				
				case 0:
				if(start_end==0) // Tela de inicio
				{
					game_running_display_init();
				}
				else if(start_end==1) // Tela de configuração
				{
					game_running_display_config();
				}
				break;
				
				case 1: // Contagem é sinalizada que irá começar- Tela de transição 
				start_count=game_running_display_transit_start(); // Retorna 2, obrigado a no proximo laço entrar na condicao seguinte
				break;
				
				case 2: // Permanece por aqui até que o contador=0 (jogador perdeu a partida) ou que o Sensor Ultrassom acuse que o jogador ganhou o jogo, condicao imposta no timer
				game_running_display_countdwown(contador);  // Retorna 2, obrigado a no proximo laco entrar na condicao seguinte
				if(Distancia<431){
					if(Distancia<20 || Distancia==0){
						start_count=4; // Vitoria do Jogador 
					}
				}
				break;
				case 3: // Game over 
				start_count=game_running_display_game_over(); // Retorna 0, obrigando a parar a contagem
				start_end=0; // Volta pra tela de inicio
				contador=99;
				cont=0;
				break;
				case 4: // You win 
				start_count=game_running_display_win(); // Retorna 0, obrigando a parar a contagem
				start_end=0; // Volta pra tela de inicio
				contador=99;
				cont=0;
				break;
				
			}
		}
		_delay_ms(50); // Delay necessário devido ao intervalo de 50ms entre as leituras do sensor ultrassom

	}