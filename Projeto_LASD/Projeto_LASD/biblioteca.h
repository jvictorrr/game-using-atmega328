#define F_CPU 16000000UL
#define BAUD 9600
#define MYUBRR F_CPU/16/BAUD-1
#define set_bit(y,bit) (y|=(1<<bit)) //coloca em 1 o bit x da variável Y
#define clr_bit(y,bit) (y&=~(1<<bit)) //coloca em 0 o bit x da variável Y
#define cpl_bit(y,bit) (y^=(1<<bit)) //troca o estado lógico do bit x da variável Y
#define tst_bit(y,bit) (y&(1<<bit)) //retorna 0 ou 1 conforme leitura do bit
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include "nokia5110.h"
#define tam_vetor 2
#define BUZZ PC6
#define DISPARO PB1


unsigned char contador_string[tam_vetor];
unsigned char contador_string_num[tam_vetor];

// USART
void USART_Transmit(unsigned char data);
void USART_Init(unsigned int ubrr);
unsigned char USART_Receive(void);

// Funções relacionadas a interface do jogo
void start_game_config(uint8_t num_dezena, uint8_t num_unidade);
void game_running_display_init();
void game_running_display_config();
void game_running_display_countdwown(uint8_t contador);
uint8_t game_running_display_transit_start();
uint8_t game_running_display_game_over();
uint8_t game_running_display_win();
