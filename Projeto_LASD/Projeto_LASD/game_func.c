#include "biblioteca.h"
#define tam_vetor 2

void int2string(unsigned int valor, unsigned char *disp)
{
	for(uint8_t n=0; n<tam_vetor; n++)
	disp[n] = 0 + 48; //limpa vetor para armazenagem dos digitos
	disp += (tam_vetor-1);
	do
	{
		*disp = (valor%10) + 48; //pega o resto da divisÃ£o por 10
		valor /=10; //pega o inteiro da divisÃ£o por 10
		disp--;
	}while (valor!=0);
}

void start_game_config(uint8_t dezena, uint8_t unidade){
	// Função que inicializa o jogo, define as configurações que deverão ser utilizadas
	
}
void game_running_display_init(){
	// Função responsável por gerenciar o display nokia durante o funcionamento do jogo
	
	// Tela inicial do Jogo
			nokia_lcd_clear(); //Limpa o LCD
			nokia_lcd_set_cursor(0,0);
			nokia_lcd_write_string("BUZZ",2); //Escreve um texto do tamanho 2
			nokia_lcd_set_cursor(0,15);
			nokia_lcd_write_string("WIRE",2); //Escreve um texto do tamanho 2
			nokia_lcd_set_cursor(0,30);
			nokia_lcd_write_string("Ultimate",1); //Escreve um texto do tamanho 2
			nokia_lcd_set_cursor(0,40);
			nokia_lcd_write_string("Countdown",1); //Escreve um texto do tamanho 2
			nokia_lcd_render(); 
 
}
void game_running_display_config(){
	
				nokia_lcd_clear(); //Limpa o LCD
				nokia_lcd_set_cursor(0,0);
				nokia_lcd_write_string("Configuracao",1);
				nokia_lcd_set_cursor(0,20);
				nokia_lcd_write_string("1: Facil",1); 
				nokia_lcd_set_cursor(0,30);
				nokia_lcd_write_string("2: Normal",1); 
				nokia_lcd_set_cursor(0,40);
				nokia_lcd_write_string("3: Dificil",1); 			
				nokia_lcd_render();
				
}
void game_running_display_countdwown(uint8_t contador){
	unsigned char contador_string[tam_vetor];
	
	nokia_lcd_clear(); //Limpa o LCD
	nokia_lcd_set_cursor(0, 0);
	nokia_lcd_write_string("Valendo",1); //Escreve a leitura no buffer do LCD
	int2string(contador, contador_string);
	nokia_lcd_set_cursor(0, 30);
	nokia_lcd_write_string(contador_string,2); //Escreve a leitura no buffer do LCD
	nokia_lcd_render(); //Atualiza a tela do display com o conteÃºdo do buffer
	_delay_ms(500);
	
}

