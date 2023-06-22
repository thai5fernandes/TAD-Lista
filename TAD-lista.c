#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    int codigo;
    char nome[50];
    int quantidade;
    float preco;
    char descricao[100];
} TProduto;

typedef struct celula {
    TProduto item;
    struct celula* prox;
} TCelula;

typedef struct Lista {
    TCelula* primeiro;
    TCelula* ultimo;
    int tamanho;
} TLista;

// Inicializacao da lista vazia
void FLVazia(TLista *Lista) {
    Lista -> primeiro = (TCelula*)malloc(sizeof(TCelula));
    Lista -> ultimo = Lista -> primeiro;
    Lista -> primeiro -> prox = NULL;
    Lista -> tamanho = 0;
}

// Verificao da lista vazia
int Vazia(TLista Lista) {
    return (Lista.primeiro == Lista.ultimo);
}

// Inserindo produto na lista
void Inserir(TProduto x, TLista *Lista) {
    Lista -> ultimo -> prox = (TCelula*)malloc(sizeof(TCelula));
    Lista -> ultimo = Lista -> ultimo -> prox;
    Lista -> ultimo -> item = x;
    Lista -> ultimo -> prox = NULL;
    Lista -> tamanho++;
}

// leitura dos dados de entrada
void lerProduto(TProduto *x) {

    //codigo
    printf("Digite o codigo do produto: ");
    fflush(stdin);
    scanf("%d", &(x->codigo));

    //nome
    printf("Digite o nome do produto: ");
    fflush(stdin);
    fgets(x->nome, 50, stdin);
    x->nome[strcspn(x->nome, "\n")] = '\0';

    //quantidade
    printf("Digite a quantidade do produto: ");
    fflush(stdin);
    scanf("%d", &(x->quantidade));

    //preco
    printf("Digite o preco do produto: ");
    fflush(stdin);
    scanf("%f", &(x->preco));

    //descricao
    printf("Digite a descricao do produto: ");
    fflush(stdin);
    fgets(x->descricao, 100, stdin);
    x->nome[strcspn(x->nome, "\n")] = '\0';
}

void Imprimir(TLista Lista) {
    TCelula* Aux;
    Aux = Lista.primeiro -> prox;
    while (Aux != NULL) {
        ImprimirProduto(Aux);
        Aux = Aux->prox;
    }
}

// Pesquisa do produto pelo codigo
TCelula* Pesquisar(TLista Lista, TProduto Item) {
    TCelula* Aux;
    Aux = Lista.primeiro;
    while (Aux->prox != NULL) {
        if (Aux->prox->item.codigo == Item.codigo)
            return Aux;
        Aux = Aux->prox;
    }
    return NULL;
}

void Excluir(TLista *Lista, TProduto *Item){
    TCelula *Aux1, *Aux2;
    Aux1 = Pesquisar(*Lista, *Item);
    if(Aux1 != NULL){
        Aux2 = Aux1->prox;
        Aux1->prox = Aux2->prox;
        *Item = Aux2->item;
        if(Aux1->prox == NULL)
           Lista->ultimo = Aux1;
        free(Aux2);
        Lista->tamanho--;
    }
    else
    {
        printf("\nNao e possivel excluir:\n");
        Item->codigo = -1;
    }
}

//impressco dos produtos
void ImprimirProduto(TCelula* x) {
    printf("Codigo: %d\n", x->item.codigo);
    printf("Nome: %s\n", x->item.nome);
    printf("Quantidade: %d\n", x->item.quantidade);
    printf("Preco: %.2f\n", x->item.preco);
    printf("Descricao: %s\n", x->item.descricao);
}

int main() {
    TLista Lista;
    TProduto x;
    int opcao;
    x.codigo = 1;
    FLVazia(&Lista);

while (1) {
        printf("\n-----------------------------\n");
        printf("\tOpcoes:\n");
        printf("1- Inserir um produto.\n");
        printf("2- Excluir um produto.\n");
        printf("3- Imprimir a lista.\n");
        printf("4- Pesquisar por um produto.\n");
        printf("5- Sair!\n");
        printf("\n-----------------------------\n");
        printf("\nEscolha uma opcao: ");
        fflush(stdin);
        scanf("%d", &opcao);
        printf("-----------------------------\n");

   switch (opcao){
    case 1:
        lerProduto(&x);
        Inserir(x, &Lista);
        printf("Produto inserido com sucesso!\n");
        break;

    case 2:
        printf("\nInsira o codigo do produto que deseja excluir: ");
        fflush(stdin);
        scanf("%d", &(x.codigo));
        Excluir(&Lista, &x);
           if(x.codigo != -1) {
           ImprimirProduto(&x);
           printf("\nProduto excluido!\n");
          } else {
           printf("\nProduto nao encontrado!\n");
          }
         break;
    case 3:
        if (Vazia(Lista)) {
            printf("\nA lista esta vazia!\n");
        } else {
            printf("\nLista dos produtos:\n");
            Imprimir(Lista);
        }
         break;
    case 4:
       printf("\nDigite o codigo do produto que deseja encontar:\n ");
       fflush(stdin);
       scanf("%d", &(x.codigo));
       TCelula* p = Pesquisar(Lista, x);
       if (p != NULL) {
           printf("\nProduto encontrado!\n");
           printf("Codigo: %d\n", p->item.codigo);
           printf("Nome: %s\n", p->item.nome);
           printf("Quantidade: %d\n", p->item.quantidade);
           printf("Preco: %.2f\n", p->item.preco);
           printf("Descricao: %s\n", p->item.descricao);
       }else{
            printf("\nProduto desejado nao encontrado!\n");
       }
        break;
    case 5:
        printf("\nSaindo!!\n");
        exit(0);
    default:
        printf("\nOpcao invalida!\nDigite novamente.\n");
        break;
        }
    }

    return 0;
 }
