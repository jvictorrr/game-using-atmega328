# BuzzWire Ultimate Countdwon 

*Projeto de um jogo utilizando o microcontrolador atmel328 para o laboratório da disciplina de Arquitetura de Sistemas Digitais*

## 1. Código	

O código em questão deve ser implementado para o funcionamento de um jogo no qual 
o objetivo é que o usuário consiga levar passar por um labirinto de uma ponta a outra
do percurso antes que o tempo acabe, para aumentar a dificuldade, quando o jogador
sofrer uma punição ao encostar na na barreira. essa punição pode ser de 5, 10 ou 15 segundos.

Assim, inicialmente as funções utilizadas no programa foram moduladas nos arquivos
“biblioteca.h” e “game_func.c” onde estão declarados as variáveis, os arquivos externos e as funções relacionadas ao jogo. 


No atmel foram definidas as portas: 

- PB1 como o pino de saída responsável por emitir o sinal do sensor ultrassom
- PB0 como entrada, para receber o retorno do sinal ultrassônico
- PD2 e PD3 são entradas que habilitam as interrupções 
- PD5 a saída
- Portas C são habilitadas como saída das portas 1 a 5 para o display e 6 para funcionar como o ativador da base do transistor

![pinagem-ATMEGA328P](https://user-images.githubusercontent.com/39633395/132619261-4ccc4969-8c45-4449-8be0-87d770c9837f.jpg)
