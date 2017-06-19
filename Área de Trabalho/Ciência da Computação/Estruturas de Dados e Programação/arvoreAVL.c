//Programador: Matheus E. Santana
//18/06/2017
#include <stdio.h>
#include <stdlib.h>

typedef struct Celula{
	struct Celula * esq;
	struct Celula * dir;
	struct Celula * raiz;
	int num;

}Celula;
/*Inserir elemento na árvore*/
void ins_AVL(Celula **r, int valor);
/*Busca elemento na árvore.*/
Celula *busca_AVL (Celula *r, int x);
/*Remove um elemento da árvore.*/
int rem_AVL (Celula **r, int x);
/*Retorna o maior nó entre os filhos*/
Celula *maior (Celula **r);
/*Imprime o valor do nó e o fator de balanceamento.*/
void visita(Celula *no);
/*Imprime árvore em ordem simetrica.*/
void percursoERD(Celula *r);
/*Imprime a altura do nó.*/
int altura(Celula *no);
/*Retorna o maior valor entre duas alturas.*/
int max(int a, int b);
/*Aplica rotação a esquerda.*/
Celula *rotacao_esq(Celula **no);
/*Aplica rotação a direita.*/
Celula *rotacao_dir(Celula **no);
/*Aplica uma dupla rotação a direita.*/
Celula *rotacao_dupla_dir(Celula **no);
/*Aplica uma dupla rotação a esquerda.*/
Celula *rotacao_dupla_esq(Celula **no);
/*Calcula o fator de balanceamento de um nó.*/
int balanceamento(Celula *no);
/*Balaceia a árvore toda.*/
void balanceia_avl(Celula **no);

int main(){
	int i = 0;
	int operacao;
	int l = 1;
	int qtd;
	int no;
	int noPesquisado;
	Celula *r = NULL;
	while(l){
		
		Celula *noResultado = NULL;
		noPesquisado = 0;
		qtd = 0;
		printf("-----------------ARVORE AVL----------------\n");
		printf("Digite o numero da operacao para efetua-la!\n");
		printf("1 - Inserir nos.\n");
		printf("2 - Buscar nos.\n");
		printf("3 - Remover nos.\n");
		printf("4 - Imprimir arvore e fatores de balanceamento.\n" );
		printf("5 - Sair!\n");
		

		scanf("%d", &operacao);

		if(operacao == 1){
			printf("Digite a quantidade de nos!\n");
			scanf("%d", &qtd);
			for(i = 0; i < qtd; i++){
			printf("Insira o no %d\n", i+1);
				scanf("%d", &no);
				ins_AVL(&r, no);
			}
			balanceia_avl(&r);		
			
		}
		if(operacao == 2){
			printf("Digite o no a ser pesquisado!\n");
			scanf("%d", &no);
			 noResultado = busca_AVL(r, no);

			if(noResultado == NULL){
				printf("Resultado: NULL\n");
			}else if(noResultado->num == no){
				printf("Resultado:  %d\n", no);
			}

		}
		if(operacao == 3){
			printf("Digite o valor do no a ser removido!\n");
			scanf("%d", &no);
			noResultado = busca_AVL(r, no);
			if(noResultado == NULL)
				printf("0\n");
			else if(noResultado->num == no){
				rem_AVL(&r, no);
				printf("1\n");
				//rebalancear.
			balanceia_avl(&r);
				
			}
		}

		if(operacao == 4){
			percursoERD(r);
		}
		if(operacao == 5){
			break;
		}

		
	}
	
}
/*Recebe um ponteiro para a raiz de uma árvore AVL e um inteiro e insere um novo nó q com o valor do inteiro.*/
void ins_AVL(Celula **r, int valor){
	/*Verificar se a árvore está vazia*/
	Celula *nova;			//Célula que será inserida.
	Celula *ant = NULL;		//Ponteiro para o nó anterior a célula.
	Celula *prox = NULL;	//Ponteiro para o próximo nó da célula.
	
	/*Instânciando nova célula*/
	nova = (Celula*) malloc(sizeof(Celula));
	nova->esq = NULL;
	nova->dir = NULL;
	nova->num = valor;
	
	/*Caso a árvore esteja vazia.*/
	if(*r == NULL){	
		*r = nova;
	
	/*Caso tenha pelo menos um elemento*/
	}else{
		/*Andando pela árvore a partir da raiz.*/
		prox = *r;

		while(prox != NULL){
			/*Guardando posição do nó da vez.*/
			ant = prox; 

			/*Efetuando percuso na árvore.*/
			if(valor < prox->num){
				prox = prox->esq;
			}else if(valor > prox->num){
				prox = prox->dir;
			}else{
				printf("Nó já existente!");
				free(nova);
				return;
			}
			
		}
	/*Inserindo o novo nó.*/	
	if(valor < ant->num){
		ant->esq = nova;
		nova->raiz = ant;
	}
	if(valor > ant->num)
		ant->dir = nova;
		nova->raiz = ant;
	}
	//Balancear a arvore!!
	
}

Celula *busca_AVL (Celula *r, int x){
	if(r == NULL){
		return NULL;
	}
	if(r->num == x){
		return r;	
	}
	if( x < r->num){
		return(busca_AVL(r->esq, x));
	}

	if( x > r->num){
		return(busca_AVL(r->dir, x));
	}
	
}

int rem_AVL (Celula **r, int x){
	/*Verificar se a árvore não está vazia!*/
	Celula *aux;

	if((*r) == NULL)
		return 0;
	
	/*Quando achar o nó*/
	if((*r)->num == x){
		/*Não remover este printf!*/
		printf("");
		
		aux = (*r);
		/*1 - Se o nó tem só o filho da direita, substitua-o pelo filho.*/
		if((*r)->esq == NULL)
			*r = (*r)->dir;
		
		else if((*r)->dir == NULL)
			*r = (*r)->esq;
		
		else{
			/*Caso tenha dois filhos, substitua pelo maior nó da subárvore esquerda..*/
			aux = maior(&((*r)->esq));
			(*r)->num = aux->num;
		}
		free(aux);	
		return 1;
	
	}else{
		if(x < (*r)->num)
			return rem_AVL(&((*r)->esq), x);
		else
			return rem_AVL(&((*r)->dir), x);
	}
}

Celula *maior (Celula **r){
	Celula *aux = *r;
	if (aux->dir==NULL){
		*r = (*r)->esq;
		return (aux);
	}else
		return maior(&((*r)->dir));
}

void percursoERD(Celula *r){
	if(r != NULL){
	if(r->esq != NULL)
		percursoERD(r->esq);
	visita(r);

	if(r->dir != NULL)
		percursoERD(r->dir);
	}
}
void visita(Celula *no){
	printf("No: %d  Fator de balanceamento: %d\n", no->num, balanceamento(no));

}

int altura(Celula *no){
	int altura_dir = 0;
	int altura_esq = 0;
	if(no == NULL)
		return 0;
	if(no->esq != NULL)
		altura_esq = altura(no->esq);
	if(no->dir != NULL)
		altura_dir = altura(no->dir);

	return max(altura_esq, altura_dir)+ 1;
}
int max(int a, int b){
	if(a >= b)
		return a;
	else
		return b;
}

Celula *rotacao_esq(Celula **no){
	Celula *aux;
    aux = (*no)->dir;
    (*no)->dir = aux->esq;
    
       aux->esq = (*no);
    return aux; 
}

Celula *rotacao_dir(Celula **no){
	Celula *aux = (*no)->esq;
	(*no)->esq = aux->dir;
	aux->dir = *no;
	return aux;
}

Celula *rotacao_dupla_dir(Celula **no){
	(*no)->esq = rotacao_esq(&((*no)->esq));
	return rotacao_dir(&(*no));

}

Celula *rotacao_dupla_esq(Celula **no){
	(*no)->dir = rotacao_dir(&((*no)->dir));
	return rotacao_esq(&(*no));
}

int balanceamento(Celula *no){
	return (altura(no->esq) - altura(no->dir));
}

void balanceia_avl(Celula **no){
	if(*no != NULL){
		if(balanceamento(*no) <= -2){
			if(balanceamento((*no)->esq) == 1){
				*no = rotacao_dupla_esq(&(*no));

			}else{
				*no = rotacao_esq(&(*no));	
				//printf("saiur\n");
				
			}

		}else if(balanceamento(*no) >= 2){
					
			if(balanceamento((*no)->dir) == -1){
				(*no) = rotacao_dupla_esq((*no));
			}else
				(*no) = rotacao_esq((*no));
				
		}

		if((*no)->esq != NULL){
			balanceia_avl(&((*no)->esq));
		}

		if((*no)->dir != NULL){
			balanceia_avl(&((*no)->dir));
		}
	}
}