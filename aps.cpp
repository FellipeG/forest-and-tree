/* ESTRUTURA DE DADOS - 862;
	* Fellipe José Rosa Garcias - 2017200985
	* Hugo Olaitan Ferreira Jerônimo - 2018101788
	* Jefferson Silva Brito - 2017100077
	* Leandro Sena de Catro - 2018100826
*/


#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <iostream>

using namespace std;

// Contador para manipular a exibição de elementos de uma árvore específica
int contador = 1;

// Cria o struct da arvore que será inserida em uma floresta
struct EnoArvore {
	int chave;
 	struct EnoArvore *esq;
	struct EnoArvore *dir;
};

// Cria o struct da floresta
struct EnoFloresta {
	int chaveInicial;
 	int chaveFinal;
 	struct EnoFloresta *esq;
 	struct EnoFloresta *dir;
 	struct EnoArvore *arvore;
};

// Define o monitor
struct EnoFloresta *monitor;

// Define o monitor como valor inicial null
void create() {
	monitor = NULL;
}

// Aloca a floresta na memória passando a chave por parâmetro
struct EnoFloresta *alocarFloresta(int chave) {
	struct EnoFloresta *f;
	f = (struct EnoFloresta *)malloc(sizeof(struct EnoFloresta));

	/* Em chave inicial e final é definido o limite dos números aceitos pela floresta
	   Caso seja 10 a chave passada por parâmetro, a floresta aceitará valores de 1 a 9 */
	f->chaveInicial = chave-9;
	f->chaveFinal = chave;
	f->esq = NULL;
	f->dir = NULL;
	f->arvore = NULL;
	
	return f;
}

// Aloca o árvore na memória passando a chave como parâmetro
struct EnoArvore *alocarArvore(int chave) {
	struct EnoArvore *a;
	a = (struct EnoArvore *)malloc(sizeof(struct EnoArvore));
	a->chave = chave;
	a->esq = NULL;
	a->dir = NULL;
	
	return a;
}

// Insere uma nova floresta
void inserirFloresta(int chave, struct EnoFloresta **elem) {
	
	
	// Caso base
	if (*elem == NULL) {
		
		struct EnoFloresta *f = alocarFloresta(chave);
		*elem = f;
		return;
		
	}
	
	/* Se a chave da nova floresta for menor do que a chave da floresta passada por parâmetro, 
	chama a árvore a esquerda, senão, chama a árvore a direita */
	(chave < (*elem)->chaveInicial) ? inserirFloresta(chave, &(*elem)->esq) : inserirFloresta(chave, &(*elem)->dir);
	
}

// Cria uma árvore binária
void inserirNaArvore(int chave, struct EnoArvore **raiz) {
	
	// Caso base
	if (*raiz == NULL) {
		*raiz = alocarArvore(chave);
		return;
	}
	
	/* Se a chave da nova árvore for menor do que a da raiz, chama a árvore a esquerda
	senão, chama a árvore a direita até encontrar null */
	(chave < (*raiz)->chave) ? inserirNaArvore(chave, &(*raiz)->esq) : inserirNaArvore(chave, &(*raiz)->dir);
}

// Verifica em qual das florestas a chave deve ser inserida
void inserirArvore(int chave, struct EnoFloresta **floresta) {

	 // Verifica se a chave estão entre os valores permitidos da floresta
	if (chave >= (*floresta)->chaveInicial && chave < (*floresta)->chaveFinal) {
		inserirNaArvore(chave, &(*floresta)->arvore);
		return;
	}
	
	// Caso seja menor que o valor minimo, chama a floresta a esquerda
	if (chave < (*floresta)->chaveInicial) {
		inserirArvore(chave, &(*floresta)->esq);
	}
	
	// Caso seja maior, chama a floresta a direita
	if (chave > (*floresta)->chaveFinal) {
		inserirArvore(chave, &(*floresta)->dir);
	}

}

// Imprime a árvore de todas passada por parâmetro - (método colchete)
void imprimirPreOrdemArvore(struct EnoArvore *raiz) {
	
	// Caso base
	if (raiz == NULL) {
		cout << "[]";
		return;
	}
	
	// Imprime a chave
	cout << " [" << raiz->chave;

	
	// Chama o elemento a esquerda
	imprimirPreOrdemArvore(raiz->esq);

	// Chama o elemento a direita
	imprimirPreOrdemArvore(raiz->dir);
	
	cout << "] ";
	
	
}

// Imprime a árvore de todas passada por parâmetro - (método colchete)
void imprimirPreOrdemArvoreTotal(struct EnoArvore *raiz) {
	
	// Caso base
	if (raiz == NULL) {
		cout << "()";
		return;
	}
	
	// Imprime a chave
	cout << " (" << raiz->chave;

	
	// Chama o elemento a esquerda
	imprimirPreOrdemArvoreTotal(raiz->esq);

	// Chama o elemento a direita
	imprimirPreOrdemArvoreTotal(raiz->dir);
	
	cout << ") ";
	
	
}


// Imprime a floresta e suas respectivas árvores - (método colchete)
void imprimirPreOrdem(struct EnoFloresta *floresta) {

	// Caso base
	if(floresta == NULL) {
		cout << "[]";
		return;
	}

	// Imprime a chave final da floresta (que é o valor digitado pelo usuário ou do teste)
	cout << " [" << floresta->chaveFinal;
	
	cout << " {";
	imprimirPreOrdemArvoreTotal(floresta->arvore);
	cout << "} ";

	// Chama a floresta a esquerda
  	imprimirPreOrdem(floresta->esq);  
	
	// Chama a floresta a direita
  	imprimirPreOrdem(floresta->dir);  
  	
  	cout << "] ";
}

// Imprime as opções de árvore disponíveis
void imprimirOpcoesArvore(struct EnoFloresta *floresta, int *contador) {
	
	if (floresta == NULL) return;
	
	imprimirOpcoesArvore(floresta->esq, contador);
	cout << "[" << (*contador)++ << "] De " << floresta->chaveInicial << " até " << floresta->chaveFinal - 1 << " (Floresta " << floresta->chaveFinal << ")" << endl;
	imprimirOpcoesArvore(floresta->dir, contador);

}

// Recebe a opção do menu, o contador do topo da página e a floresta monitor. Verifica se a opção bate com o contador e imprime a árvore da floresta correta
void ImprimirArvoreEspecifica(int opcao, int *contador, struct EnoFloresta *floresta) {
	
	if (floresta == NULL) return;
	
		ImprimirArvoreEspecifica(opcao, contador, floresta->esq);
		if (opcao == (*contador)++) {
			imprimirPreOrdemArvore(floresta->arvore);
		}
		ImprimirArvoreEspecifica(opcao, contador, floresta->dir);
}

// Menu
int menu() {
	int opcao;
	system("cls");
	cout << endl << "-------- MENU --------" << endl << endl;
	cout << "[1] Inserir elemento" << endl;
	cout << "[2] Imprimir dados" << endl;
	cout << "[0] Sair" << endl;
	cout << "Opção: ";
	cin >> opcao;
	switch(opcao) {
		case 0: 
			return 0;
		case 1:
		{ 
			system("cls");
			cout << endl << "-------- INSERIR DADO --------" << endl << endl;
			int elem;
		  	cout << "Digite o elemento a ser inserido: ";
		  	cin >> elem;
		  	if (elem < 1 || elem > 89) {
		  		cout << "Elemento inválido, digite um número >= 1 e <= 89" << endl;
				system("pause");
				return 1;	
			}
		  	inserirArvore(elem, &monitor);
		  	return 1;
		}
		
		case 2:
		{ 
			system("cls");
			cout << endl << "-------- IMPRIMIR DADOS --------" << endl << endl;
			int opcao, opcao2;
			cout << "[1] Para Imprimir pré ordem de todos os dados da Floresta" << endl;		  
	      	cout << "[2] Imprimir pré ordem dos dados específicos de uma floresta" << endl;
	      	cout << "Opção: ";
	      	cin >> opcao;
		  	if (opcao == 1) {
		  		imprimirPreOrdem(monitor);
			} else if (opcao == 2) {
				imprimirOpcoesArvore(monitor, &contador);
				contador = 1;
				cout << "Opção: ";
				cin >> opcao2;
				ImprimirArvoreEspecifica(opcao2, &contador, monitor);
				contador = 1;
			} else{
				cout << "Opção inválida!" << endl;
			}
			cout << endl;
		  	system("pause");
		  	return 1;
		}

		default:
			cout << "Digite uma opção VÁLIDA!" << endl;
			system("pause");
			return 1;
	}	
}

// Insere as árvores e florestas automaticamente no início da execução do programa
void inserirDados() {
	int arvore[9]={5, 15, 25, 35, 45, 55, 65, 75, 85};
	int floresta[9]={50, 80, 70, 40, 10, 30, 60, 20, 90};
			
	int sizeFloresta = sizeof(floresta) / sizeof(floresta[0]); // Obtem o tamanho do vetor floresta
	for(int i=0; i<sizeFloresta; i++) {
		inserirFloresta(floresta[i], &monitor);
	}
	int sizeArvore = sizeof(arvore) / sizeof(arvore[0]); // Obtem o tamanho do vetor arvore
	for(int i=0; i<sizeArvore; i++) {
		inserirArvore(arvore[i], &monitor);
	} 
}

main() {

	// Seta a linguagem padrão para português, para aceitar acentos e ç
	setlocale(LC_ALL, "Portuguese");
	create();
	inserirDados();
	while(menu());
	system("cls");
	cout << endl << "ESTRUTURA DE DADOS - 862" << endl;
	cout << "--------------------------------------------------------" << endl;
	cout << "Fellipe José Rosa Garcias - 2017200985" << endl;
	cout << "Hugo Olaitan Ferreira Jerônimo - 2018101788" << endl;
	cout << "Jefferson Silva Brito - 2017100077" << endl;
	cout << "Leandro Sena de Catro - 2018100826" << endl << endl;
	system("pause");

}
