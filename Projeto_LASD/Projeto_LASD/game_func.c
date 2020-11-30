#include "biblioteca.h"

void start_game_config(uint8_t dezena, uint8_t unidade){
	// Função que inicializa o jogo, define as configurações que deverão ser utilizadas
	
}
void game_running_display(){
	// Função responsável por gerenciar o display nokia durante o funcionamento do jogo
	
	
			nokia_lcd_clear(); //Limpa o LCD
			nokia_lcd_set_cursor(0, 10);
			nokia_lcd_write_string("GAME", 2); //Escreve um texto do tamanho 2
			nokia_lcd_render(); 

}
