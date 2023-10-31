#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <conio.h>
#include <time.h>
#include <locale.h>

// Aplicação jogo Snake feito por Cynthia e Rita

int c[300][2], pontos = 1, cx = 2, cy = 2;
int comida[2], velo = 150, escolha, opcao;

// Definição de cores
#define VERMELHO 12 //para a cor vermelha
#define VERDE 10  //para a cor verde

// Para definir a cor
void setCor(int corFundo, int corPrimeiroPlano) {
    // A função
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), (corFundo << 4) | corPrimeiroPlano);
}

// Posição  das coordenadas
void gotoxy(int x, int y) {
    COORD coord;
    coord.X = x;
    coord.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}
int main() {
	
	printf("**********REGRAS**********\n");{
    printf("1. Comande a cobra com as teclas W, A, S, e D ou as setas do seu teclado.\n");
    printf("2. Evite bater na parede.\n");
    printf("3. Evite bater na sua cauda.\n");
    printf("4. A cada ponto a velocidade aumenta.\n");
    printf("5. Ganha o jogo quando conseguir 10 pontos.\n");
	system("pause");
	system("cls");

}
    int i, gameover = 0;
    int tecla;
    
    
    for (i = 0; i < 50; i++) {//Linha superior
        gotoxy(i, 0);
        printf("%c", 219);
        Sleep(4); // Para execução em 4 milissegundos 
    }
    for (i = 0; i < 20; i++) {//Coluna da direita
        gotoxy(50, i);
        printf("%c", 219);
        Sleep(4); // Para execução em 4 milissegundos 
    }
    for (i = 50; i >= 0; i--) {// Linha inferior 
        gotoxy(i, 20);
        printf("%c", 219);
        Sleep(4);
    }
    for (i = 20; i > 0; i--) {// Coluna da esquerda
        gotoxy(0, i);
        printf("%c", 219);
        Sleep(4); // Para execução em 4 milissegundos
    }
    geraComida(); // Gera a comida
    desenha(); // Desenha a cobra
    tecla = 'd'; // A direção para a direita

    while (gameover == 0 && pontos < 10) {
        gotoxy(52, 2);
        printf("Pontos: %d\t", pontos);
        gotoxy(52, 4);
        printf("Velocidade: %.2f s", 1000.0 / velo);
        c[0][0] = cx;
        c[0][1] = cy;
        if (kbhit()) // Se alguma tecla for apertada, o valor
            tecla = getch(); // Vai para a tecla 'tecla'

        if (tecla == 'w' || tecla == 'W' || tecla == 72) { // Se a cabeça da esuqerda estiver na parede superior, o jogo acaba
            cy--;
            if (cy == 0)
                break;
        }
        if (tecla == 'a' || tecla == 'A' || tecla == 75) { // Se a cabeça da cobra estiver na parede da esquerda, o jogo acaba
            cx--;
            if (cx == 0)
                break;
        }
        if (tecla == 's' || tecla == 'S' || tecla == 80) { // Se a cabeça da cobra estiver na parte inferior, o jogo acaba
            cy++;
            if (cy == 20)
                break;
        }
        if (tecla == 'd' || tecla == 'D' || tecla == 77) { // Se a cabeça da cobra estiver na parte direita, o jogo acaba
            cx++;
            if (cx >= 50)
                break;
        }

        if (cx == comida[0] && cy == comida[1]) { // Se a cobra comer  a comida
            pontos++;
            if (velo > 0)
                velo -= 5;
            geraComida();
        }
        gameover = analiza();
        atualiza();
        desenha();
        gotoxy(50, 20);
        Sleep(velo);
    }

    system("cls"); // Se o jogador perder ou ganhar, limpa a tela e exibe uma mensagem final
    
    
    if (pontos == 10) {
        setCor(0, VERDE);
        
        printf("GANHOU! Fez %d pontos.\n", pontos);
        FILE *ex1; //variavel arquivo//

	//Passo 1: criação de arquivo//
	ex1= fopen ("PARABÊNS!!!.txt", "w"); 
	
	//Passo 2: imprimindo o arquivo//
	fprintf(ex1, "VOCÊ É UM VENCEDOR!! (/^0^/) \n" );
	
	//Passo 3: encerrando o arquivo//
	fclose(ex1);
    } else {
        setCor(0, VERMELHO);
        printf("PERDEU! TENTE NOVAMENTE Fez %d pontos.\n", pontos);
    }
    setCor(0, 15);

    // MENU
    int opcao = 1;

    printf("\n*DESEJA CONTINUAR O JOGO?*\n");
    printf("1. Sim.\n");
    printf("2. Sair.\n");
    printf("Escolha: ");
    scanf("%d", &opcao);

    if (opcao == 1) { // Se o jogador optar por continuar jogando
        inicializaJogo(); // Reinicia o estado do jogo
        main(); // Chama main novamente para reiniciar o jogo
    } else if (opcao == 2) { // Se não, encerra o programa, digitando 2 
        exit(0);
    } else {
    	printf ("RESPOSTA INVALIDA! \n");
	}
    system("pause");
}
// Desenho da cobrinha
void desenha() {
    int i;
    setCor(0, VERDE); // Cor verde para o texto
    for (i = 0; i < pontos; i++) {
        gotoxy(c[i][0], c[i][1]);
        printf("%c", 219);
    }
    setCor(0, 15); // Restaura as cores padrão (fundo preto e primeiro plano branco)
}

// Atualizar a posição da cobrinha
void atualiza() {
    int i;
    gotoxy(c[pontos][0], c[pontos][1]);
    printf(" ");
    for (i = pontos; i >= 0; i--) {
        c[i + 1][0] = c[i][0];
        c[i + 1][1] = c[i][1];
    }
}

// Verificar se a cobrinha bateu no próprio corpo
int analiza() {
    int i, retorno = 0;
    for (i = 1; i < pontos; i++) {
        if (cx == c[i][0] && cy == c[i][1]) {
            retorno = 1;
        }
    }
    return retorno;
}

// Gerar as frutinhas
void geraComida() {
    gotoxy(comida[0], comida[1]);
    printf(" ");
    srand(time(NULL));
    comida[0] = (rand() % 48) + 1;
    comida[1] = (rand() % 18) + 1;
    gotoxy(comida[0], comida[1]);
    setCor(0, VERMELHO); // Cor vermelha para a fruta
    printf("%c", 4);
    setCor(0, 15); // Restaurar as cores padrão
}

// Função para inicializar o estado do jogo
void inicializaJogo() {
    int i;
    pontos = 1;
    cx = 2;
    cy = 2;
    velo = 150;
    for (i = 0; i < 300; i++) {
        c[i][0] = 0;
        c[i][1] = 0;
    }
    comida[0] = 0;
    comida[1] = 0;
    system("cls");
}

