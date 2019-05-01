#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <iostream>

using namespace std;

struct EnoArvore {
	int chave;
 	struct EnoArvore *esq;
	struct EnoArvore *dir;
};

struct EnoFloresta {
	int chaveInicial;
 	int chaveFinal;
 	struct EnoFloresta *esq;
 	struct EnoFloresta *dir;
 	struct EnoArvore *arvore;
};

struct EnoFloresta *monitor;

void create() {
	monitor = NULL;
}

struct EnoFloresta *alocarFloresta(int chave) {
	struct EnoFloresta *f;
	f = (struct EnoFloresta *)malloc(sizeof(struct EnoFloresta));
	f->chaveInicial = chave-9;
	f->chaveFinal = chave;
	f->esq = NULL;
	f->dir = NULL;
	f->arvore = NULL;
}

struct EnoArvore *alocarArvore(int chave) {
	struct EnoArvore *a;
	a = (struct EnoArvore *)malloc(sizeof(struct EnoArvore));
	a->chave = chave;
	a->esq = NULL;
	a->dir = NULL;
}


void inserirFloresta(int chave, struct EnoFloresta **elem) {
	
	if (*elem == NULL) {
		
		struct EnoFloresta *f = alocarFloresta(chave);
		*elem = f;
		return;
		
	}
	
	(chave < (*elem)->chaveInicial) ? inserirFloresta(chave, &(*elem)->esq) : inserirFloresta(chave, &(*elem)->dir);
	
}

struct EnoFloresta *retornaFloresta(int chave, struct EnoFloresta *elem) {
	
	if(elem == NULL) return NULL;
	
	if (elem->chaveInicial < chave && elem->chaveFinal > chave) return elem;
	
	if (elem->esq != NULL) {
		
		if(elem->chaveInicial > chave) {
			
			retornaFloresta(chave, elem->esq);
		}
	
	}
	
	if (elem->dir != NULL) {
		
		if(elem->chaveFinal < chave) {
			
			retornaFloresta(chave, elem->dir);
		}
	
	}
	
}

/*void inserirNaArvore(int chave, struct EnoArvore *arvore) {

	while (arvore->chave) {
	}

}

void inserirArvore (int chave) {
	
	struct EnoFloresta *floresta = retornaFloresta(chave);
	
	if(floresta->arvore == NULL) {
		struct EnoArvore *a = alocarArvore(chave);
		return;
	}
	
	if (chave < floresta->arvore->chave) {
		inserir
	}
	
	
}*/

void imprimirPreOrdem(struct EnoFloresta **floresta) {
	if((*floresta) == NULL || ((*floresta)->chaveInicial == 0 && (*floresta)->chaveFinal == 0)) return;

	cout << "[" << (*floresta)->chaveFinal;
	((*floresta)->esq != NULL) ? cout << "[" << (*floresta)->esq->chaveFinal << "]" : cout << "[]";
	((*floresta)->dir != NULL) ? cout << "[" << (*floresta)->dir->chaveFinal << "]" : cout << "[]";
	cout << "]" << endl;
  	
  	imprimirPreOrdem(&(*floresta)->esq);  
  	imprimirPreOrdem(&(*floresta)->dir);  
}

void imprimir(int opcao) {  
  switch(opcao) {
  	case 1: 
		cout << "Percurso PreOrdem floresta" << endl;
  		imprimirPreOrdem(&monitor);
  		break;
	case 2:
		cout << "Percurso PreOrdem arvore" << endl;
		//imprimirPreOrdemArvore(raiz);
		break;
  	default:
  		cout << "Opcao Nao Invalida!!!" << endl;
  }/*switch*/
}

int menu() {
	int opcao;
	system("cls");
	cout << "Digite:" << endl;
	cout << "0. Para Sair" << endl;
	cout << "1.Para Inserir na floresta" << endl;
	cout << "2.Para Inserir na arvore" << endl;
	cout << "3.Para Imprimir a floresta" << endl;
	cout << "4.Para Imprimir a arvore" << endl;
	cout << "5.Teste" << endl;
	cin >> opcao;
	switch(opcao) {
		case 0: return 0;
		case 1:
		{ int elem;
		  cout << "Digite o elemento para inserir na Floresta: ";
		  cin >> elem;
		  //inserir(elem,&raiz);
		  return 1;
		}
		
		case 2:
		{ int elem;
		  cout << "Digite o elemento para inserir na arvore da floresta: ";
		  cin >> elem;
		  //IncluirArvFloresta(elem,&raiz);
		  return 1;
		}
		
		case 3:
		{ 
		  int ordem;
		  cout << "Digite:" << endl;		  
	      cout << "1. Para Imprimir PreOrdem a Floresta" << endl;
	      cin >> ordem;
		  imprimir(ordem);	  
		  system("pause");
		  return 1;
		}
		
		case 4:
		{ 
		  int ordem;
		  cout << "Digite:" << endl;	  
	      cout << "1. Para Imprimir PreOrdem a arvore da floresta" << endl;
	      cin >> ordem;
		  //imprimir(ordem);	  
		  system("pause");
		  return 1;
		}

		case 5:
		{ 
			int x[10]={5, 15, 25, 35, 45, 55, 65, 75, 85, 95};
			int z[9]={50, 80, 70, 40, 10, 30, 60, 20, 90};
			
			int sizez = sizeof(z) / sizeof(z[0]); // Obtem o tamanho do vetor Z
			for(int i=0; i<sizez; i++) {
				inserirFloresta(z[i], &monitor);
				
			}
			
			int sizex = sizeof(x) / sizeof(x[0]); // Obtem o tmanho do vetor X
			for(int i=0; i<sizex; i++) {
				//inserir(x[i]);
			}
			
		  	//imprimir(1);	  
		  	system("pause");
		  	return 1;
        }       
		
		default:
			cout << "Digite uma opcao VALIDA!";
			return 1;
	}	
}

main() {
	create();
	while(menu());
}

void imprimirPreOrdemArvore(struct EnoArvore *arvore)
{
	if(!arvore) return;
	
	cout << "[";
  	cout << arvore->chave;
  	//imprimirPreOrdem(arvore->esq);  
  	//imprimirPreOrdem(arvore->dir);  
	cout << "]";
}
