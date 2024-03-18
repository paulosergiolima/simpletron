#include <stdio.h>
#include <sys/types.h>

#define READ 10
#define WRITE 11

#define LOAD 20
#define STORE 21

#define ADD 30
#define SUBTRACT 31
#define DIVIDE 32
#define MULTIPLY 33

#define BRANCH 40
#define BRANCHNEG 41
#define BRANCHZERO 42
#define HALT 43

void clear(int memory[], int size, char signal[]) {
	for(int i = 0; i < size; i++) {
		memory[i] = 0;
		signal[i] = '+';
	}
}

int getDigits(int number) {
	int count = 0;
	if (number == 0) {
		return 1;
	}
	while(number>0) {
		count++;
		number = number / 10;
	}
	return count;
}

void dump(int acumulador, int contadorInstrucao, int registroInstrucao,int codigoOperacao, int operando, int memory[], char signal[]) {
	printf("REGISTROS:\n");
	printf("acumulador %d\n", acumulador);
	printf("contadorInstrucao %d\n", contadorInstrucao);
	printf("registroInstrucao %d\n", registroInstrucao);
	printf("codigoOperacao %d\n", codigoOperacao);
	printf("operando %d\n", operando);
	printf("Memória:\n");
	for(int i = 0; i < 10; i++) {
		printf("         %d", i);
	}
	printf("\n");
	for(int i = 0; i < 100; i = i + 10) {
		if(i == 0) {
			printf(" %d", i);
		}else {
			printf("%d", i);
		}
		printf("   ");
		for(int j = 0; j < 10; j = j + 1) {
			printf("%c", signal[i+j]);
			for(int k = getDigits(memory[i+j]); k <= 3; k++) {
				printf("0");
			}
			printf("%d     ", memory[i+j]);
		}
		printf("\n");
	}

}
int main() {
	printf("*** Bem vindo ao Simpletron! ***\n");
	printf("*** Por favor digite uma instrução (ou palavra ***\n");
	printf("*** de dados) de seu programa por vez. Digitarei o ***\n");
	printf("*** numero da posição e um ponto de interrogação ***\n");
	printf("*** (?). Digite então a palavra para aquela posição ***\n");
	printf("*** Digite o valor sentinela -99999 para encerrar a ***\n");
	printf("*** digitação de seu programa. ***\n");
	int memory[100];
	char signal[100];
	clear(memory, 100, signal);
	int acumulador = 0;
	int contadorInstrucao = 0;
	int registroInstrucao = 0;
	int codigoOperacao = 0;
	int operando = 0;

	int i = -1;
	do {
		i++;
		if(i < 10) {
			printf("0%d ? ", i);
		}else {
			printf("%d ? ", i);
		}
		int number;
		scanf("%d", &number);
		if(number == -99999) {
			break;
		}
		if (number >= 0) {
			memory[i] = number;
			signal[i] = '+';
		}else {
			memory[i] = number * -1;
			signal[i] = '-';
		}
	}while (memory[i] != 99999);
	printf("*** Carregamento do programa concluido *** *** Inicio da execução do programa ***\n");
	while(contadorInstrucao < 100) {
		codigoOperacao = memory[contadorInstrucao] / 100;
		int unclear_num = 0;
		operando = memory[contadorInstrucao] % 100;
		switch (codigoOperacao) {
			case READ:
				printf("Escrever no %d local: ", operando);
				scanf("%d", &unclear_num);
				if(unclear_num >= 0) {
					signal[operando] = '+';
				}else {
					signal[operando] = '-';
					unclear_num = unclear_num * -1;
				}
				memory[operando] = unclear_num;
				contadorInstrucao++;
				continue;
			case WRITE:
				printf("OUTPUT: %d\n", memory[operando]);
				contadorInstrucao++;
				continue;
			case LOAD:
				acumulador = memory[operando];
				contadorInstrucao++;
				continue;
			case STORE:
				memory[operando] = acumulador;
				contadorInstrucao++;
				continue;
			case ADD:
				acumulador = memory[operando] + acumulador;
				contadorInstrucao++;
				continue;
			case SUBTRACT:
				acumulador = acumulador - memory[operando];
				contadorInstrucao++;
				continue;
			case DIVIDE:
				acumulador = memory[operando] /  acumulador;
				contadorInstrucao++;
				continue;
			case MULTIPLY:
				acumulador = acumulador * memory[operando];
				contadorInstrucao++;
				continue;;
			case BRANCH:
				contadorInstrucao = operando;
				continue;
			case BRANCHNEG:
				if(acumulador < 0) {
					contadorInstrucao = operando;
				}else {
					contadorInstrucao++;
				}
				continue;
			case BRANCHZERO:
				if(acumulador == 0) {
					contadorInstrucao = operando;
				}else {
					contadorInstrucao++;
				}
				continue;
			case HALT:
				contadorInstrucao = 100;
				break;
				continue;
			default:
				contadorInstrucao++;
				continue;

		}

	}
	dump(acumulador, contadorInstrucao, registroInstrucao, codigoOperacao, operando, memory, signal);

}
