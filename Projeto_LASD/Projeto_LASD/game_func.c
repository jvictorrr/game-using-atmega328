#include "biblioteca.h"

void int2string(uint8_t valor, unsigned char *disp)
{
	
	for(uint8_t n=0; n<tam_vetor; n++)
	disp[n] = 0 + 48; //limpa vetor para armazenagem dos digitos
	disp += (tam_vetor-1);
	do
	{
		*disp = (valor%10) + 48; //pega o resto da divisão por 10
		valor /=10; //pega o inteiro da divisão por 10
		disp--;
	}while (valor!=0);
}

void start_game_config(uint8_t dezena, uint8_t unidade){
	// Função que inicializa o jogo, define as configurações que deverão ser utilizadas
	
}
void game_running_display_init(){
	// Função responsável por mostrar a tela inicial do jogo
	
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
	// Tela que configura o nivel de dificuldade do jogo
	
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
	// Tela que mostra a contagem regressiva durante o jogo
	
	
	nokia_lcd_clear(); //Limpa o LCD
	nokia_lcd_set_cursor(0, 0);
	nokia_lcd_write_string("GO",1); //Escreve a leitura no buffer do LCD
	int2string(contador, contador_string_num);
	nokia_lcd_set_cursor(20, 15);
	nokia_lcd_write_string(contador_string_num,4); //Escreve a leitura no buffer do LCD
	nokia_lcd_render(); //Atualiza a tela do display com o conteÃºdo do buffer
	_delay_ms(100);
	
}
uint8_t game_running_display_transit_start(){
	
	nokia_lcd_clear(); //Limpa o LCD
	nokia_lcd_set_cursor(30,15);
	nokia_lcd_write_string("3",4);
	nokia_lcd_render();
	_delay_ms(1000);
	
	
	nokia_lcd_clear(); //Limpa o LCD
	nokia_lcd_set_cursor(30,15);
	nokia_lcd_write_string("2",4);
	nokia_lcd_render();
	_delay_ms(1000);
	
	nokia_lcd_clear(); //Limpa o LCD
	nokia_lcd_set_cursor(30,15);
	nokia_lcd_write_string("1",4);
	nokia_lcd_render();
	_delay_ms(1000);
	
	
	nokia_lcd_clear(); //Limpa o LCD
	nokia_lcd_set_cursor(15,15);
	nokia_lcd_write_string("GO",4);
	nokia_lcd_render();
	_delay_ms(1000);
	
	return 2;
	
}
uint8_t game_running_display_game_over(){
	// Tela que mostra o fim do jogo
	
	nokia_lcd_clear(); //Limpa o LCD
	nokia_lcd_set_cursor(20,0);
	nokia_lcd_write_string("GAME",2); //Escreve um texto do tamanho 2
	nokia_lcd_set_cursor(20,25);
	nokia_lcd_write_string("OVER",2); //Escreve um texto do tamanho 2
	nokia_lcd_render();
	set_bit(PORTC,BUZZ);
	_delay_ms(400);
	clr_bit(PORTC,BUZZ);
	_delay_ms(5000);
	return 0;
}
uint8_t game_running_display_win(){
	// Tela que mostra o fim do jogo
	
	nokia_lcd_clear(); //Limpa o LCD
	nokia_lcd_set_cursor(20,0);
	nokia_lcd_write_string("YOU",2); //Escreve um texto do tamanho 2
	nokia_lcd_set_cursor(20,25);
	nokia_lcd_write_string("WIN",2); //Escreve um texto do tamanho 2
	nokia_lcd_render();
	set_bit(PORTC,BUZZ);
	_delay_ms(400);
	clr_bit(PORTC,BUZZ);
	_delay_ms(3000);
	return 0;
}
