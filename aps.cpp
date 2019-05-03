#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <iostream>

using namespace std;

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
		cout << (*raiz)->chave << endl;
		return;
	}
	
	/* Se a chave da nova árvore for menor do que a da raiz, chama a árvore a esquerda
	senão, chama a árvore a direita até encontrar null */
	(chave < (*raiz)->chave) ? inserirNaArvore(chave, &(*raiz)->esq) : inserirNaArvore(chave, &(*raiz)->dir);
}

// Verifica em qual das florestas a chave deve ser inserida
void inserirArvore(int chave, struct EnoFloresta **floresta) {

	 // Verifica se a chave estão entre os valores permitidos da floresta
	if ((chave >= (*floresta)->chaveInicial && chave < (*floresta)->chaveFinal) || (chave >= (*floresta)->chaveFinal && (*floresta)->dir == NULL)
		|| (chave < (*floresta)->chaveInicial && (*floresta)->esq == NULL)) {
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
	if (raiz == NULL) return;
	
	// Imprime a chave
	cout << "[" << raiz->chave;

	// Caso o elemento a esquerda não seja nulo, é impresso
	(raiz->esq != NULL) ? cout << "[" << raiz->esq->chave << "]" : cout << "[]";

	// Caso o elemento a direita não seja nulo, é impresso
	(raiz->dir != NULL) ? cout << "[" << raiz->dir->chave << "]" : cout << "[]";
	cout << "]";
	
	// Chama o elemento a esquerda
	imprimirPreOrdemArvore(raiz->esq);

	// Chama o elemento a direita
	imprimirPreOrdemArvore(raiz->dir);
	
	
}


// Imprime a floresta e suas respectivas árvores - (método colchete)
void imprimirPreOrdem(struct EnoFloresta **floresta) {

	// Caso base
	if((*floresta) == NULL) return;

	// Imprime a chave final da floresta (que é o valor digitado pelo usuário ou do teste)
	cout << "[" << (*floresta)->chaveFinal;
	
	// Se a floresta a esquerda não for nula Ã© impressa
	if ((*floresta)->esq != NULL) {
		cout << " [";
		cout << (*floresta)->esq->chaveFinal;
		// Imprime a árvore da floresta a esquerda
		imprimirPreOrdemArvore((*floresta)->esq->arvore);
		cout << "] ";
	} else {
		// Imprime colchete vazio caso a floresta a esquerda seja nula
		cout << " [] ";
	}
	
	// Se a floresta a direita não for nula é impressa
	if ((*floresta)->dir != NULL) {
		cout << "[";
		cout << (*floresta)->dir->chaveFinal;
		// Imprime a árvore da floresta a direita
		imprimirPreOrdemArvore((*floresta)->dir->arvore);
		cout << "]";
	} else {
		// Imprime colchete vazio caso a floresta a direita seja nula
		cout << "[]";
	}
	
	
	cout << "]" << endl;
  	
	// Chama a floresta a esquerda
  	imprimirPreOrdem(&(*floresta)->esq);  
	
	// Chama a floresta a direita
  	imprimirPreOrdem(&(*floresta)->dir);  
}

// Imprime as opções de árvore disponíveis
void imprimirOpcoesArvore(struct EnoFloresta *floresta, int *contador) {
	
	if (floresta == NULL) return;
	
	imprimirOpcoesArvore(floresta->esq, contador);
	cout << "[" << (*contador)++ << "] De " << floresta->chaveInicial << " até " << floresta->chaveFinal - 1 << endl;
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
	cout << "[1] Inserir na floresta" << endl;
	cout << "[2] Inserir na arvore" << endl;
	cout << "[3] Imprimir dados" << endl;
	cout << "[4] Massa de teste" << endl;
	cout << "[0] Sair" << endl;
	cout << "Opção: ";
	cin >> opcao;
	switch(opcao) {
		case 0: 
			return 0;
		case 1:
		{ 
			system("cls");
			cout << endl << "-------- INSERIR NA FLORESTA --------" << endl << endl;
			int elem;
		  	cout << "Digite o elemento para inserir na Floresta: ";
		  	cin >> elem;
		  	return 1;
		}
		
		case 2:
		{ 
			system("cls");
			cout << endl << "-------- INSERIR NA ÁRVORE --------" << endl << endl;
			int elem;
		  	cout << "Digite o elemento para inserir na arvore da floresta: ";
		  	cin >> elem;
		  	return 1;
		}
		
		case 3:
		{ 
			system("cls");
			cout << endl << "-------- IMPRIMIR DADOS --------" << endl << endl;
			int opcao, opcao2;
			cout << "[1] Para Imprimir pré ordem dos dados da Floresta" << endl;		  
	      	cout << "[2] Imprimir pré ordem dos dados específicos de uma floresta" << endl;
	      	cout << "Opção:";
	      	cin >> opcao;
		  	if (opcao == 1) {
		  		imprimirPreOrdem(&monitor);
			} else if (opcao == 2) {
				imprimirOpcoesArvore(monitor, &contador);
				contador = 1;
				cout << "Opção: ";
				cin >> opcao2;
				ImprimirArvoreEspecifica(opcao2, &contador, monitor);
				//imprimirPreOrdemArvore(monitor);	
			} else{
				cout << "Opção inválida!" << endl;
			}
			cout << endl;
		  	system("pause");
		  	return 1;
		}

		case 4:
		{ 
			system("cls");
			cout << endl << "-------- MASSA DE TESTE --------" << endl << endl;
			int arvore[9]={5, 15, 25, 35, 45, 55, 65, 75, 85};
			int floresta[9]={50, 80, 70, 40, 10, 30, 60, 20, 90};
			
			int sizeFloresta = sizeof(floresta) / sizeof(floresta[0]); // Obtem o tamanho do vetor Z
			for(int i=0; i<sizeFloresta; i++) {
				inserirFloresta(floresta[i], &monitor);
			}
			int sizeArvore = sizeof(arvore) / sizeof(arvore[0]); // Obtem o tamanho do vetor X
			for(int i=0; i<sizeArvore; i++) {
				inserirArvore(arvore[i], &monitor);
			} 
		  	system("pause");
		  	return 1;
    }       
		
			default:
				cout << "Digite uma opção VÁLIDA!";
				return 1;
	}	
}

main() {

	// Seta a linguagem padrão para português, para aceitar acentos e ç
	setlocale(LC_ALL, "Portuguese");
	create();
	while(menu());
	cout << endl << "Feito por:" << endl;
	cout << "Fellipe José Rosa Garcias - 2017200985" << endl;
	cout << "Hugo - Matrícula" << endl;
	cout << "Jeferson - Matrícula" << endl;
	cout << "Leandro - Matrícula" << endl;
	system("pause");

}
